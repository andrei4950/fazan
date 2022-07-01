#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool are_words_linked(string word1, string word2)
{
    if(word1[0]==word2[word2.size()-2] && word1[1]==word2[word2.size()-1])
        return 1;
    return 0;
}

void add_used_word(string word)
{
    ofstream used_words("used_words.txt");
    used_words<<word<<'\n';
    used_words.close();
}

vector<string> get_used_words()
{
    vector<string> used_words = {"test"};
    return used_words;
}

bool is_used(string word)
{
    vector<string> used_words = get_used_words();
    unsigned long len = used_words.size();
    for(int i=0; i<len; i++)
    {
        if(word == used_words[i])
            return 1;
    }
    return 0;
}

vector<string> get_all_words()
{
    vector<string> all_words = {"test"};
    
    ifstream dictionary;
    dictionary.open("/Users/andynic/c++ projects/fazan/fazan/list.txt");
    string content;
    if ( dictionary.is_open() )
    {
        dictionary >> content;
        cout << content;
    }
    dictionary.close();
    
    return all_words;
}

bool is_real(string word)
{
    vector<string> all_words = get_all_words();
    unsigned long len = all_words.size();
    for(int i=0; i<len; i++)
    {
        if(word == all_words[i])
            return 1;
    }
    return 0;
}

void display_player_response(string word, bool is_player_one_turn)
{
    if(is_player_one_turn)
        cout<<"First player's response:  ";
    else
        cout<<"Second player's response: ";
    cout<<word<<endl;
}

void display_round_over(int score1, int score2)
{
    cout << "TURN OVER!" << endl;
    cout << "First player score is  " << score1 << endl;
    cout << "Second player score is " << score2 << endl;
}

string bot1(string last_letters)
{
    return 0;
}

string bot2(string last_letters)
{
    return 0;
}

void setup_game(int &first_player_score, int &second_player_score, string &last_word, string &second_to_last_word)
{
    
}

bool is_game_over(int first_player_score, int second_player_score)
{
    return 1;
}

bool is_round_over(string last_word, string second_to_last_word)
{
    return 1;
}

void run_game()
{
    int first_player_score;
    int second_player_score;
    string last_word;
    string second_to_last_word;
    bool is_player_one_starting = rand() % 2;
    bool is_player_one_turn = is_player_one_starting;

    setup_game(first_player_score, second_player_score, last_word, second_to_last_word);
    
    while(!is_game_over(first_player_score, second_player_score))
    {
        while(!is_round_over(last_word, second_to_last_word))
        {
            
        }
        is_player_one_turn = !is_player_one_turn;
    }
}

int main()
{
    get_all_words();
    return 0;
}

