//
//  boss_bot.h
//  fazan
//
//  Created by Andy Nic on 04/07/2022.
//

#ifndef boss_bot_h
#define boss_bot_h
#include <vector>
#include <iostream>


using namespace std;

class boss_bot : bot
{
public:
    boss_bot(database db);
    
public:
    std::string get_reply(std::string last_word);
    
private:
    static vector<vector<long int>> base_link_level(vector<string> dictionary);
    static vector<vector<long int>> word_scores(vector<string> dictionary, vector<vector<long int>> link_level);
    vector<string> get_best_words(int min, string last_word);
    
private:
    vector<vector<long int>> ws;
};

#endif /* boss_bot_h */
