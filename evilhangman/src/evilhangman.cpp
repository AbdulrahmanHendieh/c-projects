#include <iostream>
#include <set>
#include <fstream>
#include <map>
#include <tuple>

using namespace std;



bool check_existing_word_length(int word_length, map<int, set<string>>& words_group_by_length);
int get_word_length(map<int, set<string>>& words_group_by_length);
map<int, set<string>> dictMapContainer();
map<int, set<string>> dictMapContainer();
bool answer_show_word_list();


const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
set<string> dictContainer();
map<int, set<string>> dictMapContainer();

int main() {
    cout << "Welcome to Hangman." << endl;
    std::cout << "C++ version: " << __cplusplus << std::endl;
    return 0;
}


set<string> dictContainer(){

    string filePath = "/Users/abdulrahmanhendieh/Kurser/tddd86/projects/evilhangman/res/dictionary.txt";
    string word;
    fstream dictFile(filePath);
    set<string> wordContainer;

    while (dictFile >> word){
        wordContainer.insert(word);
    }
    return wordContainer;
}

map<int, set<string>> dictMapContainer(){

    set<string> wordContainer = dictContainer();
    map<int, set<string>> wordMapContainer;

    for (const string& word : wordContainer){


        int wordLength = word.length();
        wordMapContainer[wordLength].insert(word);

    }
    return wordMapContainer;
}


int get_word_length(map<int, set<string>>& words_group_by_length){

    int word_length;
    cout << "Please choose a word length: ";
    cin >> word_length;
    bool word_length_exist = check_existing_word_length(word_length, words_group_by_length);

    while (!word_length_exist){
        cout << "No words found of that length. Try again: ";
        cin >> word_length;
        word_length_exist = check_existing_word_length(word_length, words_group_by_length);

    }

    return word_length;

}

bool check_existing_word_length(int word_length, map<int, set<string>>& words_group_by_length){
    auto key = words_group_by_length.find(word_length);

    if (key != words_group_by_length.end()){
        return true;
    }
    return false;
}



int get_number_guessing(){

    int guesses;
    cout << "How many gusses would you like: ";
    cin >> guesses;

    while (guesses <= 0){
        cout << "The number og gussess shall be more than 0, please try again: ";
        cin >> guesses;

    }
    return guesses;
}

bool answer_show_word_list(){
    char choice;
    cout << "Would you like to see hoe many word left after each guess? a; yes, b; no: ";

    while(true){
    cin >> choice;

    switch (choice) {
    case 'a':
    case 'A':
        return true;
    case 'b':
    case 'B':
        return false;
    default:
        cout<< "please choose beteen a and b options try again: ";
        break;

    }
    }

}







