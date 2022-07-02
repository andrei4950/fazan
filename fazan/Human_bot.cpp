//
//  Human_bot.cpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#include <iostream>
#include "Human_bot.h"

#include "Tools.h"

using namespace std;

string Human_bot::get_reply(string last_word)
{
    string response = get_response(last_word);
    while((!Database::is_real(response) || !Tools::are_words_linked(last_word, response) || m_db.is_used(response)) && response != "")
    {
        cout << "That word is not real, already used or not linked! Try again, or leave empty. " << endl;
        response = get_response(last_word);
    }
    return response;
}

string Human_bot::get_response(string last_word)
{
    string response;
    cout << "Other player said " << last_word << endl;
    cout << "Your response: ";
    getline(cin, response);
    return response;
}
