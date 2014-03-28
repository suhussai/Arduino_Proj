// Project: HIT! (hit.cpp)
// Name: Raghav Vamaraju
// Student ID: 1350076
// CCID: vamaraju
// Partner: Syed Hussain
// LEC EA1, LBL ED01

#include "definitions.h"
#include "functions.h"


void setup() 
{
    // Initialize the Serial monitor, pin inputs, and screen.
    Serial.begin(9600);
    Serial.println("---PROGRAM BEGIN---");
    digitalWrite(SEL, HIGH);
    pinMode(BUTTON, INPUT);
    digitalWrite(BUTTON, HIGH);
    tft.initR(INITR_BLACKTAB);  

    // Run functions to welcome the Player, print the rules, and 
    // select the gameplay mode.
    welcome();
    rules();
    mode_selection();
    
    tft.fillScreen(ST7735_BLACK);

    // Randomly vary the position of the two characters by
    // changing the y-coordinate.
    int rand_ext_y, rand_ext_y2;
    randomSeed(analogRead(5));
    rand_ext_y = random(50);
    rand_ext_y2 = random(60);

    starting_y = starting_y + rand_ext_y;
    starting_y2 = starting_y2 + rand_ext_y2;

    rand_ext_y = random(40);
    rand_ext_y2 = random(30);

    starting_y = starting_y - rand_ext_y;
    starting_y2 = starting_y2 - rand_ext_y2;
    
    // Ensure that Player 1 goes first.
    P1_SHOOTING = true;
    P2_SHOOTING = false;
    P2_COMP_SHOOTING = false;
    FIELD = 3;
    
    // Draw the ground, character, and field indicator.
    ground();
    character(starting_x, starting_y, 1);
    field_reader();
}

void loop() 
{
    // Check if either Player has died. If they have, print
    // "GAME OVER" and restart the game (i.e., run "setup").
    if(P1_LIFE <= 0 || P2_LIFE <= 0) {
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(0,40);
        tft.setTextSize(2);
        tft.setTextColor(ST7735_GREEN);
        tft.setRotation(PI);
        tft.println("  GAME OVER");
        tft.setTextSize(1);
        
        if (P1_LIFE <= 0) {
            tft.print("\n\r\n\r      Player 2 Wins!");
        }
        
        if (P2_LIFE <= 0) {
            tft.print("\n\r\n\r      Player 1 Wins!");
        }
        
        delay(5000);
        tft.fillScreen(ST7735_BLACK);
        tft.setRotation(-PI);
        P1_LIFE = starting_life_count;
        P2_LIFE = starting_life_count;
        RESET = true;
        setup();
    }
    
    // If the game has been played already, this ensures that the variables 
    // are reset to default.
    if (RESET) {
        P1_SHOOTING = true;
        P2_SHOOTING = false;
        P2_COMP_SHOOTING = false;
        P1_LIFE = starting_life_count;
        P2_LIFE = starting_life_count;
        FIELD = 3;
        turn_num = 0;
        vector(angle_P1, 0);
        vector(angle_P2, 0);
        angle_P1 = 0;
        angle_P2 = 0;
        
        ground();
        field_reader();
        power_reader();
        character(starting_x, starting_y, 0);
        character(starting_x, starting_y2, 0);
        character(starting_x, starting_y, 1);
        RESET = false;
    }

    // If it is Player 1's turn, read the joystick position and
    // change the vector position accordingly. If Player 1 has fired
    // (i.e., pressed the pushbutton), draw the ball and change turns
    // to Player 2.
    if(P1_SHOOTING) {
        int jstick_new_h = analogRead(HOR);  // side t0 side
        
        // If the joystick is pushed downwards, increase the angle of the
        // vector from the vertical start position.
        if ((jstick_new_h - jstick_start_h) > 100 && rad_2_deg(angle_P1) < 130 ) {
            angle_P1 = angle_P1 + ((PI)/180);
            vector(angle_P1-((PI)/180),0);
            vector(angle_P1,1);
        }
        else { 
            vector(angle_P1,1);
        }

        // If the joystick is pushed upwards, decrease the angle of the
        // vector from the vertical start position.
        if ((jstick_new_h - jstick_start_h) < -100 && rad_2_deg(angle_P1) > -130) {
            angle_P1 = angle_P1 - ((PI)/180);
            vector(angle_P1+((PI)/180),0);
            vector(angle_P1,1);
        }
        else { 
            vector(angle_P1,1);
        }

        // Read the power setting from the potentiometer.
        power_P1 = power_reader();
        int fire = digitalRead(BUTTON);

        if (fire == LOW) {
            draw_ball(power_P1, angle_P1);  
            change_turns();
        }

        // If the joystick is pressed, display the power and angle
        // settings on to the screen and wait for the joystick to be re-pressed.
        if(digitalRead(SEL) == LOW) {    
            disp_power_ang(P1_SHOOTING,P2_SHOOTING);
            
            while(digitalRead(SEL) == HIGH) { }
            
            if(digitalRead(SEL) == LOW) {
                tft.setRotation(-PI);
                tft.fillScreen(ST7735_BLACK);
                ground();
                field_reader();
                power_reader();
                character(starting_x, starting_y, 1);
                vector(angle_P1,1);    
            }
    
            delay(200); 
        }
    }
    
    
    // Repeat the process from above but for Player 2 (only if it is his turn
    // and he is still alive). 
    if(P2_SHOOTING && (P2_LIFE != 0)) {
    
        int jstick_new_h2 = analogRead(HOR);  // side t0 side

        if ((jstick_new_h2 - jstick_start_h) > 100 && rad_2_deg(angle_P2) > -130 ) {
            angle_P2 = angle_P2 - ((PI)/180);
            vector(angle_P2+((PI)/180),0);
            vector(angle_P2,1);
        }
        else { 
            vector(angle_P2,1);
        }

        if ((jstick_new_h2 - jstick_start_h) < -100 && rad_2_deg(angle_P2) < 130) {
            angle_P2 = angle_P2 + ((PI)/180);
            vector(angle_P2-((PI)/180),0);
            vector(angle_P2,1);
        }
        else { 
            vector(angle_P2,1);
        }

        power_P2 = power_reader();
        int fire2 = digitalRead(BUTTON);
    
        if (fire2 == LOW) {
            draw_ball(power_P2, angle_P2);    
            change_turns();
        }

        if(digitalRead(SEL) == LOW) {    
            disp_power_ang(P1_SHOOTING,P2_SHOOTING);
            
            while(digitalRead(SEL) == HIGH) { }

            if(digitalRead(SEL) == LOW) {
                tft.setRotation(-PI);
                tft.fillScreen(ST7735_BLACK);
                ground();
                field_reader();
                power_reader();
                character(starting_x, starting_y2, 1);
                vector(angle_P2,1);    
            }
    
            delay(200); 
        }
    }
    
    
    // If it is the Computer's turn, randomly choose his shooting position 
    // within certain limits, and change it based on his previous shooting
    // position.
    if(P2_COMP_SHOOTING && (P2_LIFE != 0)){
        vector(angle_P2, 0);
        float next_hit_y, next_hit_x;
        
        // If it is the first time the Computer is shooting, define
        // the power and angle of his shot.
        if(turn_num == 1) {
            next_hit_y = 400;
            next_hit_x = 120;

            power_P2 = sqrt(abs(next_hit_x*g*3))/max_v;	
            angle_P2 = (-1)*asin((next_hit_y*g)/((power_P2*max_v)*(max_v)));
        }
     
        // If it is not his first time shooting, define the power and angle
        // of his shot relative to his previous shot and then add a random
        // modifier.
        else if (turn_num != 1) {
            float v2 = ((power_P2*max_v)*(power_P2*max_v));
            float prev_hit_y = starting_y2 + (-1)*((v2)*(sin(2*angle_P2))/g);
            float prev_hit_x = v2/(2*g);
	
            float diff = (prev_hit_y - 10) - starting_y - 320;
            
            // If his previous shot was too powerful, decrease both the
            // power and angle by a small, random amount.
            if(diff > 0) {
                angle_P2 = angle_P2 - deg_2_rad(random(0,5));
                float x = random(1,5);
                x = x/100;
                power_P2 = power_P2 - x;
            }

            // If his previous shot was too weak, increase both the
            // power and angle by a small, random amount.
            if(diff < 0) {
                angle_P2 = angle_P2 + deg_2_rad(random(0,5));
                float y = random(1,5);
                y = y/100;
                power_P2 = power_P2 + y;
            }
        }
      
        // Draw his vector, fire, and change turns.
        vector(angle_P2,1);
        draw_ball(power_P2, angle_P2);	  
        change_turns();
        prev_angle_P2 = angle_P2;

    }
}


