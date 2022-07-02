//
//  Alex_bot.h
//  fazan
//
//  Created by Andy Nic on 02/07/2022.
//

#ifndef Alex_bot_h
#define Alex_bot_h

#include <stdio.h>

class Alex_bot : Bot
{
public:
    Alex_bot(Database db);
    
public:
    std::string get_reply(std::string last_word);
    
private:
    void add_future_use(std::string word);
    bool will_be_used(std::string word);
    
private:
    std::vector<std::string> used_words;
};


#endif /* Alex_bot_h */
