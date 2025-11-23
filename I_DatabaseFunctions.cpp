/***************************************************************************
*                                                                          *
***************************************************************************/
//Include header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "I_2048.h"

//***************INITIALIZE GRID******************
/**This function intializes the grid to begining values
Parameters: grid[][MAX_COL] is the grid of tiles which will be initialized
*/
void initializeGrid(Tiles grid[][MAX_COL]){
    //Assign each tile in the grid to a value of 0, and their image to nullptr
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            grid[row][col].value = 0;
            grid[row][col].image = nullptr;
        }
    }
}
//***************NEW TILE FUNCTIONS***************
/** This function decides if the new tile will be a 2 or a 4
Returns: 2 or 4 based on chance
*/
int randomTileValue(){
    //assign that random index the value of 2 or 4(10%)
    //generate a random number between 0 to 10
    int ichance = 0;

    ichance = rand() % 9 + 1;

    if (ichance > 1){
        ichance = 2;
    }
    else{
        ichance = 4;
    }
    return ichance;
}
/** This function generates a random tile by getting a random index in the grid
Parameters: grid[][MAX_COL] is the grid of tiles which will be accessed
Returns: 0
*/
int generateRandomTile(Tiles grid[][MAX_COL]){
    //Get a random index in the grid
    int randRow = rand() % 4;
    int randCol = rand() % 4;

    //Set number of open tiles to 16
    int openTiles = 16;

    //Check how many open tiles their are to prevent an infinite loop from occuring.
    for (int r = 0; r < MAX_ROW; r++){
        for (int c = 0; c < MAX_COL; c++){
            if (grid[r][c].value > 0){
                openTiles--;
            }
        }
        printf("\n");
    }
    //If no open tiles, no tile should be generated
    if (openTiles == 0){
        return 0;
    }

    //Get a new random index/spot on the grid as long as the tile is not open(has a value of 0)
    while (grid[randRow][randCol].value > 0){
        //get a random tile location
        randRow = rand() % 4; //(max-min) + min
        randCol = rand() % 4; //(max-min) + min
    }

    //Set the random tile to a value of 2 or 4
    grid[randRow][randCol].value = randomTileValue();
    /*printf("Row: %d Col: %d\n", randRow, randCol);
    for (int r = 0; r < MAX_ROW; r++){
        for (int c = 0; c < MAX_COL; c++){
            printf("%d ", grid[r][c].value);
        }
        printf("\n");
    }*/
    return 0;

}
//***************MOVEMENT FUNCTIONS***************
/** This function shifts all tiles up as much as possible with respect to rules of the game.
Parameters: grid[][Max_COL] is the grid of tiles which will be updated.
*/
void moveTilesUp(Tiles grid[][MAX_COL]){
    //Declare and initialize rowholder
    int rowholder = 0;

    //Iterate through each column and shift all rows within each column.
    for (int col = 0; col < MAX_COL; col++){
        //rowholder allows function to hold the row where no tile has yet been shifted.
        rowholder = 0;
        for (int row = 0; row < MAX_ROW; row++){
            //If a tile has a value > 0 then we must shift it up.
            if (grid[row][col].value != 0){
                //Only change position of tiles if rowholder != row otherwise nothing would change since it will reset the value to 0
                if (rowholder != row){
                    //shift the tile's value to the rowholder.
                    grid[rowholder][col].value = grid[row][col].value;
                    //reset the tiles value to 0.
                    grid[row][col].value = 0;
                }
                //move on to the next row
                rowholder++;
            }
        }
    }
}
/** This function shifts all tiles down as much as possible with respect to rules of the game.
Parameters: grid[][Max_COL] is the grid of tiles which will be updated.
*/
void moveTilesDown(Tiles grid[][MAX_COL]){
    //Declare and initialize rowholder
    int rowholder = 0;

    //Iterate through each column and shift all rows within each column from bottom to top
    for (int col = 0; col < MAX_COL; col++){
        //Start from last row
        rowholder = MAX_ROW - 1;
        for (int row = MAX_ROW - 1; row >= 0; row--){
            //If a tile has a value > 0 then we must shift down
            if (grid[row][col].value != 0){
                //Only change position of tiles if rowholder != row otherwise nothing would change since it will reset the value to 0
                if (rowholder != row){
                    //shift the tile's value to rowholder
                    grid[rowholder][col].value = grid[row][col].value;
                    //reset the tiles value to 0
                    grid[row][col].value = 0;
                }
                //move onto next row
                rowholder--;
            }
        }
    }
}
/** This function shifts all tiles to the left as much as possible with respect to rules of the game.
Parameters: grid[][Max_COL] is the grid of tiles which will be updated.
*/
void moveTilesLeft(Tiles grid[][MAX_COL]){
    //Declare and initialize colholder
    int colholder = 0;

    //Iterate through each row and shift all columns in the same row
    for (int row = 0; row < MAX_ROW; row++){
        colholder = 0;
        for (int col = 0; col < MAX_COL; col++){
            //If a tile has a value > 0, we must shift left.
            if (grid[row][col].value != 0){
                //Only change position of tiles if colholder != col otherwise nothing would change since it will reset the value to 0
                if (colholder != col){
                    //Shift tile's value to colholder
                    grid[row][colholder].value = grid[row][col].value;
                    //Rest the tiles value to 0
                    grid[row][col].value = 0;
                }
                //Move to the next column
                colholder++;
            }
        }
    }
}
/** This function shifts all tiles to the right as much as possible with respect to rules of the game.
Parameters: grid[][Max_COL] is the grid of tiles which will be updated.
*/
void moveTilesRight(Tiles grid[][MAX_COL]){
    //Declare and initialize colholder
    int colholder = 0;

    //Iterate through each row and shift all columns in the same row
    for (int row = 0; row < MAX_ROW; row++){
        //Start from first row
        colholder = MAX_COL - 1;
        //Start from last column
        for (int col = MAX_COL - 1; col >= 0; col--){
            //If a tile has a value > 0 we must shift right
            if (grid[row][col].value != 0){
                //Only change position of tiles if colholder != col otherwise nothing would change since it will reset the value to 0
                if (colholder != col){
                    //Shift tiles to colholder
                    grid[row][colholder].value = grid[row][col].value;
                    //Reset tiles values
                    grid[row][col].value = 0;
                }
                //Move onto next column
                colholder--;
            }
        }
    }
}

int checkGrids(Tiles grid[][MAX_COL], int oldGrid[][MAX_COL], bool &checkSameGrid){
    //check whether the grid changed to determine if a new tile must be generated
    checkSameGrid = true;

    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            if (oldGrid[row][col] != grid[row][col].value){
                checkSameGrid = false;
                return 0;
            }
        }
    }

    return 0;
}
/** This function merges two adjacent tiles if they have the same value.
Parameters: grid[][Max_COL] is the grid of tiles which will be updated.
score is passed by reference in order to update the player's score
*/
void mergeTilesLeft(Tiles grid[][MAX_COL], int &score){
    //Iterate through the 2D array
    for (int row = 0; row < MAX_ROW; row++){
        //Iterate till column index 2 to avoid accesing elements outside of the array
        for (int col = 0; col < MAX_COL - 1; col++){
            if (grid[row][col].value == grid[row][col + 1].value){
                //Merge tiles may not be needed. code seems to work without it.
                //Double the value of the tile closets to the direction of movement
                grid[row][col].value *= 2;

                //Update score value
                score += grid[row][col].value;

                //Reset other tile
                grid[row][col + 1].value = 0;
            }
        }
    }
}
/** This function merges two adjacent tiles if they have the same value.
Parameters: grid[][Max_COL] is the grid of tiles which will be updated.
score is passed by reference in order to update the player's score
*/
void mergeTilesRight(Tiles grid[][MAX_COL], int &score){
    //Iterate through the 2D array
    //Start from first row
    for (int row = 0; row < MAX_ROW; row++){
        //Start from last column iterate till the column index 1 to avoid accessing elemnts outside the array
        for (int col = MAX_COL - 1; col > 0; col--){
            if (grid[row][col].value == grid[row][col - 1].value){
                //Change the value
                grid[row][col].value *= 2;

                //Update score value
                score += grid[row][col].value;

                //Reset other tile
                grid[row][col - 1].value = 0;
            }
        }
    }
}
/** This function merges two adjacent tiles if they have the same value.
Parameters: grid[][Max_COL] is the database of tiles in our grid which will be updated.
score is passed by reference in order to update the player's score
*/
void mergeTilesUp(Tiles grid[][MAX_COL], int &score){
    //Iteretae through the 2D array.
    //Iterate through the rows of each columns
    for (int col = 0; col < MAX_COL; col++){
        //Iterate till row index 2 to avoid accessing elements outside the array
        for (int row = 0; row < MAX_ROW - 1; row++){
            if (grid[row][col].value == grid[row + 1][col].value){
                //Change value
                grid[row][col].value *= 2;

                //Update score value
                score += grid[row][col].value;

                //Reset other tile
                grid[row + 1][col].value = 0;
            }
        }
    }
}
/** This function merges two adjacent tiles if they have the same value.
Parameters: grid[][Max_COL] is the database of tiles in our grid which will be updated.
score is passed by reference in order to update the player's score
*/
void mergeTilesDown(Tiles grid[][MAX_COL], int &score){
    //Iterate through the the 2D array
    for (int col = 0; col < MAX_COL; col++){
        //Start from last row. Iterate till row index 1 to avoid accessing elements outside the array
        for (int row = MAX_ROW - 1; row > 0; row--){
            if (grid[row][col].value == grid[row - 1][col].value){
                //Change value
                grid[row][col].value *= 2;

                //Update score value
                score += grid[row][col].value;

                //Reset value
                grid[row - 1][col].value = 0;
            }
        }
    }
}
