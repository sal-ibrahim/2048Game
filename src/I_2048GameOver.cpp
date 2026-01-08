/***************************************************************************
*                                                                          *
***************************************************************************/
//Include header files
#include <stdio.h>
#include "I_2048.h"

//***************GAME OVER CONDITIONS***************
/** This functions checks for possible horizontal merges
Parameters: grid[][Max_COL] is the grid of tiles in our grid which will be accesed.
*/
int checkHzMoves(Tiles grid[][MAX_COL]){
    //Traverse through elements in the grid
    for (int row = 0; row < MAX_ROW; row++){
        //Avoid accesing elements outside the grid
        for (int col = 0; col < MAX_COL - 1; col++){
            if (grid[row][col].value == grid[row][col + 1].value){
                //There are possible moves to be made
                return 1;
            }
        }
    }
    //No possible moves
    return 0;
}
/** This functions checks possible vertical merges
Parameters: grid[][Max_COL] is the grid of tiles in our grid which will be accesed.
*/
int checkVrtMoves(Tiles grid[][MAX_COL]){
    //Traverse through the elements in the grid
    for (int col = 0; col < MAX_COL; col++){
        //Avoid accesing elements outside the grid
        for (int row = 0; row < MAX_ROW - 1; row++){
            if (grid[row][col].value == grid[row + 1][col].value){
                //There are possible moves to be made
                return 1;
            }
        }
    }
    //No possible moves
    return 0;
}
/** This functions checks for any open tiles.
Parameters: grid[][Max_COL] is the grid of tiles in our grid which will be accesed.
*/
int checkOpenTiles(Tiles grid[][MAX_COL]){
    //Traverse through elements in the grid
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            if (grid[row][col].value == 0){
                //There is an open tile
                return 1;
            }
        }
    }
    //No open tiles
    return 0;
}
/** This functions checks if any tile has reached the value 2048
Parameters: grid[][Max_COL] is the grid of tiles in our grid which will be accesed.
*/
bool checkWin(Tiles grid[][MAX_COL]){
    //traverse through elements in the grid.
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            //check if any tile has a value of 2048
            if (grid[row][col].value == 2048){
                //they have won the game
                return true;
            }
        }
    }
    //they have not won the game
    return false;
}

//***************GAME OVER CHECK***************
/** This functions checks whether the game can continue
Parameters: grid[][Max_COL] is the grid of tiles in our grid which will be accesed.
Returns: false if the game can continue, true if the game ends.
*/
bool checkGameOver(Tiles grid[][MAX_COL]){
    //variables
    int total = 0;

    //add return values
    total += checkHzMoves(grid) + checkVrtMoves(grid) + checkOpenTiles(grid);
    printf("\n%d %d %d\n", checkHzMoves(grid), checkVrtMoves(grid), checkOpenTiles(grid));

    //if empty tiles and possible merges are present, no game over.
    if (total >= 1){
        return false;
    }
    //if no empty tiles and no possible merges are present. Game over!
    else{
        return true;
    }
}
