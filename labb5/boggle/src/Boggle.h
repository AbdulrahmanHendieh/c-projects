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
    Grid<char> board;


    // Retuns the human player's current score.
    int get_human_score() const;

    // Returns the computer's current score.
    int get_computer_score() const;

    // Returns the set of valid words fond by the human player.
    Set<string> get_human_words() const;

    // Returns the set of valid words found by the computer.
    Set<string> get_computer_words() const;

    // Initializes the game board using custom letters or random cubes if empty.
    void create_custom_board(string chosen_letters);


    // Validates a word against the dictionary, minimum length, and previous guesses.
    string check_word(string word);

    // Loads the English dictionary words from file into the lexicon.
    void load_english_word();

    // Searches the board for the given human word and updates score if found.
    bool search_human_word_in_board(string word);

    // Finds all remaining valid words on the board for the computer.
    void search_computer_word_in_board();

    // Resets scores and fond word sets for a new game.
    void reset();



private:
    Lexicon dict;
    int human_score = 0;
    int computer_score = 0;
    Set<string> human_word;
    Set<string> computer_word;

    // Populates the board grid with the 16 user provided letters.
    void set_up_custom_board(string chosen_letters);

    // Populates the board grid by shuffling and rolling the standard Boggle cube
    void set_up_random_board();

    // Recursive helper using backtracking to verify if a word can be formed from (ro, col).
    bool search_human_helper_func(string word,int row,int col, Grid<bool>& marked_letters);

    // Recursive helper using backtracking and prefix pruning to collect all valid words from (row, col).
    void search_computer_helper_func(int row,int col, Grid<bool>& marked_letters, string current_word);


};

#endif
