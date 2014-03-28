// Project: HIT! (definitions.h)
// Name: Raghav Vamaraju
// Student ID: 1350076
// CCID: vamaraju
// Partner: Syed Hussain
// LEC EA1, LBL ED01

// This is a header file containing all of the (global) variable definitions for the program.

#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__


#include <Arduino.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>

#define TFT_CS   6  
#define TFT_DC   7  
#define TFT_RST  8  


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 
 
// Define variables approximating the joystick starting position.
#define jstick_start_h 512
#define jstick_start_v 512


// Define variables for the maximum velocity of the ball and gravity.
#define max_v 30
#define g 0.981


// Pin definitions for the joystick, pushbutton, and potentiometer.
#define SEL 9 
#define VERT 1
#define HOR 0 
#define BUTTON 4
#define POT 2


// Starting coordinates for field 1 of the total playing field (3 total).
const int Starting_f1_x = 0;
const int Starting_f1_y = 0;
const int Ending_f1_x = 128;
const int Ending_f1_y = 160;


// Starting coordinates for field 2 of the total playing field (3 total).
const int Starting_f2_x = 0;
const int Starting_f2_y = 160;
const int Ending_f2_x = 128;
const int Ending_f2_y = 320;


// Starting coordinates for field 3 of the total playing field (3 total).
const int Starting_f3_x = 0;
const int Starting_f3_y = 320;
const int Ending_f3_x = 128;
const int Ending_f3_y = 480;


// Global constants for the ground position, character position,
// starting life count, hit threshold.
const int ground_x = 127;
const int ground_y = 0;
const int starting_x = ground_x - 15;
const int starting_x_ball = 100;
const int starting_life_count = 3;
const int hit_thresh = 20;    // The ball must be within 20 pixels of a Player to count as a hit.


// Global variables for the character position, angle, and power.
int starting_y2 = 70;
int starting_y = 70;
float angle_P1 = 0; // Angle is calculated in radians unless otherwise stated.
float power_P1 = 0;
float angle_P2 = 0; // Angle is calculated in radians unless otherwise stated.
float power_P2 = 0;
float ticks_prsnt = 0;
float prev_angle_P2 = 0;


// Starting field number and turn number.
int FIELD = 3;
int turn_num = 0;


// Variables for Player 1 and 2 life.
int P1_LIFE = starting_life_count;
int P2_LIFE = starting_life_count;


// Logicals for checking the turn.
bool P1_SHOOTING = true;
bool P2_SHOOTING = false;
bool P2_COMP_SHOOTING = false;
bool P2_COMP_PLAYING = false;    // This is turned on when a Player vs. Computer game is selected.
bool RESET = false;    // This becomes true after the game is completed.


#endif


