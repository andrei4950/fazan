//
//  Bot.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Bot_h
#define Bot_h

#include "database.h"

class bot
{
protected:
    database m_db;
public:
    bot(database db) : m_db(db) {};
public:
    virtual std::string get_reply(std::string last_word) = 0;
};

#endif /* Bot_h */
