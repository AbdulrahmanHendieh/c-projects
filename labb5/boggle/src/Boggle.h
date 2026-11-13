//name: Abdulrahman Hendieh
// LiuID: abdhe895


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


using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "/Users/abdulrahmanhendieh/Kurser/tddd86/projects/labb5/boggle/res/EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;



    // Retuns the human player's current score.
    int get_human_score() const;

    // Returns the computer's current score.
    int get_computer_score() const;

    // Returns the set of valid words fond by the human player.
    Set<string> get_human_words() const;

    // Returns the set of valid words found by the computer.
    Set<string> get_computer_words() const;

    // Populates the board grid with the 16 user provided letters.
    void set_up_custom_board(string chosen_letters);

    // Populates the board grid by shuffling and rolling the standard Boggle cube
    void set_up_random_board();


    // Loads the English dictionary words from file into the lexicon.
    void load_english_word();

    // return true of human word is in board
    bool human_word_is_in_board(const string &word) const;

    // Finds all remaining valid words on the board for the computer.
    void search_computer_word_in_board();

    // Resets scores and fond word sets for a new game.
    void reset();

    // Checks whether all characters in the given string are alphabetic letters.
    bool is_valid_letter(const string& chosen_letters) const;

    // checking word length if length less then 4 then return false other way retrurn true

    bool check_word_length(const string& word) const;

    // Checks whether the given word exists in the English dictionary.
    bool is_in_dictionary(const string& word) const;

    // Checks whether the human player has already found the given word.
    bool already_found(const string& word) const;

    // Adds a valid word to the human player's word set and updates their score.
    void update_human_status(const string& word);

    // Returns the character located at (row, col) on the game board.
    char get_letter_in_board(int row, int col) const;



private:
    Lexicon dict;
    int human_score = 0;
    int computer_score = 0;
    Set<string> human_word;
    Set<string> computer_word;
    Grid<char> board;


    // Recursive helper using backtracking to verify if a word can be formed from (ro, col).
    bool search_human_word_helper_func(const string& word,int row,int col, Grid<bool>& marked_letters) const ;

    // Recursive helper using backtracking and prefix pruning to collect all valid words from (row, col).
    void search_computer_words_helper_func(int row,int col, Grid<bool>& marked_letters, string current_word);


};

#endif
