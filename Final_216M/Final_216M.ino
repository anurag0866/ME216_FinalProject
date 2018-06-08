/*---------------Includes-----------------------------------*/
#include <Wire.h>
#include <SPI.h>
#include <Metro.h>

/*---------------Global Variables-----------------------------------*/
#include "globalVariables.h"

// Display
#include "ssd1306_i2c.h"
#include "AdafruitIO_WiFi.h"
#include "icons.h"

//IMU
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  

//WIFI
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//Files
#include "displayCode.h"
#include "IMUCode.h"
#include "IOTCode.h"
Metro workout_minute_timer = Metro(60000);
bool continueimuflag = 0;

/*---------------Module Fuctions-----------------------------------*/
void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}


void setup() {
  target = 50;
  currentRepCount = 0;
  totalDayCount = 0;
  workoutTime = 0;
  score = 10;
  leagueposition = 3;
  workoutflag = 0;
  continueimuflag = 0;

  // Setup file for display
  Serial.begin(115200);
  Serial.println("RESET");
  pinMode(STATS_BUTTON, INPUT);
  pinMode(PAUSE_BUTTON, INPUT);
  pinMode(WORKOUT_BUTTON, INPUT);
  display.init();
  display.clear();
  drawDefault(10, 10) ;
  disp = DEFAULT_STATE;

  //Setup for LSM IMU  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");
  Serial.println("");
  Serial.println("");
  int lift_state = 0;

   WiFi.begin(WIFI_SSID , WIFI_PASS);

}

void loop() {
  score = totalDayCount * 2;
  screenloop();
  if ((workoutflag == 1) && (continueimuflag==0)) {
    continueimuflag = 1;
    workout_minute_timer.reset();
  }
  if (continueimuflag ==1) {
    IMUloop();
    if (workout_minute_timer.check()==1) {
      workoutTime = workoutTime+1;
      drawWorkout(10, 10);
      io.run();
      Anurag216Score->save(score);
    }    
  }
  if ((workoutflag == 0) && (continueimuflag==1)) {
    continueimuflag = 0;
  }
}
