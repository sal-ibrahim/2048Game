/***************************************************************************
*                                                                          *
* This program plays the game 2048 in C using allegro GUI                  *
***************************************************************************/

//include header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h> 		// for message box
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "I_2048.h"

int main(int argc, char *argv[]){
    //***************ALLEGRO SETUP REQUIREMENTS******************
    //Initialize Allegro
	initializeAllegro();

	//Declare and intialize display
	ALLEGRO_DISPLAY *display = nullptr;
	display = al_create_display(SCREEN_W, SCREEN_H);

	//Intialize fonts
	ALLEGRO_FONT *font = nullptr;
	font = al_load_ttf_font("Pixel_Font.ttf", LETTER_SIZE, 0);

	//Add event queue object
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;

    //Setup event queue
    event_queue = al_create_event_queue();

    //Check if routines worked properly
	checkSetup(display, font, event_queue);

    //Register events for our event queue
	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());

 	//Set window title
    al_set_window_title(display, "2048");

    //Create a set of images
    ALLEGRO_BITMAP *images[NUM_IMAGES];
    //Initialize images
    for (int i = 0; i < NUM_IMAGES; i++){
        images[i] = nullptr;
    }
    //Load images
    loadImages(images);

    //Check if images loaded up properly
	for (int i = 0; i < NUM_IMAGES; i++){
        if (!images[i]) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load one or more images!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_font(font);
        al_destroy_event_queue(event_queue);
     	return -1;
	 }
	}

    //*********************DECLARE / INITIALZE GRID************************
    //Seed random generator
    srand(time(0));

    //Create struct variable as a 2D array
    Tiles grid[MAX_ROW][MAX_COL];

    //intialize grid
    initializeGrid(grid);


    //Generate a random tile because the game always starts with two tiles
    generateRandomTile(grid);
    generateRandomTile(grid);


    //Declare and initialize screens
 	ALLEGRO_BITMAP *screen[5];
 	//Initialize screens
 	//Initialize images
    for (int i = 0; i < 3; i++){
        screen[i] = nullptr;
    }
 	//Load screens
 	loadScreens(screen);

 	//Check if images loaded up properly
	for (int i = 0; i < 3; i++){
        if (!screen[i]) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load one or more screens!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_font(font);
        al_destroy_event_queue(event_queue);
        for (int i = 0; i < NUM_IMAGES; i++){
            al_destroy_bitmap(images[i]);
        }
     	return -1;

        }
	}

	//***Player struct variable
	//Create a variable for the player struct
	Player playerInfo[100];


 	//****************MENU********************
    al_draw_bitmap(screen[0], 0, 0, 0);

 	al_flip_display();

 	//Variables
 	char userName[50];
 	int numPlayers = 0;
 	bool breakOutLoop = true;
 	bool newGame = true;
 	bool resumeGame = false;
 	int iChoice = 0;
 	int score = 0;

 	//get number of players
    numPlayers = getNumOfPlayers();

 	while (true){
        //Create an event and name it
        ALLEGRO_EVENT events;

        al_wait_for_event(event_queue, &events);

        //wait for an event to occur
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE || events.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {

            return 0;
      	}
      	if (events.type == ALLEGRO_EVENT_KEY_DOWN){
            switch (events.keyboard.keycode){
                //Play new game
                case ALLEGRO_KEY_P:
                    //increase the number of players
                    numPlayers++;

                    //ask the user for their user name
                    printf("Enter username: ");
                    scanf("%s", userName);

                    newGame = true;
                    resumeGame = false;
                    breakOutLoop = true;
                    break;

                //View quick manual
                case ALLEGRO_KEY_M:
                    //Display manual screen
                    al_draw_scaled_bitmap(screen[1], 0, 0, 1280, 1280, 0, 0, 1280 * 0.8, 1280 * 0.8, 0);

                    //Tell user more instrucutions on text file
                    al_draw_text(font, al_map_rgb(0, 0, 0), 512, 896, ALLEGRO_ALIGN_CENTER, "More info @ manual.txt");
                    al_flip_display();

                    //wait ten seconds
                    al_rest(10);

                    //return to menu
                    al_draw_bitmap(screen[0], 0, 0, 0);
                    al_flip_display();

                    //set all breakouts to false
                    newGame = false;
                    resumeGame = false;
                    breakOutLoop = false;
                    break;

                //Resume saved game
                case ALLEGRO_KEY_R:
                    //Display players and choice on console
                    uploadPlayers(playerInfo);
                    loadSavedGame(playerInfo, grid, numPlayers, iChoice, score);

                    //Check if use can play resumed game
                    if (!checkGameOver(grid) && !checkWin(grid)){
                        //start the game;
                        breakOutLoop = true;
                        resumeGame = true;
                        newGame = false;
                    }
                    else{
                        //Tell user they can't play
                        al_draw_text(font, al_map_rgb(0, 0, 0), 512, 0, ALLEGRO_ALIGN_CENTER, "The chosen player is not playable.");
                        al_flip_display();

                        //reinitialze grid
                        initializeGrid(grid);
                        generateRandomTile(grid);
                        generateRandomTile(grid);
                        score = 0;
                        breakOutLoop = false;
                    }
                    break;
            }
            if (breakOutLoop){
                //get out of menu
                break;
            }
      	}
 	}
    //*******************UPDATE GRID************************
    //Variables
    char PrintScore[100] = "";
    //2D array to hold old grid.
    int oldGrid[MAX_ROW][MAX_COL];
    //check if the old grid and the updated grid are the same
    bool checkSameGrid = false;

    //Setup game loop
    while (!checkGameOver(grid)){
        //Now create an event and name it
        ALLEGRO_EVENT ev;
        //Wait for an event to occur
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
      	}
      	if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch (ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    //save old grid before changes are made in order to compare the old and updated grid
                    for (int row = 0; row < MAX_ROW; row++){
                        for (int col = 0; col < MAX_COL; col++){
                            oldGrid[row][col] = grid[row][col].value;
                            printf("%d ", oldGrid[row][col]);
                        }
                        printf("\n");
                    }

                    //Move up
                    moveTilesUp(grid);
                    //Merge tiles
                    mergeTilesUp(grid, score);
                    //Move up again to fill gaps
                    moveTilesUp(grid);
                    for (int row = 0; row < MAX_ROW; row++){
                        for (int col = 0; col < MAX_COL; col++){
                            printf("%d ", grid[row][col].value);
                        }
                        printf("\n");
                    }
                    //check whether the grid changed to determine if a new tile must be generated
                    checkGrids(grid, oldGrid, checkSameGrid);

                    //Generate random tile
                    if (!checkSameGrid){
                        generateRandomTile(grid);
                    }
                    break;

                case ALLEGRO_KEY_DOWN:
                    //save old grid before changes are made in order to compare the old and updated grid
                    for (int row = 0; row < MAX_ROW; row++){
                        for (int col = 0; col < MAX_COL; col++){
                            oldGrid[row][col] = grid[row][col].value;
                        }
                    }

                    //Move down
                    moveTilesDown(grid);
                    //Merge tiles down
                    mergeTilesDown(grid, score);
                    //Move tiles down again to fill gaps
                    moveTilesDown(grid);

                    //check whether the grid changed to determine if a new tile must be generated
                    checkGrids(grid, oldGrid, checkSameGrid);

                    //Generate random tile
                    if (!checkSameGrid){
                        generateRandomTile(grid);

                    }
                    break;

                case ALLEGRO_KEY_LEFT:
                    //save old grid before changes are made in order to compare the old and updated grid
                    for (int row = 0; row < MAX_ROW; row++){
                        for (int col = 0; col < MAX_COL; col++){
                            oldGrid[row][col] = grid[row][col].value;
                        }
                    }
                    //Move left
                    moveTilesLeft(grid);
                    //Merge tiles
                    mergeTilesLeft(grid, score);
                    //Move left again to fill gaps
                    moveTilesLeft(grid);

                    //check whether the grid changed to determine if a new tile must be generated
                    checkGrids(grid, oldGrid, checkSameGrid);

                    //Generate random tile
                    if (!checkSameGrid){
                        generateRandomTile(grid);

                    }
                    break;

                case ALLEGRO_KEY_RIGHT:
                    //save old grid before changes are made in order to compare the old and updated grid
                    for (int row = 0; row < MAX_ROW; row++){
                        for (int col = 0; col < MAX_COL; col++){
                            oldGrid[row][col] = grid[row][col].value;
                        }
                    }
                    //Move right
                    moveTilesRight(grid);
                    //Merge tiles
                    mergeTilesRight(grid, score);
                    //Move right again to fill gaps
                    moveTilesRight(grid);

                    //check whether the grid changed to determine if a new tile must be generated
                    checkGrids(grid, oldGrid, checkSameGrid);

                    //Generate random tile
                    if (!checkSameGrid){
                        generateRandomTile(grid);

                    }
                    break;
            }
      	}
      	//Draw background grid
        al_draw_scaled_bitmap(screen[2], 0, 0, 1280, 1280, 0, 0, 1280 * 0.8, 1280 * 0.8, 0);

      	//Update tile images
      	updateTileImage(grid, images);

      	//Print the updated grid
      	printTiles(font, grid);

      	//Display score
      	sprintf(PrintScore, "%d", score);
        al_draw_text(font, al_map_rgb(174, 219, 230), 750, 135, ALLEGRO_ALIGN_CENTER, PrintScore);

      	//Flip the display to show the updated screen
      	al_flip_display();

      	//check if the user won
      	if (checkWin(grid)){
            al_rest(2);
            break;
      	}
    }
    //Game Over
    //If the user won(reach 2048)
    if (checkWin(grid)){
        al_rest(2);
        //Draw background grid
        al_draw_scaled_bitmap(screen[2], 0, 0, 1280, 1280, 0, 0, 1280 * 0.8, 1280 * 0.8, 0);
        //draw bitmap
        al_draw_scaled_bitmap(screen[4], 0, 0, 82, 28, 320, 448, 82 * 5, 28 * 5, 0);

        al_flip_display();

        al_rest(3);
    }
    //If the user lost
    else if (checkGameOver(grid)){
        al_rest(2);
        //Draw background grid
        al_draw_scaled_bitmap(screen[2], 0, 0, 1280, 1280, 0, 0, 1280 * 0.8, 1280 * 0.8, 0);
        //draw bitmap
        al_draw_scaled_bitmap(screen[3], 0, 0, 82, 28, 320, 448, 82 * 5, 28 * 5, 0);

        al_flip_display();

        al_rest(3);
    }

    //clean up all add ons to ensure exit cleanly, ***destroy all bitmaps, untisall keyboard events etc..
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    for (int i = 0; i < NUM_IMAGES; i++){
        al_destroy_bitmap(images[i]);
    }
    for (int i = 0; i < 3; i++){
        al_destroy_bitmap(screen[i]);
    }

    //Save the game
    if (newGame){
        saveNewGame(grid, userName, score);
    }
    else if (resumeGame){
        saveResumedGame(grid, playerInfo, score, iChoice, numPlayers);
    }

    return 0;
}
