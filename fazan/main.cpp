#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Database.h"
#include "Bot.h"
#include "Lau_bot.h"
#include "Tools.h"

using namespace std;

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


class Fazan_god:Bot
{
public:
    virtual string get_reply(string last_word, Database db)
    {
        return 0;
    }
};


class Andy_bot:Bot
{
public:
    Andy_bot(Database db) : Bot(db) {};
    
private:
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
        string response = "";
        vector<string> closing_words = get_closing_words(m_db);
        if(last_word.size()>1){
            for(int iter = 0; iter < closing_words.size(); iter ++)
            {
                if(Tools::are_words_linked(last_word, closing_words[iter]) && !m_db.is_used(closing_words[iter]))
                {
                    response = closing_words[iter];
                    return response;
                }
            }
        }
        
        vector<string> all_words = m_db.get_all_words();
        for(int iter = 0; iter < all_words.size(); iter ++)
        {
            if(Tools::are_words_linked(last_word, all_words[iter]) && !m_db.is_used(all_words[iter]))
            {
                response = all_words[iter];
                return response;
            }
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

    bool is_round_over(string last_word, string second_to_last_word, Database db)
    {
        return !(Tools::are_words_linked(second_to_last_word, last_word)) || !(Database::is_real(last_word)) || db.is_used(last_word);
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
        Database db;
        Andy_bot player1(db);
        Lau_bot player2(db);

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
            }while(!is_round_over(last_word, second_to_last_word, db));
            
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
            db.reset_used_words();
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

