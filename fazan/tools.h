//
//  Tools.hpp
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Tools_hpp
#define Tools_hpp

#include <string>
#include <stdio.h>

class tools
{
public:
    static bool are_words_linked(std::string word1, std::string word2);
    static bool is_closing(std::string word, std::vector<std::string> used_words);
};

#endif /* Tools_hpp */
