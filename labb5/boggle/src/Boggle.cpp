
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
    board.resize(BOARD_SIZE, BOARD_SIZE);
    chosen_letters = toUpperCase(chosen_letters);
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
    board.resize(BOARD_SIZE, BOARD_SIZE);

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





void Boggle::load_english_word(){
    dict.addWordsFromFile(DICTIONARY_FILE);
}

bool Boggle::human_word_is_in_board(const string& word) const{

  Grid<bool> marked_currently_used_letters(BOARD_SIZE, BOARD_SIZE);

    for (int row = 0; row < BOARD_SIZE; row++){
        for (int col = 0; col < BOARD_SIZE; col++){
            if (search_human_helper_func(word, row, col, marked_currently_used_letters)){
                return true;

            }
        }
    }
    return false;

}

bool Boggle::search_human_helper_func(const string& word, int row, int col, Grid<bool>& marked_letters) const {

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

    if (current_word.length() >= MIN_WORD_LENGTH && dict.contains(current_word) && !computer_word.contains(current_word) && !human_word.contains(current_word)){
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




bool Boggle:: is_valid_letter(const string& chosen_letters)const {

    if (chosen_letters.length() != BOARD_SIZE * BOARD_SIZE){
        return false;
    }

    for (char letter: chosen_letters){
        if (!isalpha(letter)){
            return false;
        }
    }
    return true;

}


bool Boggle::check_word_length(const string& word) const {
    return word.length() >= MIN_WORD_LENGTH;
}


bool Boggle::is_in_dictionary(const string& word) const {
    return dict.contains(word);
}


bool Boggle::already_found(const string& word) const {
    return human_word.contains(word);
}


void Boggle:: update_human_status(const string& word){
    human_word.insert(word);
    human_score += word.length() - 3;

}

char Boggle::get_letter_in_board(int row, int col) const {
    return board.get(row, col);
}





