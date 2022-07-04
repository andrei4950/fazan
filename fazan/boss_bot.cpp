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
    for(int i = 0; i < bll.size(); i++){
        for(int j = 0; j < bll[i].size(); j++)
        {
            cout<<bll[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    vector<vector<long int>> ws = word_scores(all_words, bll);
    cout<<"word scores: "<<"\n";
    for(int i = 0; i < ws.size(); i++){
        for(int j = 0; j < ws[i].size(); j++)
        {
            cout<<ws[i][j]<<" ";
        }
        cout<<"\n";
    }
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
                word_scores[word[0] - 'A'][word[1] - 'A'] = 1000000;
        }
    }
    return word_scores;
}

string boss_bot::get_reply(string last_word)
{
    string response = "";
    vector<string> closing_words = get_closing_words(m_db);
    if(last_word.size()>1){
        for(int iter = 0; iter < closing_words.size(); iter ++)
        {
            if(tools::are_words_linked(last_word, closing_words[iter]) && !m_db.is_used(closing_words[iter]))
            {
                response = closing_words[iter];
                return response;
            }
        }
    }
    
    vector<string> all_words = m_db.get_all_words();
    for(int iter = 0; iter < all_words.size(); iter ++)
    {
        if(tools::are_words_linked(last_word, all_words[iter]) && !m_db.is_used(all_words[iter]))
        {
            response = all_words[iter];
            return response;
        }
    }
    
    return response;
}
