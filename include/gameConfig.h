/*---------------------------------------------------------------------------^/
 | Names: Dillon Allan and Amir Hansen                                       |
 | ID: 0000000 and 0000000                                                   |
 | CMPUT 275, Winter 2019                                                    | 
 | Final Project: Pac Man on Arduino                                         |
/^---------------------------------------------------------------------------*/
/* Game constant configuration */
#ifndef game_config
#define game_config

#define Y_BOUND 31 // num tiles on y-axis 
#define X_BOUND 28 // num tiles on x-axis
#define SCALE 8 // tile size
#define ILI9341_PINK 0xEB17
#define ILI9341_ORANGE 0xEB62
#define ILI9341_LIGHTBLUE 0x44FD

/* For the Joystick */
#define DEAD_ZONE 64*64
#define STICK_OFFSET 512

#endif