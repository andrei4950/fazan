//
//  Bot.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Bot_h
#define Bot_h

#include "Database.h"

class Bot
{
protected:
    Database m_db;
public:
    Bot(Database db) : m_db(db) {};
public:
    virtual std::string get_reply(std::string last_word) = 0;
};

#endif /* Bot_h */
