//
//  Database.cpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "database.h"
#include "settings.h"

using namespace std;

void database::add_used_word(string word)
{
    used_words_db.push_back(word);
    sort(used_words_db.begin(), used_words_db.end());
}

void database::reset_used_words()
{
    used_words_db = {};
}

string database::get_file_content(string filename)
{
    ifstream file;
    file.open(filename);
    string content;
    if ( file.is_open() )
    {
        string line;
        while(getline(file, line))
        {
            content.append(line);
            content.append(" ");
        }
        file.close();
    }
    else
    {
        cout<<"ERROR! File not found. "<<endl;
        content = "";
    }
    return content;
}

bool database::uses_normal_letters(std::string word)
{
    bool is_normal = 1;
    int size = word.size();
    for(int i = 0; i < size; i++)
    {
        if(word[i]<'A' || word[i]>'A'+26)
            is_normal = 0;
    }
    return is_normal;
}

vector<string> database::get_file_content_vector(string filename)
{
    vector<string> content_vector = {};
    string content_string = get_file_content(filename);
    string word = "";
    for (unsigned i=0; i<content_string.length(); ++i)
    {
        if(content_string.at(i) == ' ')
        {
            if(word != "" && database::uses_normal_letters(word))
            {
                transform(word.begin(), word.end(), word.begin(), :: toupper);
                content_vector.push_back(word);
                word = "";
            }
            else
                word = "";
        }
        else
        {
            word += content_string.at(i);
        }
    }
    sort(content_vector.begin(), content_vector.end());
    return content_vector;
}

vector<string> database::get_used_words()
{
    vector<string> output = used_words_db;
    return output;
}

bool database::is_used(string word)
{
    transform(word.begin(), word.end(), word.begin(), :: toupper);
    vector<string> used_words = get_used_words();
    unsigned long len = used_words.size();
    bool ok = 0;
    
    for(int i=0; i<len; i++)
    {
        if(word == used_words[i])
        {
            ok = 1;
            break;
        }
    }
    return ok;
}

vector<string> database::get_all_words()
{
    return get_file_content_vector(settings::db_path);
}

bool database::is_real(string word)
{
    transform(word.begin(), word.end(), word.begin(), :: toupper);
    vector<string> all_words = database::get_all_words();
    unsigned long len = all_words.size();
    bool ok = 0;
    
    for(int i=0; i<len; i++)            //future improvements: binary search
    {
        if(word == all_words[i])
        {
            ok = 1;
            break;
        }
    }
    return ok;
}

