// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h
#include <grid.h>
#include <iostream>
#include <string>
#include <lexicon.h>
#include<set>
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "/Users/abdulrahmanhendieh/Kurser/tddd86/projects/labb5/boggle/res/EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    Grid<char> board;


    int get_human_score() const;
    int get_computer_score() const;
    Set<string> get_human_words() const;
    Set<string> get_computer_words() const;
    void create_custom_board(string chosen_letters);
    string get_chosen_letters();
    string check_word(string word);
    void load_english_word();
    bool search_human_word_in_board(string word);
    void search_computer_word_in_board();
    void reset();



private:
    Lexicon dict;
    int human_score = 0;
    int computer_score = 0;
    Set<string> human_word;
    Set<string> computer_word;
    void set_up_custom_board(string chosen_letters);
    void set_up_random_board();
    bool search_human_helper_func(string word,int row,int col, Grid<bool>& marked_letters);
    void search_computer_helper_func(int row,int col, Grid<bool>& marked_letters, string current_word);







};

#endif
