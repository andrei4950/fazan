//
//  Database.h
//  fazan
//
//  Created by Laurentiu Taropa on 02/07/2022.
//

#ifndef Database_h
#define Database_h

#include <string>
#include <vector>

class Database
{
public:
    void add_used_word(std::string word);
    void reset_used_words();

private:
    static std::string get_file_content(std::string filename);
    
public:
    static std::vector<std::string> get_file_content_vector(std::string filename);

    std::vector<std::string> get_used_words();
    bool is_used(std::string word);

    static std::vector<std::string> get_all_words();

    static bool is_real(std::string word);
private:
    std::vector<std::string> used_words_db = {};
};

#endif /* Database_h */
