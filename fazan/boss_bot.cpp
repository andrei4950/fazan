//
//  boss_bot.cpp
//  fazan
//
//  Created by Andy Nic on 04/07/2022.
//

#include <stdio.h>
#include "bot.h"
#include "boss_bot.h"
#include "database.h"
#include "tools.h"

using namespace std;

boss_bot::boss_bot(database db) : bot(db)
{
    vector<string> all_words = m_db.get_all_words();
    vector<vector<long int>> bll = base_link_level(all_words);
    
    ws = word_scores(all_words, bll);
}

vector<string> get_closing_words(database db)
{
    vector<string> all_words = db.get_all_words();
    vector<string> closing_words = {};
    bool is_ending_closing[26][26];
    
    for(int i = 0; i < 26; i++)
    {
        for(int j = 0; j < 26; j++)
        {
            is_ending_closing[i][j] = 1;
        }
    }
    
    long int dictionary_size = all_words.size();
    for(int iter = 0; iter < dictionary_size; iter ++)
    {
        if (all_words[iter].size()>1)
        {
            int first_letter = all_words[iter][0] - 'A';
            int second_letter = all_words[iter][1] - 'A';
            is_ending_closing[first_letter][second_letter] = 0;
        }
    }
    
    for(int iter = 0; iter < dictionary_size; iter ++)
    {
        string word = all_words[iter];
        if (word.size()>1)
        {
            if(is_ending_closing[word[word.size()-2]-'A'][word[word.size()-1]-'A'])
            {
                closing_words.push_back(word);
            }
        }
    }
    return closing_words;
}

vector<string> boss_bot::get_best_words(int min, string last_word)
{
    vector<string> all_words = m_db.get_all_words();
    vector<string> used_words = m_db.get_used_words();
    
    vector<string> available_words;
    set_difference(all_words.begin(), all_words.end(), used_words.begin(), used_words.end(), back_inserter(available_words));
    
    vector<string> best_words;
    long int dictionary_size = available_words.size();
    while(best_words.size() == 0 && min <= 1000)
    {
        cout<<min<<"\n";
        for(int iter = 0; iter < dictionary_size; iter ++)
        {
            string word = available_words[iter];
            if (word.size()>1)
            {
                if(ws[word[word.size()-2]-'A'][word[word.size()-1]-'A'] == min && tools::are_words_linked(last_word, word))
                {
                    best_words.push_back(word);
                }
            }
        }
        min++;
    }
    return best_words;
}

vector<vector<long int>> boss_bot::base_link_level(vector<string> dictionary)
{
    vector<vector<long int>> base_link_level;
    for(int i = 0; i < 26; i++)
    {
        base_link_level.push_back({});
        for(int j = 0; j < 26; j++)
        {
            base_link_level[i].push_back({0});
        }
    }
    
    long int dictionary_size = dictionary.size();
    for(int iter = 0; iter < dictionary_size; iter ++)
    {
        if (dictionary[iter].size()>1)
        {
            int first_letter = dictionary[iter][0] - 'A';
            int second_letter = dictionary[iter][1] - 'A';
            base_link_level[first_letter][second_letter]++;
        }
    }
    return base_link_level;
}

vector<vector<long int>> boss_bot::word_scores(vector<string> dictionary, vector<vector<long int>> link_level)
{
    vector<vector<long int>> word_scores;
    for(int i = 0; i < 26; i++)
    {
        word_scores.push_back({});
        for(int j = 0; j < 26; j++)
        {
            word_scores[i].push_back({link_level[i][j]});
        }
    }
    
    long int dictionary_size = dictionary.size();
    for(int iter = 0; iter < dictionary_size; iter ++)
    {
        string word = dictionary[iter];
        if (word.size()>1)
        {
            if (link_level[word[word.size()-2] - 'A'][word[word.size()-1]-'A'] == 0)
                word_scores[word[0] - 'A'][word[1] - 'A'] = 1000;
        }
    }
    return word_scores;
}

string boss_bot::get_reply(string last_word)
{
    if(last_word.size()>1){
        vector<string> best_words = get_best_words(0, last_word);
        return best_words[0];
    }
    else
    {
        vector<string> best_words = get_best_words(1, last_word);
        return best_words[0];
    }
}
