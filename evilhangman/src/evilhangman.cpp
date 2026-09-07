#include <iostream>
#include <set>
#include <fstream>
#include <map>

using namespace std;



const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
set<string> dictContainer();
map<int, set<string>> dictMapContainer();

int main() {
    cout << "Welcome to Hangman." << endl;

    map<int, set<string>> wordMapContainer = dictMapContainer();

    set<string> wordLengthFour = wordMapContainer[4];


    for (const string& word: wordLengthFour){
        cout << word << endl;
    }







    return 0;
}


set<string> dictContainer(){

    string filePath = "/Users/abdulrahmanhendieh/Kurser/tddd86/c++ projects/evilhangman/res/dictionary.txt";
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






