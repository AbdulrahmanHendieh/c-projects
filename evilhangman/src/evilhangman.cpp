// liuId: abdhe895
#include <iostream>
#include <set>
#include <fstream>
#include <map>
#include <tuple>
#include <cctype>

using namespace std;

// Reads the dictionary file and categorizes words by their length
map<int, vector<string>> get_english_word_devided_by_length();

// Prompts the user for a word length and verifies that matching words exist
int get_word_length(const map<int, vector<string>>& english_word_devided_by_length);

// Template function for safe user input handling and stream buffer clearing
template <typename T>
T controll_input(const string& prompt);

// Prompts the user for the number of guesses (must be greater than 0)
int get_number_guesses();

// Asks the user whether they want to display the remaining word list
bool want_to_see_word_list();

// Prompts for a letter input and validates that it is a single unused letter
char get_guessed_letter(const set<char>& marked_letters);

// Retrieves the list of words matching the selected word length
vector<string> get_word_list_of_choosen_length(int chosen_word_length, const map<int, vector<string>>& english_word_devided_by_length);

// Partitions current words into word families based on the guessed letter's positions
map<string, vector<string>> get_word_families(char guessed_letter,const string& current_pattern, const vector<string>& word_list);

// Finds and returns the word family that contains the largest number of words
pair<string, vector<string>> get_largest_word_familliy(const map<string, vector<string>>& word_families);

// Asks the user if they want to play another game round
bool play_again();

// Displays current game state including guessed letters, remaining guesses, and pattern
void game_status(string& current_pattern, int number_guesses, const vector<string> word_list, bool show_word_list,const set<char>& marked_letters);

// Main game loop running until the player wins or runs out of guesses
void game_loop(const map<int, vector<string>>& english_word_devided_by_length);


const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";





// Main function: Loads the dictionary once and manages game replays
int main(){
    map<int, vector<string>> english_word_devided_by_length = get_english_word_devided_by_length();
    cout << "welcome" << endl;
    bool keep_playing = true;

    while (keep_playing){
        game_loop(english_word_devided_by_length);
        keep_playing = play_again();
    }


}


map<int, vector<string>> get_english_word_devided_by_length(){
    string filename = "/Users/abdulrahmanhendieh/Kurser/tddd86/projects/evilhangman/res/di.txt";
    ifstream english_dict(filename);
    string word;
    map<int, vector<string>> english_word_devided_by_length;

    while (english_dict >> word){
        english_word_devided_by_length[word.length()].push_back(word);

    }
    english_dict.close();
    return english_word_devided_by_length;
}



int get_word_length(const map<int, vector<string>>& english_word_devided_by_length){

    while (true){
        int word_length = controll_input<int>("Please choose a word length?: ");
        auto key = english_word_devided_by_length.find(word_length);
        if (key != english_word_devided_by_length.end()){
            return word_length;
        }
        cout << "There are no words with length " << word_length << ". Try again: ";
    }
}

int get_number_guesses(){

    while (true){

        int number_guesses = controll_input<int>("How many guesses would you like to have: ");

        if (number_guesses > 0){
            return number_guesses;
        }
        cout << "The number number should be greater than 0" << endl ;

    }
}


bool want_to_see_word_list(){

    while (true){
        char action = controll_input<char>("Do you like to see a word list afret guessing, (a: yes, b: no): ");
        switch (action) {
        case 'a':
        case 'A':
            return true;
        case 'b':
        case 'B':
            return false;
        default:
            cout << "invalid input";
            break;
        }
    }
}

char get_guessed_letter(const set<char>& marked_letters){

    while (true){
        string input = controll_input<string>("please guess a letter: ");

        if (input.length() > 1){
        cout << "Invalid input, please enter a letter from the alphabet." << endl;

        }

        else{
            char guessed_letter = tolower(input[0]);

            if (ALPHABET.find(guessed_letter) == string::npos) {
            cout << "Invalid input, please enter a letter from the alphabet." << endl;
        }
            else if (marked_letters.count(guessed_letter) > 0) {
            cout << "The letter: " << guessed_letter << " has already been used." << endl;
        }
            else{
                return guessed_letter;
        }
        }
    }
}

vector<string> get_word_list_of_choosen_length(int chosen_word_length, const map<int, vector<string>>& english_word_devided_by_length){
    return english_word_devided_by_length.at(chosen_word_length);

}


map<string, vector<string>> get_word_families(char guessed_letter, const string& current_pattern, const vector<string>& word_list){
    map<string, vector<string>> word_families;

    for (string word: word_list){
        string pattern = current_pattern;

        for (size_t i = 0; i < word.length(); i++){

            if(word[i] == guessed_letter){
                pattern[i] = guessed_letter;
            }
        }

        word_families[pattern].push_back(word);

    }
    return word_families;
}


pair<string, vector<string>> get_largest_word_familliy(const map<string, vector<string>>& word_families){
    vector<string> largest_word_familliy;
    size_t max_size = 0;
    string max_pattern = "";
    for (const auto& [pattern, word_familliy]: word_families){

        if (word_familliy.size() > max_size){
            max_size = word_familliy.size();
            max_pattern = pattern;
        }
    }
    largest_word_familliy = word_families.at(max_pattern);
    return {max_pattern, largest_word_familliy};
}


bool play_again(){

    while (true){
        char action = controll_input<char>("Do you like to play again? (a: yes, b: no) ");
        switch (action) {
        case 'a':
        case 'A':
            return true;
        case 'b':
        case 'B':
            return false;
        default:
            cout << "invalid input";
            break;
        }
    }
}

template <typename T>
T controll_input(const string& prompt){
    T input;
    cout << prompt;
    while (!(cin >> input)){
        cout << "invalid input please try again: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return input;
}

void game_status(string& current_pattern, int number_guesses, const vector<string> word_list, bool show_word_list,const set<char>& marked_letters){
    cout << "------------------------------------------" << endl;

    cout << "Guessed letters: (";
    for (const char& letter: marked_letters){
        cout << letter << ", ";
    }
    cout << ")" << endl;

    cout << "number guesses: " << number_guesses << endl;

    cout << "current pattern: " << current_pattern << endl;

    if (show_word_list){
        cout << "word list: ";
        for (const string& word: word_list){
            cout << word << ", ";
        }
        cout << endl;
    }

}

void game_loop(const map<int, vector<string>>& english_word_devided_by_length){

    int word_length = get_word_length(english_word_devided_by_length);
    string current_pattern(word_length, '-');
    int number_guesses = get_number_guesses();
    bool show_word_list = want_to_see_word_list();
    vector<string> word_list = get_word_list_of_choosen_length(word_length, english_word_devided_by_length);
    set<char> marked_letters;
    map<string, vector<string>> word_families;


    while (current_pattern.find('-') != string::npos && number_guesses > 0){
        game_status(current_pattern, number_guesses, word_list, show_word_list, marked_letters);
        char guessed_letter = get_guessed_letter(marked_letters);
        marked_letters.insert(guessed_letter);
        word_families = get_word_families(guessed_letter, current_pattern, word_list);
        auto [max_pattern, largest_family] = get_largest_word_familliy(word_families);
        word_list = largest_family;


        if (current_pattern == max_pattern){
            cout << "The word do not conatin: " << guessed_letter << endl;
            number_guesses--;

        }else{
            cout << "the word have att least one: " << guessed_letter << endl;
            current_pattern = max_pattern;

        }
    }

    if (current_pattern.find('-') == string::npos) {
        cout << " You won! The word was: " << current_pattern << endl;
    } else {
        cout << "Sorry you ran out of guesses! The word was: " << word_list[0] << endl;
    }
}












































