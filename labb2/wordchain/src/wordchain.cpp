#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
using namespace std;


set<string> englishWordContainer();
void printWordChain(stack<string> wordChain);
void wordChain(string firstWord, string secWord, set<string>& englishWordDict);

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

int main(){
    string firstWord;
    string secWord;
    set<string> englishWordDict = englishWordContainer();

    cout << "Welcome to TDDD86 Word Chain." << endl
    << "If you give me two English words, I will transform the" << endl
    << "first into the second by changing one letter at a time." << endl << endl;

    cout<< "Please type two words: ";
    cin >> firstWord >> secWord;

    wordChain(firstWord, secWord, englishWordDict);

}


void wordChain(string firstWord, string secWord, set<string>& englishWordDict){

    queue<stack<string>> wordChains;
    set<string> markedWord;
    stack<string> wordChain;
    wordChain.push(firstWord);
    wordChains.push(wordChain);
    markedWord.insert(firstWord);

    while (!wordChains.empty()){
        stack<string> currentStack = wordChains.front();
        wordChains.pop();
        string currentWord = currentStack.top();

        if (currentWord == secWord){
            printWordChain(currentStack);
            return;
        }

        for (int i = 0; i < currentWord.length(); i++){
            string tempWord = currentWord;
            for (char letter: ALPHABET){
                tempWord[i] = letter;

                if (markedWord.count(tempWord) || !englishWordDict.count(tempWord)){
                    continue;
                }

                markedWord.insert(tempWord);
                stack<string> wordChainCopy = currentStack;
                wordChainCopy.push(tempWord);
                wordChains.push(wordChainCopy);
            }
        }

    }

}


set<string> englishWordContainer(){
    set<string> englishWordSet;
    string fileName = "/Users/abdulrahmanhendieh/Kurser/tddd86/projects/wordchain/res/dictionary.txt";
    ifstream englishDict(fileName);
    string word;

    while(getline(englishDict, word)){
        englishWordSet.insert(word);
    }

    return englishWordSet;
}


void printWordChain(stack<string> wordChain){
    cout << "Chain from data back to code:"<< endl;
    while (!wordChain.empty()){
        if (wordChain.size() == 1){
            cout << wordChain.top()<< endl;
            wordChain.pop();
            break;
        }
        cout << wordChain.top() << " " << "->"<< " ";
        wordChain.pop();

    }
    cout<< "Have a nice day.";
}

