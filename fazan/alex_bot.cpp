//
//  Alex_bot.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Alex_bot_hpp
#define Alex_bot_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "bot.h"
#include "tools.h"
#include "alex_bot.h"

using namespace std;

alex_bot::alex_bot(database db) : bot(db)
{
    used_words = db.get_used_words();
    all_words = db.get_all_words();
    
    int len = all_words.size();
    for(int i = 0; i < 26; i++)
    {

    }
}
   
vector<string> alex_bot::get_links(string word)
{
    vector<string> linked_words;
    unsigned long len = all_words.size();
    unsigned long pos = 0;
    
    do
    {
        pos++;
    }while(pos < len - 2 && !tools::are_words_linked(word, all_words[pos]));
    
    while(tools::are_words_linked(word, all_words[pos]) && pos < len)
    {
        linked_words.push_back(all_words[pos]);
        pos++;
    }
    return linked_words;
}

string alex_bot::direct_closer(string word, vector<string> linked_words)
{
    unsigned long len = linked_words.size();
    unsigned long percent = 0;
    for(unsigned long i = 0; i < len; i++)
    {
        percent = (100 * i) / len;
        if(tools::is_closing(linked_words[i], m_db.get_used_words()))
        {
            return linked_words[i];
        }
    }
    return "";
}

string alex_bot::no_closer(string word, vector<string> linked_words)
{
    string reply = "";
    unsigned long len = linked_words.size();
    
        for(unsigned long i = 0; i < len; i++)
        {
            if(!tools::is_closing(direct_closer(linked_words[i], linked_words), m_db.get_used_words()))
            {
                reply = linked_words[i];
                break;
            }
        }
    return reply;
}

string alex_bot::get_reply(string word)
{
    vector<string> linked_words = get_links(word);
    string reply = "";
    
    if(word.size() != 1)
    {
        reply = direct_closer(word, linked_words);
        
        if(reply == "")
        {
            reply = no_closer(word, linked_words);
        }
    }
    else
    {
        reply = no_closer(word, linked_words);
    }
    
    return reply;
}

#endif /* Alex_bot_hpp */
