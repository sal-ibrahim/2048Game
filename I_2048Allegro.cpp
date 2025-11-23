/***************************************************************************
*                                                                          *
*                                                                          *                                                                                                              *
***************************************************************************/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>.
#include "I_2048.h"

/**Initializes required allegro functions */
void initializeAllegro(){
    // Initialize Allegro
	al_init();

	//Initialize font addons
	al_init_font_addon();
    al_init_ttf_addon();

}
/**This function checks to see if some allegro routines have been set up properly.
A message box reports what wasn't set up properly.
Parameters: display, font and event_queue variables
Returns: 0 if good, -1 if error
*/
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue){
    //Check if allegro routines worked successfully.
    //Check if display worked properly
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	//Check if fonts worked properly
	if (!font){
        al_show_native_message_box(display, "Error", "Error", "Could not load Pixel_Font.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
   }
    //Intialize and check keyboard routines
    if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "Failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}
   	//Check event queue
   	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_font(font);
      	return -1;
	}
	//Initialize and check image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return 0;
	}
	//Initialize and check primitive addons
	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
	return 0;
}
//********PRINT GRID TO SCREEN*********
/**This function prints the contents of the grid to the screen using allegro
Parameters: Tiles grid[][MAX_COL] is the grid of tiles
ALLEGRO_FONT
*/
/*
void printGrid(ALLEGRO_FONT *font, Tiles grid[][MAX_COL], ALLEGRO_BITMAP *screen){
    //Build screen by printing to the buffer
    //al_clear_to_color(BACKGROUND);

    screen = al_load_bitmap("background.png");
    // Display picture started at top left corner
	al_draw_bitmap(screen, 0, 0, 0);

}
*/
/**This function displays the tiles in 2D array to the grid using allegro
Parameters: Tiles grid[][MAX_COL] is the grid of tiles
ALLEGRO_FONT
*/
void printTiles(ALLEGRO_FONT *font, Tiles grid[][MAX_COL]){
    //Display tiles onto grid
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            if (grid[row][col].value != 0){
                //Swap row and col in coordinate calculation otherwise tiles will be reflected. col = x, row = y
                int x = (col * TILE_W)  + 85;
                int y = (row * TILE_H)  + 315;
                int tile_width = al_get_bitmap_width(grid[row][col].image);
                int tile_height = al_get_bitmap_height(grid[row][col].image);

                //Draw each tile's image
                al_draw_scaled_bitmap(grid[row][col].image, 0, 0, tile_width, tile_height, x, y, 135 * 1.4, 100 * 1.4, 0);
            }
        }
    }
}
/**This function loads images
Parameters: images[] is an array of images which is used to store tile images
*/
void loadImages(ALLEGRO_BITMAP *images[]){
    //Load images
    images[0] = al_load_bitmap("tile2.png");
    images[1] = al_load_bitmap("tile4.png");
    images[2] = al_load_bitmap("tile8.png");
    images[3] = al_load_bitmap("tile16.png");
    images[4] = al_load_bitmap("tile32.png");
    images[5] = al_load_bitmap("tile64.png");
    images[6] = al_load_bitmap("tile128.png");
    images[7] = al_load_bitmap("tile256.png");
    images[8] = al_load_bitmap("tile512.png");
    images[9] = al_load_bitmap("tile1024.png");
    images[10] = al_load_bitmap("tile2048.png");
}
/**This function updates each tile's image based on their value
Parameters: grid[][MAX_COL] is the grid which will be accessed
images[] is the array of images which will be used to assign images
*/
void updateTileImage(Tiles grid[][MAX_COL], ALLEGRO_BITMAP *images[]){
    //If the tile has a value of 0, set it to nullptr
    for (int row = 0; row < MAX_ROW; row++){
        for (int col = 0; col < MAX_COL; col++){
            if (grid[row][col].value == 0){
                grid[row][col].image = nullptr;
            }
            else{
                //Set each tile's image to the corresponding image in the array
                switch (grid[row][col].value){
                    case 2:
                        grid[row][col].image = images[0];
                        break;
                    case 4:
                        grid[row][col].image = images[1];
                        break;
                    case 8:
                        grid[row][col].image = images[2];
                        break;
                    case 16:
                        grid[row][col].image = images[3];
                        break;
                    case 32:
                        grid[row][col].image = images[4];
                        break;
                    case 64:
                        grid[row][col].image = images[5];
                        break;
                    case 128:
                        grid[row][col].image = images[6];
                        break;
                    case 256:
                        grid[row][col].image = images[7];
                        break;
                    case 512:
                        grid[row][col].image = images[8];
                        break;
                    case 1024:
                        grid[row][col].image = images[9];
                        break;
                    case 2048:
                        grid[row][col].image = images[10];
                        break;
                }
            }
        }
    }
}
/**This function loads screens
Parameters: screen[] is an array to hold screen images
ALLEGRO_FONT
*/
void loadScreens(ALLEGRO_BITMAP *screen[]){
    //Load screens
    screen[0] = al_load_bitmap("menu.png");
    screen[1] = al_load_bitmap("manual.png");
    screen[2] = al_load_bitmap("mainBackground.png");
    screen[3] = al_load_bitmap("mainWin.png");
    screen[4] = al_load_bitmap("mainEnd.png");
}
