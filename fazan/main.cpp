#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Tools
{
public:
    static bool are_words_linked(string word1, string word2)
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
};


class Database
{
public:
    static void add_used_word(string word)
    {
        ofstream used_words("used_words.txt");
        used_words<<word<<'\n';
        used_words.close();
    }

    static void reset_used_words()
    {
        
    }

private:
    static string get_file_content(string filename)
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
    
public:
    static vector<string> get_file_content_vector(string filename)
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

    static vector<string> get_used_words()
    {
        return get_file_content_vector("/Users/andynic/c++ projects/fazan/fazan/used_words.txt");
    }

    static bool is_used(string word)
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

    static vector<string> get_all_words()
    {
        return get_file_content_vector("/Users/andynic/c++ projects/fazan/fazan/list.txt");
    }

    static bool is_real(string word)
    {
        transform(word.begin(), word.end(), word.begin(), :: toupper);
        vector<string> all_words = get_all_words();
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

};


class Display
{
public:
    static void display_player_response(string word, bool is_player_one_turn)
    {
        if(is_player_one_turn)
            cout<<"First player's response:  ";
        else
            cout<<"Second player's response: ";
        cout<<word<<endl;
    }

    static void display_round_over(int score1, int score2)
    {
        cout << "ROUND OVER!" << endl;
        cout << "First player score is  " << score1 << endl;
        cout << "Second player score is " << score2 << endl;
    }
};


class Bot
{
public:
    virtual string get_reply(string last_word) = 0;
};


class Fazan_god:Bot
{
public:
    virtual string get_reply(string last_word)
    {
        return 0;
    }
};


class Andy_bot:Bot
{
    vector<string> get_closing_words(Database db)
    {
        vector<string> all_words = db.get_all_words();
        vector<string> closing_words = {};
        bool is_ending_closing[26][26];
        
        for(int i = 0; i < 26; i++)
        {
            for(int j = 0; j < 26; j++)
            {
                is_ending_closing[i][j] = 1;
            }
        }
        
        long int dictionary_size = all_words.size();
        for(int iter = 0; iter < dictionary_size; iter ++)
        {
            is_ending_closing[all_words[iter][0]][all_words[iter][1]] = 0;
        }
        
        for(int iter = 0; iter < dictionary_size; iter ++)
        {
            string word = all_words[iter];
            if(is_ending_closing[word[word.size()-2]][word[word.size()-1]])
            {
                closing_words.push_back(word);
            }
        }
        return closing_words;
    }
public:
    virtual string get_reply(string last_word)
    {
        closing_words = get_closing_words(db)
        return 0;
    }
};


class Human_bot:Bot
{
    string get_response(string last_word)
    {
        string response;
        cout << "Other player said " << last_word << endl;
        cout << "Your response: ";
        getline(cin, response);
        return response;
    }
    
public:
    virtual string get_reply(string last_word)
    {
        string response = get_response(last_word);
        while((!Database::is_real(response) ||  !Tools::are_words_linked(last_word, response)) && response != "")
        {
            cout << "That word is not real or not linked! Try again, or leave empty. " << endl;
            response = get_response(last_word);
        }
        return response;
    }
};


class Core
{
    void setup_game(int &player1_score, int &player2_score, string &last_word, string &second_to_last_word)
    {
        player1_score = 0;
        player2_score = 0;
        last_word = "";
        second_to_last_word = "";
    }

    bool is_game_over(int player1_score, int player2_score)
    {
        return player1_score>=5 || player2_score>=5;
    }

    bool is_round_over(string last_word, string second_to_last_word)
    {
        return !(Tools::are_words_linked(second_to_last_word, last_word)) || !(Database::is_real(last_word)) || Database::is_used(last_word);
    }
    
public:
    void run_game()
    {
        int player1_score;
        int player2_score;
        string last_word;
        string second_to_last_word;
        bool is_player_one_starting = rand() % 2;
        bool is_player_one_turn = is_player_one_starting;
        Human_bot player1;
        Human_bot player2;

        setup_game(player1_score, player2_score, last_word, second_to_last_word);
        
        while(!is_game_over(player1_score, player2_score))
        {
            int word_number = 0;
            char starting_letter = (char)((int)'A' + (rand() % 26));
            last_word += starting_letter;
            
            do
            {
                if(is_player_one_turn)
                {
                    second_to_last_word = last_word;
                    last_word = player1.get_reply(last_word);
                    transform(last_word.begin(), last_word.end(), last_word.begin(), :: toupper);
                }
                else
                {
                    second_to_last_word = last_word;
                    last_word = player2.get_reply(last_word);
                    transform(last_word.begin(), last_word.end(), last_word.begin(), :: toupper);
                }
                
                if(word_number>0)
                    Display::display_player_response(last_word, is_player_one_turn);
                
                word_number++;
                is_player_one_turn = !is_player_one_turn;
            }while(!is_round_over(last_word, second_to_last_word));
            
            if(word_number == 2)
            {
                if(is_player_one_turn)
                    player2_score++;
                else
                    player1_score++;
            }
            else
            {
                if(is_player_one_turn)
                    player1_score++;
                else
                    player2_score++;
            }
            
            Display::display_round_over(player1_score, player2_score);
        }
    }
};

int main()
{
    Core core;
    core.run_game();
    return 0;
}

