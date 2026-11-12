
//name: Abdulrahman Hendieh
// LiuID: abdhe895


// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own



#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include<set>

static const int NUM_CUBES = 16;
static const int CUBE_SIDES = 6;
static string CUBES[NUM_CUBES] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


int Boggle::get_human_score() const {
    return human_score;
}

int Boggle::get_computer_score() const {
    return computer_score;
}

Set<string> Boggle::get_human_words() const {
    return human_word;
}

Set<string> Boggle::get_computer_words() const {
    return computer_word;
}

void Boggle::set_up_custom_board(string chosen_letters){
    int index = 0;
    for (int row = 0; row < BOARD_SIZE; row++){
        for (int col = 0; col < BOARD_SIZE; col++){
            board[row][col] = chosen_letters[index];
            index++;
        }
    }
}

void Boggle::set_up_random_board(){
    string cubes_copy[NUM_CUBES];
    for (int i = 0; i < NUM_CUBES; i++){
        cubes_copy[i] = CUBES[i];
    }
    shuffle(cubes_copy, NUM_CUBES);
    int index = 0;
    for (int row = 0; row < BOARD_SIZE; row++){
        for (int col = 0; col < BOARD_SIZE; col++){
            board[row][col] = cubes_copy[index][randomInteger(0, CUBE_SIDES -1)];
            index++;

        }
    }
}

void Boggle::create_custom_board(string chosen_letters){
    board.resize(BOARD_SIZE, BOARD_SIZE);
    chosen_letters = toUpperCase(chosen_letters);

    if (chosen_letters.empty()){
        set_up_random_board();
    } else{
        set_up_custom_board(chosen_letters);
    }
}

string Boggle::check_word(string word){
    word = toUpperCase(word);

    if (!dict.contains(word)){
        return "That word is not in the dictionary.";
    }

    if (word.length() < 4){
        return "That word is not long enough.";
    }


    if (human_word.contains(word)) {
        return "You have already guessed that word.";
    }

    return word;
}

void Boggle::load_english_word(){
    dict.addWordsFromFile(DICTIONARY_FILE);
}

bool Boggle::search_human_word_in_board(string word){

  Grid<bool> marked_currently_used_letters(BOARD_SIZE, BOARD_SIZE);

    for (int row = 0; row < BOARD_SIZE; row++){
        for (int col = 0; col < BOARD_SIZE; col++){
            if (search_human_helper_func(word, row, col, marked_currently_used_letters)){
                human_word.insert(word);
                human_score += word.length() - 3;
                return true;

            }
        }

    }
    return false;

}

bool Boggle::search_human_helper_func(string word, int row, int col, Grid<bool>& marked_letters){

    if (word.empty()){
        return true;
    }

    if (!board.inBounds(row, col) ){
        return false;
    }

    if (board[row][col] != word[0] ||  marked_letters[row][col]){
        return false;
    }

    marked_letters[row][col] = true;

    for (int dr = -1; dr <= 1; dr++){
        for (int dc = -1; dc <= 1; dc++){
            if (!(dr == 0 && dc == 0)){
                if (search_human_helper_func(word.substr(1), row + dr, col + dc, marked_letters )){
                    return true;
                }

            }
        }
    }
    marked_letters[row][col] = false;
    return false;
}



void Boggle::search_computer_word_in_board(){
    Grid<bool> marked_letters(BOARD_SIZE, BOARD_SIZE);
    for (int row = 0; row < BOARD_SIZE; row++){
        for (int col = 0; col < BOARD_SIZE; col++){
            search_computer_helper_func(row, col, marked_letters, "");
        }
    }

}


void Boggle::search_computer_helper_func(int row, int col,  Grid<bool>& marked_letters, string  current_word){

    if (!board.inBounds(row, col) || marked_letters[row][col]){
        return;
    }
    current_word += board[row][col];

    if (!dict.containsPrefix(current_word)){
        return;
    }

    if (current_word.length() >= 4 && dict.contains(current_word) && !computer_word.contains(current_word) && !human_word.contains(current_word)){
        computer_word.insert(current_word);
        computer_score += current_word.length() - 3;
    }


    marked_letters[row][col] = true;

    for (int dr = -1; dr <= 1; dr++){
        for (int dc = -1; dc <= 1; dc++){
            if (!(dr == 0 && dc == 0)){

                search_computer_helper_func(row + dr, col + dc, marked_letters, current_word);
            }

        }
     }

    marked_letters[row][col] = false;
}

void Boggle::reset() {
    human_score = 0;
    computer_score = 0;
    human_word.clear();
    computer_word.clear();
}













