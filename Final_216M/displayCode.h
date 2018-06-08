//// Module Defined values
//#define SDA 4
//#define SCL 5
//#define I2C 0x3C
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define WORKOUT_BUTTON 16
#define PAUSE_BUTTON   14
#define STATS_BUTTON   12  


#include <Metro.h>
SSD1306 display(0x3C, 4, 5); // Display instance
Metro displaytimer = Metro(5000);

void drawDefault(int x, int y) {
  display.clear();
  display.setFontScale2x2(true);
  display.drawString(20 , 0 , "Forza");
  display.setFontScale2x2(false);
  display.drawString(20, 30, "Hi Sirius");  
  display.display();
}
// Screen to display stats (button 12)
void drawStats(int x, int y) {
  display.clear();
  display.setFontScale2x2(false);
  display.drawString(0 , 0 , "Today's Stats");
  display.drawString(0, 15, String("Score:" + String(score)));  
  display.drawString(0, 30, String("Position:" + String(leagueposition)));
  display.drawString(0, 45, String("Day Count:" + String(totalDayCount)));  
  display.display();
}
// Screen to display Pause (button 14)
void drawPause(int x, int y) {
  display.clear();
  display.setFontScale2x2(false);
  display.drawString(0 , 0 , "Workout Paused");
  display.drawString(0, 20,  "Great Job ");
  display.drawString(0, 40, String("Total: " + String(totalDayCount)));
  display.display();
}

// Screen to display Workout (button 16)
void drawWorkout(int x, int y) {
  display.clear();
  display.setFontScale2x2(true);
  display.drawString(0, 15, String("Count:" + String(currentRepCount)));
  display.setFontScale2x2(false);
  display.drawString(0, 50, String("Total:" + String(totalDayCount)));
  display.display();
}

void drawPauseError(int x, int y) {
  display.clear();
  display.setFontScale2x2(false);
  display.drawString(0, 20, "Start a Workout First");
  display.drawString(0, 40, ":)");
  display.display();
}

typedef enum {
  DEFAULT_STATE,STATE_S, STATE_P, STATE_W, STATE_PE
} display_state;

display_state disp;

void screenloop() {

  //Serial.println(disp);
  // put your main code here, to run repeatedly:
    switch (disp) {
    case DEFAULT_STATE:      
      if (digitalRead(STATS_BUTTON) == 0) {
        disp = STATE_S;
        displaytimer.reset();
        drawStats(10, 10);
      }
      if (digitalRead(PAUSE_BUTTON) == 0) {
        disp = STATE_PE;
        displaytimer.reset();
        drawPauseError(10, 10);
      }
      if (digitalRead(WORKOUT_BUTTON) == 0) {
        disp = STATE_W;
        workoutflag = 1;
		    currentRepCount = 0;
        displaytimer.reset();
        drawWorkout(10, 10);
      }  
      break;
    case STATE_S:
      if (displaytimer.check() == 1) {
        disp = DEFAULT_STATE;
        drawDefault(10, 10);
      }
      if (digitalRead(STATS_BUTTON) == 0) {
        disp = STATE_S;
        displaytimer.reset();
        drawStats(10, 10);
      }
      if (digitalRead(PAUSE_BUTTON) == 0) {
        disp = STATE_PE;
        displaytimer.reset();
        drawPauseError(10, 10);
      }
      if (digitalRead(WORKOUT_BUTTON) == 0) {
        workoutflag = 1;
        disp = STATE_W;
		    currentRepCount = 0;
        displaytimer.reset();
        drawWorkout(10, 10);
      }
      break;
   case STATE_P:
//      if (displaytimer.check() == 1) {
//        disp = DEFAULT_STATE;
//        drawDefault(10, 10);
//      }
      if (digitalRead(STATS_BUTTON) == 0) {
        disp = STATE_S;
        displaytimer.reset();
        drawStats(10, 10);
      }
//      if (digitalRead(PAUSE_BUTTON) == 0) {
//        disp = STATE_P;
//        displaytimer.reset();
//        drawPause(10, 10);
//      }
      if (digitalRead(WORKOUT_BUTTON) == 0) {
        workoutflag = 1;
        disp = STATE_W;
		    currentRepCount = 0;
        displaytimer.reset();
        drawWorkout(10, 10);
      }
      break;
   case STATE_W:
//      if (displaytimer.check() == 1) {
//        disp = DEFAULT_STATE;
//        drawDefault(10, 10);
//      }
      if (digitalRead(STATS_BUTTON) == 0) {
        workoutflag = 0;
        disp = STATE_S;
        displaytimer.reset();
        drawStats(10, 10);
      }
      if (digitalRead(PAUSE_BUTTON) == 0) {
        workoutflag = 0;
        disp = STATE_P;
        displaytimer.reset();
        drawPause(10, 10);
      }
      if (digitalRead(WORKOUT_BUTTON) == 0) {
        disp = STATE_W;
        displaytimer.reset();
        drawWorkout(10, 10);
      }    
      break;
    case STATE_PE:
      if (displaytimer.check() == 1) {
        disp = DEFAULT_STATE;
        drawDefault(10, 10);
      }
      if (digitalRead(STATS_BUTTON) == 0) {
        disp = STATE_S;
        displaytimer.reset();
        drawStats(10, 10);
      }
      if (digitalRead(PAUSE_BUTTON) == 0) {
        disp = STATE_PE;
        displaytimer.reset();
        drawPauseError(10, 10);
      }
      if (digitalRead(WORKOUT_BUTTON) == 0) {
        workoutflag = 1;
        disp = STATE_W;
		    currentRepCount = 0;
        displaytimer.reset();
        drawWorkout(10, 10);
      }    
      break;
    
    default:    // Should never get into an unhandled state
      Serial.println("What is this I do not even...");
  }
} 
     

