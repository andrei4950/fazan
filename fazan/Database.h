//
//  Database.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Database_h
#define Database_h

#include <string>

class Database
{
public:
    static void add_used_word(std::string word);
    static void reset_used_words();

private:
    static std::string get_file_content(std::string filename);
    
public:
    static std::vector<std::string> get_file_content_vector(std::string filename);

    static std::vector<std::string> get_used_words();
    static bool is_used(std::string word);

    static std::vector<std::string> get_all_words();

    static bool is_real(std::string word);
};

#endif /* Database_h */
