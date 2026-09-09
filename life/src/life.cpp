// Namn: Abdulrahman Hendieh
// liuID = abdhe895

#include<iostream>
#include<grid.h>
#include<lifeutil.h>
#include<fstream>

/**
 * Displays the welcome message and rules of the Game of Life simulation.
 */
void welcome();

/**
 * Reads grid dimensions and cell data from a file to initialize the colony.
 */
void move_to_Grid(std::ifstream& chosenFile, Grid<char>& colony);

/**
 * Counts and returns the number of living neighbor cells ('X') around a specific position.
 */
int numneighbor(const Grid<char>& colony, int bacteriaPositionRow, int bacteriaPositionColumn);

/**
 * Advances the colony to its next state based on the Game of Life rules.
 */
void nextGeneration(Grid<char>& colony);

/**
 * Outputs the current state of the grid colony to the console.
 */
void drawColony(Grid<char>& colony);

/**
 * Runs an animated simulation for a specified number of generations.
 */
void runSimulation(Grid<char>& colony, int numGeneration);

/**
 * Handles the main user interface loop for stepping, animating, or quitting the simulation.
 */
void userMeny(Grid<char>& colony);



int main(){
    std::string filename;
    Grid<char> colony;

    welcome();

    std::cout << "Grid input file name? " ;
    std::cin >> filename;
    std::ifstream chosenFile(filename);


    move_to_Grid(chosenFile, colony);
    drawColony(colony);
    userMeny(colony);

}

void welcome(){

    std::cout << "Welcome to the TDDD86 Game of Life," << std::endl <<
        "a simulation of the lifecycle of a bacteria colony." << std::endl <<
        "Cells (X) live and die by the following rules:" << std::endl <<
        "- A cell with 1 or fewer neighbours dies." << std::endl <<
        "- Locations with 2 neighbours remain stable." << std:: endl <<
        "- Locations with 3 neighbours will create life." << std::endl <<
        "- A cell with 4 or more neighbours dies." << std::endl;

}

void move_to_Grid(std::ifstream& chosenFile, Grid<char>& colony){
    int colonyNumRows;
    int colonyNumColumns;

    chosenFile >> colonyNumRows >> colonyNumColumns;
    colony.resize(colonyNumRows, colonyNumColumns);

    for (int row = 0; row < colonyNumRows; row++){
        for (int column = 0; column < colonyNumColumns; column++){
            chosenFile >> colony[row][column];
        }
    }
    chosenFile.close();
}


int numneighbor(const Grid<char>& colony, int bacteriaPositionRow, int bacteriaPositionColumn){
    int counter = 0;

    for (int dr = -1; dr <= 1; dr++){
        for (int dc = -1; dc <= 1; dc++){

            if (dr == 0 && dc == 0){
                continue;
            }

            int neighborRow = bacteriaPositionRow + dr;
            int neighborColumn = bacteriaPositionColumn + dc;

            if (colony.inBounds(neighborRow, neighborColumn) && colony.get(neighborRow, neighborColumn) ==  'X'){
                counter++;
            }
        }
    }
    return counter;
}


void drawColony(Grid<char>& colony){

    for (int row = 0; row < colony.numRows(); row++){
        for (int column = 0; column < colony.numCols(); column++){

            std::cout<< colony[row][column];
        }
        std::cout<< std::endl;
    }
}



void nextGeneration(Grid<char>& colony){

    tempColony.resize(colony.numRows(), colony.numCols());

    for (int row = 0; row < colony.numRows(); row++){
        for (int column = 0; column < colony.numCols(); column++){
            int cellNeigbor = numneighbor(colony, row, column);

            if (colony.get(row, column) == 'X'){

                if (cellNeigbor <= 1 || cellNeigbor >= 4){

                    tempColony.set(row, column, '-');
                }

                else{
                    tempColony.set(row, column, 'X');
                }

            }
            if (colony.get(row, column) == '-'){

                if (cellNeigbor == 3){

                    tempColony.set(row, column, 'X');

                }
                else{
                    tempColony.set(row, column, '-');
                }
            }

        }
    }

    colony = tempColony;

}


void runSimulation(Grid<char>& colony, int numGeneration){


    for (int generation = 1; generation <= numGeneration; generation++){
        clearConsole();
        std::cout<< "generation: " << generation << std::endl;
        nextGeneration(colony);
        drawColony(colony);
        pause(100);

    }
}

void userMeny(Grid<char>& colony){
    char action;

    do{

        std::cout<< "a)nimate, t)ick, q)uit?";
        std::cin >> action;

        switch (action) {
        case 't':
            nextGeneration(colony);
            drawColony(colony);
            break;

        case 'a':
        runSimulation(colony, 20);
            break;

        case 'q':
            clearConsole();
            std::cout << "Have a nice life!";
            break;

        default:
            std::cout<< "invalid input" << std::endl;
            break;
        }
    } while(action != 'q');
}



















