//
//  Tools.cpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#include "tools.h"

using namespace std;

bool tools::are_words_linked(string word1, string word2)
{
    transform(word1.begin(), word1.end(), word1.begin(), :: toupper);
    transform(word2.begin(), word2.end(), word2.begin(), :: toupper);
    
    bool are_linked;
    if(word1.size() > 1 && word2.size() > 1)
    {
        are_linked = word2[0] == word1[word1.size()-2] && word2[1] == word1[word1.size()-1];
    }
    else
    {
        if(word1.size() == 0 || word2.size() < 2)
            are_linked = 0;
        else
            if(word1.size() == 1)
                are_linked = word1[0] == word2[0];
            else
                are_linked = 0;
    }
    return are_linked;
}

