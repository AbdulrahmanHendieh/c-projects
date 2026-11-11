// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need
//FYCLIOMGORILHJHU


void show_board(Boggle& boggle);
bool is_valid_letter(string chosen_letters);
string get_chosen_letters();
string get_word_from_user(Boggle& boggle);
void show_human_score(Boggle& boggle);
void show_computer_score(Boggle& boggle);
void show_human_words(Boggle& boggle);
void show_computer_words(Boggle& boggle);
/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    clearConsole();
    boggle.reset();
    string word;
    boggle.load_english_word();

    if (yesOrNo("do you wnat to gernrate a random board")){
        boggle.create_custom_board("");
    }else{
        string chosen_letters = get_chosen_letters();
        boggle.create_custom_board(chosen_letters);
    }
    cout << "it is your turn!" << endl;

    while (true){
    show_board(boggle);
    cout << "Your words (" << boggle.get_human_words().size() << "): ";
    show_human_words(boggle);
    show_human_score(boggle);

    word = get_word_from_user(boggle);

    if (word.empty()){
        break;
    }

    string check_result = boggle.check_word(word);

    if (check_result != word) {
       cout << check_result << endl;
    }

    else if(boggle.search_human_word_in_board(word)){
        cout << "You found a new word!: " << word << endl;
    }

    else{
        cout << "That word can't be formed on this board." << endl;
    }

    }

    cout << "It's my turn!" << endl;
    boggle.search_computer_word_in_board();
    cout << "My words" << "(" << boggle.get_computer_words().size() << "): ";
    show_computer_words(boggle);
    show_computer_score(boggle);
    cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!";


}

// showing the board in console for the player
void show_board(Boggle& boggle){

    for (int row = 0; row < boggle.BOARD_SIZE; row++){
        for (int col = 0; col < boggle.BOARD_SIZE; col++){
            cout << boggle.board[row][col];
        }
        cout << endl;
    }
    cout << endl;
}

// taking the 16 letters from the user and verify that the letters is in alpahpet using is_vlaid_letter function and the length of the string is 16
string get_chosen_letters(){
    string chosen_letters;

    do{
        cout << "please type in 16 valid english letters: "<< endl;
        getline(cin, chosen_letters);
    } while (!is_valid_letter(chosen_letters) || chosen_letters.length() != 16);
    return chosen_letters;
}

// verify that the letters is in alpahpet
bool is_valid_letter(string chosen_letters){
    for (char letter: chosen_letters){
        if (!isalpha(letter)){
            return false;
        }
    }
    return true;

}


// taking the word from userz
string get_word_from_user(Boggle& boggle){
    string word;
    cout << "Type a word (or press Enter to end your turn): ";
    getline(cin, word);
    word = toUpperCase(word);
    return word;
}



// Display human score in consloe
void show_human_score(Boggle& boggle){
    int human_score = boggle.get_human_score();
    cout << "Your Score: (" << human_score << ")" << endl;
}

// Display computer Score in Console
void show_computer_score(Boggle& boggle){
    int computer_score = boggle.get_computer_score();
    cout << "My Score: (" << computer_score << ")" << endl;
}

void show_human_words(Boggle& boggle){
    Set<string> human_words = boggle.get_human_words();
    cout << "{ ";

    for (string word : human_words){
        cout << '"' << word << '"' << ",";
    }
    cout << "}" << endl;
}


void show_computer_words(Boggle& boggle){
    Set<string> computer_words = boggle.get_computer_words();
    cout << "{ ";

    for (string word : computer_words){
        cout << '"' << word << '"' << ",";

    }
      cout << "}" << endl;
}






/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}


