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

#include "Database.h"

using namespace std;


void Database::add_used_word(string word)
{
    ofstream used_words("used_words.txt");
    used_words<<word<<'\n';
    used_words.close();
}

void Database::reset_used_words()
{
    
}

string Database::get_file_content(string filename)
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

vector<string> Database::get_file_content_vector(string filename)
{
    vector<string> content_vector = {};
    string content_string = get_file_content(filename);
    string word = "";
    for (unsigned i=0; i<content_string.length(); ++i)
    {
        if(content_string.at(i) == ' ')
        {
            if(word != "")
            {
                content_vector.push_back(word);
                word = "";
            }
        }
        else
        {
            word += content_string.at(i);
        }
    }
    return content_vector;
}

vector<string> Database::get_used_words()
{
    return get_file_content_vector("/Users/andynic/c++ projects/fazan/fazan/used_words.txt");
}

bool Database::is_used(string word)
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

vector<string> Database::get_all_words()
{
    return get_file_content_vector("/Users/andynic/c++ projects/fazan/fazan/list.txt");
}

bool is_real(string word)
{
    transform(word.begin(), word.end(), word.begin(), :: toupper);
    vector<string> all_words = Database::get_all_words();
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

