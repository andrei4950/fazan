//
//  Bot.cpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#include <stdio.h>
#include <string>


class Bot
{
public:
    virtual std::string get_reply(std::string last_word) = 0;
};
