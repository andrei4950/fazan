#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "database.h"
#include "bot.h"
#include "lau_bot.h"
#include "Alex_bot.h"
#include "human_bot.h"
#include "boss_bot.h"
#include "tools.h"

using namespace std;

class display
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


class Fazan_god:bot
{
public:
    virtual string get_reply(string last_word, database db)
    {
        return 0;
    }
};


class Andy_bot:bot
{
public:
    Andy_bot(database db) : bot(db) {};
    
private:
    vector<string> get_closing_words(database db)
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
            if (all_words[iter].size()>1)
            {
                int first_letter = all_words[iter][0] - 'A';
                int second_letter = all_words[iter][1] - 'A';
                is_ending_closing[first_letter][second_letter] = 0;
            }
        }
        
        for(int iter = 0; iter < dictionary_size; iter ++)
        {
            string word = all_words[iter];
            if (word.size()>1)
            {
                if(is_ending_closing[word[word.size()-2]-'A'][word[word.size()-1]-'A'])
                {
                    closing_words.push_back(word);
                }
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
                if(tools::are_words_linked(last_word, closing_words[iter]) && !m_db.is_used(closing_words[iter]))
                {
                    response = closing_words[iter];
                    return response;
                }
            }
        }
        
        vector<string> all_words = m_db.get_all_words();
        for(int iter = 0; iter < all_words.size(); iter ++)
        {
            if(tools::are_words_linked(last_word, all_words[iter]) && !m_db.is_used(all_words[iter]))
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

    bool is_round_over(string last_word, string second_to_last_word, database db)
    {
        return !(tools::are_words_linked(second_to_last_word, last_word)) || !(database::is_real(last_word)) || db.is_used(last_word);
    }
    
public:
    void run_game()
    {
        int player1_score;
        int player2_score;
        string last_word;
        string second_to_last_word;
        bool is_player_one_starting = rand() % 2;
        bool is_player_one_turn;
        database db;
        Andy_bot player1(db);
        boss_bot player2(db);

        setup_game(player1_score, player2_score, last_word, second_to_last_word);
        
        while(!is_game_over(player1_score, player2_score))
        {
            //round starts
            
            int word_number = 0;
            is_player_one_turn = is_player_one_starting;
            char starting_letter = (char)((int)'A' + (rand() % 26));
            last_word += starting_letter;
                        
            do
            {
                //turn starts
                
                db.add_used_word(last_word);
                
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
                
                display::display_player_response(last_word, is_player_one_turn);
                word_number++;
                is_player_one_turn = !is_player_one_turn;
                
                //turn ends
                
            }while(!is_round_over(last_word, second_to_last_word, db));
            
            if(word_number == 2 && tools::is_closing(second_to_last_word, db.get_used_words()))  //when you immediately end
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

            display::display_round_over(player1_score, player2_score);
            is_player_one_starting = !is_player_one_starting;
            
            //round ends
            
        }
        db.reset_used_words();
        //game ends
    }
};

int main()
{
    Core core;
    core.run_game();
    return 0;
}

