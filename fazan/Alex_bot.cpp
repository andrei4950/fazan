//
//  Alex_bot.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Alex_bot_hpp
#define Alex_bot_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Bot.h"
#include "Tools.h"

using namespace std;

class Alex_bot:Bot
{
private:
    vector<string> used_words;
    
    void add_future_use(string word)
    {
        used_words[used_words.size()] = word;
    }
    
    bool will_be_used(string word)
    {
        unsigned long len = used_words.size();
        for(int i = 0; i < len; i++)
        {
            if(used_words[i] == word)
                return 1;
        }
        return 0;
    }
    
public:
    Alex_bot(Database db) : Bot(db)
    {
        used_words = db.get_used_words();
    }
    
    string alex_bot(string word)
    {
        vector<string> all_words = Database::get_all_words();
        unsigned long len = all_words.size();
        string reply = "";
        
        if(word.size() != 1)
        {
            vector<string> linked_words;
            vector<string> temp_used_words = used_words;
            unsigned long pos = -1, i = 0;
            
            do
            {
                pos++;
            }while(pos<len || !Tools::are_words_linked(word, all_words[pos]));
            
            while(Tools::are_words_linked(word, all_words[pos]) && pos < len)
            {
                linked_words[i] = all_words[pos];
                i++;
                pos++;
            }
            
            unsigned long linked_len = i;
            bool direct_win = 0;
            
            for(i = 0; i < linked_len; i++)
            {
                if(!Tools::are_words_linked(linked_words[i], alex_bot(linked_words[i])))
                {
                    direct_win = 1;
                    reply = linked_words[i];
                    break;
                }
            }
            
            if(!direct_win)
            {
                for(i = 0; i < linked_len; i++)
                {
                    if(Tools::are_words_linked(alex_bot(linked_words[i]), alex_bot(alex_bot(linked_words[i]))) && !will_be_used(linked_words[i]))
                    {
                        reply = linked_words[i];
                        add_future_use(linked_words[i]);
                        break;
                    }
                }
            }
            
            used_words = temp_used_words;
            add_future_use(reply);
        }
        else
        {
            vector<string> linked_words;
            vector<string> temp_used_words = used_words;
            unsigned long pos = -1, i = 0;
            
            do
            {
                pos++;
            }while(pos < len || !Tools::are_words_linked(word, all_words[pos]));
            
            while(Tools::are_words_linked(word, all_words[pos]) && pos < len)
            {
                linked_words[i] = all_words[pos];
                i++;
                pos++;
            }
            
            unsigned long linked_len = i;
            for(i = 0; i < linked_len; i++)
            {
                if(Tools::are_words_linked(alex_bot(linked_words[i]), alex_bot(alex_bot(linked_words[i]))) && !will_be_used(linked_words[i]))
                {
                    reply = linked_words[i];
                    add_future_use(linked_words[i]);
                    break;
                }
            }
            
            used_words = temp_used_words;
            add_future_use(reply);
        }
        
        return reply;
    }
};

#endif /* Alex_bot_hpp */
