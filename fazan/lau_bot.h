//
//  Lau_bot.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Lau_bot_h
#define Lau_bot_h

class lau_bot : bot
{
public:
    lau_bot(database db) : bot(db) {};
    
public:
    std::string get_reply(std::string last_word);
};

#endif /* Lau_bot_h */
