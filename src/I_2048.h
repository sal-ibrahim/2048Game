#ifndef CHECK
#define CHECK

//These header files must be included in order for the program to recognize decleration of parameters that work with allegro
#include <allegro5/allegro.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_native_dialog.h> 		// for message box
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//Define constants
#define MAX_ROW 4
#define MAX_COL 4

//Define colour
#define NVBLUE   al_map_rgb(50,48,94)

//Images
#define NUM_IMAGES 11

//***FOR TILES
const int SCREEN_W = 1024;       // screen width
const int SCREEN_H = 1024;        // screen height
const int LETTER_SIZE = 60;

const int TILE_W = 220;
const int TILE_H = 165;

//Define structures
struct Tiles{
    int value;
    bool merged;
    ALLEGRO_BITMAP *image;
};
struct Player{
    char userName[50];
    int score;
    int gridOfTiles[MAX_ROW][MAX_COL];

};
//*****PROTOTYPES*****
//Tiles Generation
void initializeGrid(Tiles grid[][MAX_COL]);
int generateRandomTile(Tiles grid[][MAX_COL]);
int randomTileValue();

//Move Functions
void moveTilesUp(Tiles grid[][MAX_COL]);
void moveTilesDown(Tiles grid[][MAX_COL]);
void moveTilesLeft(Tiles grid[][MAX_COL]);
void moveTilesRight(Tiles grid[][MAX_COL]);

int checkGrids(Tiles grid[][MAX_COL], int oldGrid[][MAX_COL], bool &checkSameGrid);

void mergeTilesLeft(Tiles grid[][MAX_COL], int &score);
void mergeTilesRight(Tiles grid[][MAX_COL], int &score);
void mergeTilesUp(Tiles grid[][MAX_COL], int &score);
void mergeTilesDown(Tiles grid[][MAX_COL], int &score);

//Game Over
int checkHzMoves(Tiles grid[][MAX_COL]);
int checkVrtMoves(Tiles grid[][MAX_COL]);
int checkOpenTiles(Tiles grid[][MAX_COL]);
bool checkWin(Tiles grid[][MAX_COL]);
bool checkGameOver(Tiles grid[][MAX_COL]);

//--Allegro Functions
void initializeAllegro();
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue);
void printGrid(ALLEGRO_FONT *font, Tiles grid[][MAX_COL], ALLEGRO_BITMAP *screen);
void printTiles(ALLEGRO_FONT *font, Tiles grid[][MAX_COL]);

//Tile images
void loadScreens(ALLEGRO_BITMAP *screen[]);
void loadImages(ALLEGRO_BITMAP *images[]);
void updateTileImage(Tiles grid[][MAX_COL], ALLEGRO_BITMAP *images[]);

//--File Functions
int saveNewGame(Tiles grid[][MAX_COL], char player[50], int iScore);
int saveResumedGame(Tiles grid[][MAX_COL], Player playerInfo[], int highScore, int index, int numberPlayers);


int loadSavedGame(Player playerInfo[], Tiles grid[][MAX_COL], int counter, int &iChoice, int &score);
int saveHighScore(Tiles grid[][MAX_COL], int highScore);
int uploadPlayers(Player playerInfo[]);
int getNumOfPlayers();

#endif // CHECK
