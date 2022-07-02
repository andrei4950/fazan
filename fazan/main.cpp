#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Bot.cpp"
#include "Lau_bot.cpp"
#include "Database.cpp"


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
    virtual string get_reply(string last_word)
    {
        return 0;
    }
};


class Andy_bot:Bot
{
public:
    virtual string get_reply(string last_word)
    {
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

