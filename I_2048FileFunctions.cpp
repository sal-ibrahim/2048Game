/***************************************************************************
* This file works with text files                                          *
***************************************************************************/
#include <stdio.h>
#include "I_2048.h"

/** This function saves a new game.
Parameters: grid[][MAX_COL] is the grid of tiles in which we will used to save.
Returns: 0 if good, 1 if file did not open correctly
*/
int saveNewGame(Tiles grid[][MAX_COL], char player[50], int iScore){
    //Create file pointer
    FILE *fptr;

    //Open file for writing
    fptr = fopen("GridData.txt", "a");

    //Check if file opened correctly
    if (fptr == NULL){
        printf("File did not open correctly.\n");
        return 1;
    }

    //Write username to file
    fprintf(fptr, "%s\n", player);

    //Write all tiles into the text file
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            fprintf(fptr, "%d ", grid[row][col].value);
        }
        fprintf(fptr, "\n");
    }
    //Write the player's score
    fprintf(fptr, "%d\n", iScore);

    //Close file
    fclose(fptr);

    return 0;
}

/**This functions saves a game that has been resumed
Parameters: grid[][MAX_COL] is the grid of tiles in which we will used save.
    playerInfo[] is the struct of player information that will be used to save.
    iScore saves a copy of the player's score
    index saves a copy of the player's resumed player choice
    numberPlayers determines how many players in the database
Returns: 0 if good, 1 if file did not open correctly
*/
int saveResumedGame(Tiles grid[][MAX_COL], Player playerInfo[], int iScore, int index, int numberPlayers){
    //Update the strucutre
    //Only need to update score and grid for the resumed game
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            grid[row][col].value = playerInfo[index].gridOfTiles[row][col];
        }
    }
    //Update score
    playerInfo[index].score = iScore;

    //Create file pointer
    FILE *fptr;

    //Open file for writing
    fptr = fopen("GridData.txt", "w");

    //Check if file opened correctly
    if (fptr == NULL){
        printf("File did not open correctly.\n");
        return 1;
    }

    //Write all players info.
    for (int i = 0; i < numberPlayers; i++){
        //Write username to file
        fprintf(fptr, "%s\n", playerInfo[i].userName);

        //Wite all tiles into the text file
        for (int row = 0; row < MAX_ROW; row++){
            for (int col = 0; col < MAX_COL; col++){
                fprintf(fptr, "%d ", playerInfo[i].gridOfTiles[row][col]);
            }
            fprintf(fptr, "\n");
        }

        //Write the player's score
        fprintf(fptr, "%d\n", playerInfo[i].score);
    }

    //close file
    fclose(fptr);

    return 0;

}



/** This function loads the previous game of the user so that they can continue their previous game.
Parameters: Tiles grid[][MAX_COL] is the database of tiles in which we will update
    playerInfo[] is the struct of player information that will be used to save.
    score is used to initalize player's score
    counter saves of the numebr of players.
Returns: 0 if good 1 if file did not open correctly

*/
int loadSavedGame(Player playerInfo[], Tiles grid[][MAX_COL], int counter, int &iChoice, int &score){
    //initialize choice to an invalid choice
    iChoice = -1;
    //display options
    for (int i = 0; i < counter; i++){
        printf("(%d): %s\n", i, playerInfo[i].userName);
    }

    //ask the user for their option
    while (iChoice >= counter || iChoice < 0){
        printf("Select the saved game to play: ");
        scanf("%d", &iChoice);
    }

    //initialize the grid to the players grid of choice
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            grid[row][col].value = playerInfo[iChoice].gridOfTiles[row][col];
        }
    }

    score = playerInfo[iChoice].score;

    return 0;
}

/** This function loads all player data and displays them on the screeen so the user will choose.
Parameters: playerInfo[]
Returns: 0 if good 1 if file did not open correctly
*/
int uploadPlayers(Player playerInfo[]){
    //variables
    char player[100][50];
    int score[100];
    int i = 0;

    //create file pointer
    FILE *rd;

    //open file for reading
    rd = fopen("GridData.txt", "r");

    //check if file opened correctly
    if (rd == NULL){
        printf("File did not open correctly.\n");
        return 1;
    }

    //read in all players
    while (fscanf(rd, "%s\n", playerInfo[i].userName) != EOF){
        //then read in the tiles
        for (int row = 0; row < MAX_ROW; row++){
            for (int col = 0; col < MAX_COL; col++){
                fscanf(rd, "%d", &playerInfo[i].gridOfTiles[row][col]);
            }
            fscanf(rd, "\n");
        }
        //read in their score
        fscanf(rd, "%d\n", &playerInfo[i].score);

        i++;
    }

    return 0;
}
/**
This funciton gets the number of players\
Parameters: none
*/
int getNumOfPlayers(){
    //Variables
    char player[50];
    int points;
    int tile[4][4];
    int i = 0;

    //Create file pointer
    FILE *rd;

    //Open file for reading
    rd = fopen("GridData.txt", "r");

    //Check if file opened correctly
    if (rd == NULL){
        printf("File did not open correctly.\n");
        return 1;
    }

    //Read in all players
    while (fscanf(rd, "%s\n", player) != EOF){
        //then read in the tiles
        for (int row = 0; row < MAX_ROW; row++){
            for (int col = 0; col < MAX_COL; col++){
                fscanf(rd, "%d", &tile[row][col]);
            }
            fscanf(rd, "\n");
        }
        //Read in their score
        fscanf(rd, "%d\n", &points);

        i++;
    }

    //Return the number of players
    return i;
}
