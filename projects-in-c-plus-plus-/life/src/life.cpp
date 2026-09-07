// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

///Users/abdulrahmanhendieh/life/res/fish.txt
///Users/abdulrahmanhendieh/life/res/simple.txt

void welcome(Grid<char>& bacteriaArray);
void moveToGrid(std::ifstream &chosenFile, Grid<char> &bacteriaArray, int height, int width);
void drawGame(Grid<char> &bacteriaArray);
int checknighbors(int row, int column, Grid<char> &bacteriaArray);
void nextGeneration(Grid<char> &bacteriaArray);
void decideGeneration(Grid<char> &bacteriaArray, int decidedGeneration);
void userMenu(Grid<char> &bacteriaArray);

int main(){

    Grid<char> bacteriaArray;

    welcome(bacteriaArray);

    userMenu(bacteriaArray);

    return 0;
}

void welcome(Grid<char>& bacteriaArray){

    int height;
    int width;
    std::string fileName;

    std::cout << " Welcome to the TDDD86 Game of Life " << std::endl;
    std::cout << "Cells (X) live and die by the following rules:" << std::endl;
    std::cout << "- A cell with 1 or fewer neighbours dies." << std::endl;
    std::cout << "- Locations with 2 neighbours remain stable." << std::endl;
    std::cout << "- Locations with 3 neighbours will create life." << std::endl;
    std::cout << "- A cell with 4 or more neighbours dies." << std::endl;
    std::cout << "Please enter the file Name: ";

    std::cin >> fileName;

    std::ifstream chosenFile(fileName);

    chosenFile >> height >> width;

    bacteriaArray.resize(height, width);

    moveToGrid(chosenFile, bacteriaArray, height, width);

    std::cout << std::endl;

}


void moveToGrid(std::ifstream &chosenFile, Grid<char> &bacteriaArray, int height, int width){


    for (int row = 0; row < height; row++) {

        for (int column = 0; column < width; column++) {

            chosenFile >> bacteriaArray[row][column];
        }
    }

    chosenFile.close();
}



void drawGame(Grid<char> &bacteriaArray){

    for (int row = 0; row < bacteriaArray.numRows(); row++){

        for (int column = 0; column < bacteriaArray.numCols(); column++){

            std::cout << bacteriaArray[row][column];
        }

        std::cout << std::endl;
    }
}



int checknighbors(int row, int column, Grid<char> &bacteriaArray){

    int nighborsCounter = 0;

    for (int i = -1; i <= 1; i++){

        for (int j = -1; j <= 1; j++){

            if (i == 0 && j == 0){

                continue;
            }

            int nighborRow = row + i;
            int nighborColumn = column + j;

            if (bacteriaArray.inBounds(nighborRow, nighborColumn)){

                if (bacteriaArray.get(nighborRow, nighborColumn) == 'X'){

                    nighborsCounter++;
                }
            }
        }
    }

    return nighborsCounter;
}

void nextGeneration(Grid<char> &bacteriaArray){

    Grid<char> tempArray;

    tempArray.resize(bacteriaArray.numRows(), bacteriaArray.numCols());

    for (int row = 0; row < bacteriaArray.numRows(); row++){

        for (int column = 0; column < bacteriaArray.numCols(); column++){

            int neighbors = checknighbors(row, column, bacteriaArray);

            if (bacteriaArray.get(row, column) == 'X'){

                if (neighbors <= 1 || neighbors >= 4){

                    tempArray.set(row, column, '-');
                }

                else{

                    tempArray.set(row, column, 'X');
                }
            }

            else if (bacteriaArray.get(row, column) == '-'){

                if (neighbors == 3){

                    tempArray.set(row, column, 'X');
                }

                else{

                    tempArray.set(row, column, '-');
                }
            }
        }
    }

    bacteriaArray = tempArray;
}



void decideGeneration(Grid<char> &bacteriaArray, int decidedGeneration){

    std::cout << "Generation: 0" << std::endl;
    drawGame(bacteriaArray);

    pause(100);

    for (int i = 1; i <= decidedGeneration; i++){

        nextGeneration(bacteriaArray);
        pause(100);
        clearConsole();
        std::cout << "Generation Number: " << i << std::endl;
        drawGame(bacteriaArray);
    }
}


void userMenu(Grid<char>& bacteriaArray){

    char action;

    drawGame(bacteriaArray);

    do{

        std::cout << "a)nimate, t)ick, q)uit? : ";
        std::cin >> action;

        switch (action)
        {
        case 'a':

            decideGeneration(bacteriaArray, 20);

            break;
        case 't':

            decideGeneration(bacteriaArray, 1);

            break;

        case 'q':

            clearConsole();
            std::cout << "Have a nice Life!" << std::endl;
            return;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

    } while (action != 'q');
}
