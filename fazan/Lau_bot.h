//
//  Lau_bot.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Lau_bot_h
#define Lau_bot_h

class Lau_bot : Bot
{
public:
    Lau_bot(Database db) : Bot(db) {};
    
public:
    std::string get_reply(std::string last_word);
};

#endif /* Lau_bot_h */
