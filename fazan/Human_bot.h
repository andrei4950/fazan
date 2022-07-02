//
//  Human_bot.hpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Human_bot_hpp
#define Human_bot_hpp

#include <stdio.h>
#include "Bot.h"

class Human_bot : Bot
{
public:
    Human_bot(Database db) : Bot(db) {};
    
public:
    std::string get_reply(std::string last_word);
private:
    std::string get_response(std::string last_word);
};

#endif /* Human_bot_hpp */
