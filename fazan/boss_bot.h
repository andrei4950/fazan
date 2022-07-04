//
//  boss_bot.h
//  fazan
//
//  Created by Andy Nic on 04/07/2022.
//

#ifndef boss_bot_h
#define boss_bot_h

class boss_bot : bot
{
public:
    boss_bot(database db) : bot(db) {};
    
public:
    std::string get_reply(std::string last_word);
};

#endif /* boss_bot_h */
