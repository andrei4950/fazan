#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool are_words_linked(string word1, string word2)
{
    if(word1[0]==word2[word2.size()-2] && word1[1]==word2[word2.size()-1])
        return 1;
    return 0;
}

void add_used_word(string word)
{
    
}

vector<string> get_used_words()
{
    vector<string> used_words = {"test"};
    return used_words;
}

bool is_used(string word)
{
    vector<string> used_words = get_used_words();
    unsigned long len = used_words.size();
    for(int i=0; i<len; i++)
    {
        if(word == used_words[i])
            return 1;
    }
    return 0;
}

vector<string> get_all_words()
{
    vector<string> all_words = {"test"};
    return all_words;
}

bool is_real(string word)
{
    vector<string> all_words = get_all_words();
    unsigned long len = all_words.size();
    for(int i=0; i<len; i++)
    {
        if(word == all_words[i])
            return 1;
    }
    return 0;
}

void display_response(string word)
{
    
}

void display_turnover(int score1, int score2)
{
    
}

string bot1(string last_letters)
{
    return 0;
}

string bot2(string last_letters)
{
    return 0;
}

int main()
{
    return 0;
}

