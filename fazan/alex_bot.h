//
//  Alex_bot.h
//  fazan
//
//  Created by Andy Nic on 02/07/2022.
//

#ifndef Alex_bot_h
#define Alex_bot_h

#include <stdio.h>

class alex_bot : bot
{
public:
    alex_bot(database db);
    
public:
    std::string get_reply(std::string last_word);
    
private:
    std::vector<std::string> used_words;
    
private:
    std::vector<std::string> all_words;
    
private:
    bool is_direct_win(std::string word);
    
};


#endif /* Alex_bot_h */
