#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
using namespace std;


void printWordChain(stack<string>& wordStack);
void wordChain(string firstWord, string secWord);
set<string> englishWordContainer();

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    string firstWord;
    string secWord;

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    cin  >> firstWord >> secWord;

    wordChain(firstWord, secWord);

    return 0;
}

void wordChain(string firstWord, string secWord){

    queue< stack< string >> wordsQueue;
    stack< string> wordsStack;
    set <string> markedWord;

    wordsStack.push(firstWord);
    wordsQueue.push(wordsStack);
    markedWord.insert(firstWord);
    set<string> englishDict = englishWordContainer();


    while (!wordsQueue.empty()){

        stack <string> currentStack = wordsQueue.front();
        wordsQueue.pop();
        string currentWord = currentStack.top();

        if (currentWord == secWord){

            printWordChain(currentStack);

            return;
        }
        else{

            for (size_t i = 0; i < currentWord.length(); i++){

                for (int j = 0; j < 26; j++){

                    string neighborWord = currentWord;

                    if (currentWord[i] == ALPHABET[j]){
                        continue;
                    }

                    neighborWord[i] = ALPHABET[j];



                    if (!englishDict.count(neighborWord) || markedWord.count(neighborWord)){

                        continue;
                    }


                    else{

                        markedWord.insert(neighborWord);
                        stack<string> currentStackCopy = currentStack;
                        currentStackCopy.push(neighborWord);
                        wordsQueue.push(currentStackCopy);

                    }
                }
            }
        }
    }
}


void printWordChain(stack<string>& wordStack){

    stack <string> reverseStack;

    while (!wordStack.empty()){

        string word = wordStack.top();
        wordStack.pop();

        reverseStack.push(word);

    }

    while (!reverseStack.empty()){

        string word = reverseStack.top();
        reverseStack.pop();

        if (reverseStack.size() >= 1){

            cout << word << " " <<"->" << " ";

        }

        else{

            cout << word;

        }
    }
}

set<string> englishWordContainer(){

    ifstream file("/Users/abdulrahmanhendieh/Kurser/TDDD86/labb2/wordchain/res/dictionary.txt");
    string word;
    set <string> dict;

    while (file >> word){

        dict.insert(word);
    }

    return dict;
}







