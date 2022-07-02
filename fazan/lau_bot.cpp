//
//  Lau_bot.cpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#include <stdio.h>
#include "bot.h"
#include "lau_bot.h"
#include "database.h"

using namespace std;

string lau_bot::get_reply(string last_word)
{
    if(last_word.length() >= 2)     // Valid word
    {
        auto ending = last_word.substr(last_word.length() - 2);
//        vector<string> words = Database::get_all_words();
//        auto it = find_if(words.begin(), words.end(), [&](const auto& x) { return x.starts_with(ending);});
//        if(it != words.end()) {
//            return *it;
//        }
    }
    
    return "";
}

