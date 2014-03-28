// Project: HIT! (functions.h)
// Name: Raghav Vamaraju
// Student ID: 1350076
// CCID: vamaraju
// Partner: Syed Hussain
// LEC EA1, LBL ED01

// This is a header file containing all of the function definitions for the program.
// This must be used in conjunction with "definitions.h" to work, as some
// of the variables in this file are from there.

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__


// Function to print a "Welcome" screen for the player upon starting the Arduino.
void welcome() 
{
    tft.fillScreen(0x0000);
    tft.setCursor(40, 40);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(4);
    tft.setRotation(PI);
    tft.print("HIT!");

    tft.setTextSize(1);
    tft.setCursor(10, 90);
    tft.print("Press Joystick To Begin!");

    while (digitalRead(SEL) == HIGH) {
        if (digitalRead(SEL) == LOW) {
            break;
        }
    }
    tft.setRotation(-PI);
    return;
}


// Function to print out the rules of the game (immediately after the "Welcome" screen).
void rules() 
{
    tft.fillScreen(0x0000);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.setCursor(0, 0);
    tft.setRotation(PI);
    tft.print("GAME MANUAL");
    tft.print("\n\r\n\rOBJECTIVE:\n\rTo hit the character on   the opposite side of the  playing field. The playingfield is three screen     lengths.");

    tft.print("\n\r\n\r\n\r\n\r\n\rPress Joystick To Continue");

    while (digitalRead(SEL) == HIGH) {
        if (digitalRead(SEL) == LOW) {
            break;
        }
    }

    tft.fillScreen(0x0000);
    tft.setCursor(0, 0);

    tft.print("CONTROLS: \n\rMove the joystick to      adjust the angle of the   shot. ");
    tft.print("Adjust the          potentiometer to change   the power of the shot. ");
    tft.print("Thepushbutton fires!\n\r\n\r");
    tft.print("Happy firing!");
    tft.print("\n\r\n\r\n\rPress Joystick To Begin!");

    while (digitalRead(SEL) == HIGH) {
        if (digitalRead(SEL) == LOW) {
            break;
        }
    }
    tft.setRotation(-PI);
    return;
}



// Function to allow the player to select Player vs. Player or Player vs. Computer mode.
void mode_selection() 
{
    tft.fillScreen(0x0000);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(1);
    tft.setCursor(0, 0);
    tft.setRotation(PI);
    tft.print("Would you like to play a  2-Player match (Player vs.Player), or a 1-Player    match (Player vs. Computer)?");
    tft.print("\n\r\n\rMove the joystick to      select an option. The     option displayed in red   will be selected when the joystick is pressed.");
    
    tft.setCursor(0, 95);
    tft.setTextColor(ST7735_RED);
    tft.print("Player vs. Player\n\r");
    
    tft.setCursor(0, 103);
    tft.setTextColor(ST7735_BLACK);
    tft.print("Player vs. Computer");
    
    P2_COMP_PLAYING = false;
    
    while (digitalRead(SEL) == HIGH) {
        tft.setCursor(0, 95);
        
        if (analogRead(HOR) > 650) {
            tft.setTextColor(ST7735_BLACK);
            tft.print("Player vs. Player\n\r");
            tft.setTextColor(ST7735_RED);
            tft.print("Player vs. Computer");
            P2_COMP_PLAYING = true;
        }
        
        else if (analogRead(HOR) < 450) {
            tft.setTextColor(ST7735_RED);
            tft.print("Player vs. Player\n\r");
            tft.setTextColor(ST7735_BLACK);
            tft.print("Player vs. Computer");
            P2_COMP_PLAYING = false;
        }
    }
    
    tft.setRotation(-PI);
    return;
}


// Function to draw the ground on the playing filed.
void ground() 
{
    tft.drawFastVLine(ground_x,ground_y, 160,ST7735_WHITE);
}


// Function to convert degrees to radians.
float deg_2_rad(float deg) 
{ 
    float rad = ((deg*PI)/180);
    return rad;
}


// Function to convert radians to degrees.
float rad_2_deg(float rad) {
    float deg = ((rad*180)/PI); 
    return deg;
}


// Function to define and draw the vector above a character's head.
// This vector tells the player the angle of the shot relative to the ground.
// If "write" is TRUE, then the vector will be drawn. If "write" is FALSE, the
// vector will be erased. Note that "hypotenuse" is the length of the 
// vector (20 pixels). The calculations are done in pixels. 
void vector(float angle, bool write) 
{
    float x, y, x0, y0, x1, y1, hypotenuse;
    
    x0 = starting_x_ball; 
    
    if(P1_SHOOTING) {
        y0 = starting_y; 
    }
    
    if(P2_SHOOTING || P2_COMP_SHOOTING){    
        y0 = starting_y2; 
    }

    hypotenuse = 20;
    
    x = cos(angle)*hypotenuse;
    y = sin(angle)*hypotenuse;

    x1 = x0 - x;
    y1 = y0 - y;

    if (write){
        tft.drawLine(x0, y0, x1, y1, ST7735_WHITE);
    }
    
    if (!write){
        tft.drawLine(x0, y0, x1, y1, ST7735_BLACK);
    }
}


// Draws character at a specified x and y coordinate.
// If "write" is TRUE, the character will be drawn. If "write"
// is FALSE, the character will be erased.
void character(int16_t x, int16_t y, bool write) 
{
    int height = 5;
    int width = 3;

    if(write) {
        // Drawing the head.
        tft.drawCircle(x-3, y ,2 ,ST7735_WHITE);
   
        // Drawing the torso.
        tft.drawRect(x,y-3, width+4, height+4, ST7735_WHITE);

        // Drawing the legs.
        tft.drawFastHLine(x+height+2, y-2, 6, ST7735_WHITE);
        tft.drawFastHLine(x+height+2, y+2, 6, ST7735_WHITE);

        // Drawing the gun. The orientation of the gun will change based on 
        // which field it is drawn in (i.e., based on whether it is for Player 1 or Player 2.)
        if(FIELD == 3) {
            tft.drawRect(x,y-10, width, height+3, ST7735_WHITE);
            tft.drawCircle(x, y-12 ,1 ,ST7735_WHITE);
        }
    
        if(FIELD == 1) {
            tft.drawRect(x,y+7, width, height+3, ST7735_WHITE);
            tft.drawCircle(x, y+13 ,1 ,ST7735_WHITE);
        }
    }   
    
    
    // Same programming as above, but to erase the character.
    if(!write) {
        // Erasing the head.
        tft.drawCircle(x-3, y ,2 ,ST7735_BLACK);
   
        // Erasing the torso.
        tft.drawRect(x,y-3, width+4, height+4, ST7735_BLACK);

        // Erasing the legs.
        tft.drawFastHLine(x+height+2, y-2, 6, ST7735_BLACK);
        tft.drawFastHLine(x+height+2, y+2, 6, ST7735_BLACK);

        // Erasing the gun based on the field (i.e., based on whether it is Player 1 or Player 2).
        if(FIELD == 3) {
            tft.drawRect(x,y-10, width, height+3, ST7735_BLACK);
            tft.drawCircle(x, y-12 ,1 ,ST7735_BLACK);
        }
        
        if(FIELD == 1) {
            tft.drawRect(x,y+7, width, height+3, ST7735_BLACK);
            tft.drawCircle(x, y+13 ,1 ,ST7735_BLACK);
        }   
    }
}


// Function to draw red ticks on to the screen (in the top-right corner) 
// representing the field number.
void field_reader() {
    tft.setCursor(0,0);
    
    tft.setTextColor(ST7735_RED);
    for (int i=0; i < FIELD; i++) {
        tft.println("--");
    }
    
    tft.setTextColor(ST7735_BLACK);
    for (int i=FIELD; i < 3; i++) {
        tft.println("--");
    }      
}


// Function to read the potentiometer (power) setting and draw white ticks 
// representing it on to the screen. 
float power_reader() 
{
    float power = analogRead(POT);

    tft.setTextSize(1);
    int number_of_ticks = power / 100;

    // If the current number of ticks is less than the required number, draw more.
    if ((ticks_prsnt < number_of_ticks) || (ticks_prsnt == number_of_ticks)) {
        
        tft.setCursor(0,30);
        tft.setTextColor(ST7735_WHITE);
    
        for (int i = 0; i < number_of_ticks; i++) {
            tft.println("|");
        }
    }

    // If the current number of ticks is more than the required number, erase the extra ticks.
    if (ticks_prsnt > number_of_ticks) {
        
        tft.setCursor(0,30);
        tft.setTextColor(ST7735_BLACK);
    
        for (int i = 0; i < ticks_prsnt; i++) {
            tft.println("|");
        }

        tft.setCursor(0,30);
        tft.setTextColor(ST7735_BLACK);

        for (int i = 0; i < number_of_ticks; i++) {
            tft.println("|");
        }
    }

    // Return the power setting as a decimal percentage.
    ticks_prsnt = number_of_ticks;
    power = (power / 1023);
    return power;
}


// Function to both draw the ball (i.e., the bullet) and deteremine whether it has
// hit the other player. this is done using formulae for projectile motion.
// "v" means velocity, "d" means distance, "i" means initial, "f" means final,
// and x and y refer to the direction. "r" refers to the radius of the ball.
void draw_ball(float power1, float angle1) 
{
    float v_ix, v_iy, v_fx, v_fy;
    float d_ix, d_iy, d_fx, d_fy;

    int r = 5; 
    v_fy = 0;
    v_ix = (-1)*(power1*max_v)*cos(angle1);
    v_iy = (-1)*(power1*max_v)*sin(angle1);

    float t = 0;

    if(P2_SHOOTING || P2_COMP_SHOOTING){
        d_ix = starting_x_ball;
        d_iy = starting_y2;
    }
    if(P1_SHOOTING){
        d_ix = starting_x_ball;
        d_iy = starting_y;
    }

    d_fx = d_ix;
    d_fy = d_iy;

    // While the ball is within the 3-screen playing field, move it in
    // slight increments and check if it has touched the other player.
    // "t" represents the elapsed time.
    while (d_fx > -50 && d_fx < 129 && FIELD < 4 && FIELD > 0) {

        t = t + 0.1;
      
        v_fy = v_iy; 
        v_fx = v_ix + g*t;

        d_fx = d_ix + (v_fx)*t + 0.5*(g)*(t)*(t);
        d_fy = d_iy + (v_fy)*t;   

        tft.fillCircle(d_fx, d_fy, r, ST7735_WHITE);

        delay(100);

        tft.fillCircle(d_fx, d_fy, r, ST7735_BLACK);

        d_ix = d_fx;
        d_iy = d_fy;
        v_ix = v_fx;
        v_iy = v_fy;

        // If the ball is at the edge of the screen, exit the "while" loop 
        // if the ball has left the 3-screen playing field. Otherwise, 
        // decrement or increment the field number.
        if (d_fy < 0 || d_fy > 161) {
            if(d_fy < 0) {
                if(FIELD == 1) {
                    break;
                }
                d_iy = 160;
            }

            if(d_fy > 161) {
                if(FIELD == 3) {
                    break;
                }
                d_iy = 0;
            }

            ground();
            
            if(P1_SHOOTING) {
                character(starting_x, starting_y, 0);
                FIELD--;
            }
            if(P2_SHOOTING || P2_COMP_SHOOTING) {
                character(starting_x, starting_y2, 0);
                FIELD++;
            }
            
            field_reader();
        }

        // Check if the ball has hit the other player (player 2). If it has,
        // print it out on the screen.
        if (FIELD == 1 && P1_SHOOTING) {
            character(starting_x, starting_y2, 1);
            int diff_x1 = abs((starting_x) - d_fx);
            int diff_y1 = abs((starting_y2) - d_fy);        

            if ((diff_x1 < hit_thresh) && (diff_y1 < hit_thresh)) {
                P2_LIFE--;
                tft.fillScreen(ST7735_BLACK);
                tft.setRotation(PI);
                tft.setTextColor(ST7735_RED);
                tft.setCursor(20, 40);
                tft.print("PLAYER 2 HAS BEEN HIT!\n\r     ");
                tft.print(P2_LIFE);
                tft.print(" LIVES REMAINING");
                delay(3000);
                tft.fillScreen(ST7735_BLACK);
                tft.setRotation(-PI);
                power_reader();
                break;
            }
        }

        // Check if the ball has hit the other player (player 1). If it has,
        // print it out on the screen.
        if (FIELD == 3 && (P2_SHOOTING || P2_COMP_SHOOTING)) {
            character(starting_x, starting_y, 1);
            int diff_x2 = abs((starting_x) - d_fx);
            int diff_y2 = abs((starting_y) - d_fy);        

            if ((diff_x2 < hit_thresh) && (diff_y2 < hit_thresh)) {
                P1_LIFE--;
                tft.fillScreen(ST7735_BLACK);
                tft.setRotation(PI);
                tft.setTextColor(ST7735_RED);
                tft.setCursor(20, 40);
                tft.print("PLAYER 1 HAS BEEN HIT!\n\r     ");
                tft.print(P1_LIFE);
                tft.print(" LIVES REMAINING");
                delay(3000);
                tft.fillScreen(ST7735_BLACK);
                tft.setRotation(-PI);
                power_reader();
                break;
            }
        }
    }

    // Redraw the ground in case it has been damaged.
    ground();
}


// Function to change turns after a ball has been drawn. This will 
// redefine all the necessary variables and redraw the characters and vectors.
void change_turns() {

    // If it was initially player 1's turn, erase player 1
    // and switch to player 2.
    if(P1_SHOOTING) {
    
        // Erase player 1 and exit his turn.
        character(starting_x, starting_y, 0);
        P1_SHOOTING = false;
        
        if(P2_COMP_PLAYING) {
            P2_COMP_SHOOTING = true;
        }
        else {
            P2_SHOOTING = true;
        }

        FIELD = 1;

        // Erase and redraw player 2 (to ensure no stray pixels).
        character(starting_x, starting_y2, 0);
        character(starting_x, starting_y2, 1);
        
        // Erase the vector from player 1 and draw the vector for player 2.
        vector(angle_P1,0);
        vector(angle_P2,1);
        field_reader();
        turn_num++;
        return;
    }
    
    // If it was initially player 2's turn, erase player 2
    // and switch to player 1.
    if(P2_SHOOTING || P2_COMP_SHOOTING) {
    
        // Erase player 2 and exit his turn.
        character(starting_x, starting_y2, 0);
        P2_SHOOTING = false;
        P2_COMP_SHOOTING = false; 
        
        P1_SHOOTING = true;
        FIELD = 3;

        // Erase and redraw player 1 (to ensure no stray pixels).
        character(starting_x, starting_y, 0);
        character(starting_x, starting_y, 1);

        // Erase the vector from player 2 and draw the vector for player 1.
        vector(angle_P2,0);
        vector(angle_P1,1);
        field_reader();
        turn_num++;
        return;
    }    
}


// Function to print the current power setting and angle
// to the screen. This will occur after the joystick has been
// pressed during gameplay.
void disp_power_ang(bool P1, bool P2){
    tft.fillScreen(ST7735_BLACK);
    tft.setRotation(PI);
    tft.setCursor(0,0);
    tft.setTextColor(ST7735_WHITE);    
    tft.print("Angle: ");

    if(P1) {
        tft.print((int )rad_2_deg(angle_P1) % 360);
        tft.println(" degrees");
        tft.print("Power: ");    
        tft.println((int )(power_P1*100));
    }

    if(P2) {
        tft.print((int )rad_2_deg(angle_P2) % 360);
        tft.println(" degrees");
        tft.print("Power: ");    
        tft.println((int )(power_P2*100));
    }
    
    tft.print("\n\r\n\r\n\rPress joystick to exit!");
}

#endif


