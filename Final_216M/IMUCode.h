// Part 1 - Inclusion of Modules

// Modules for 9 Axis IMU

// Electrical Connections for the 9 Axis IMU - Adafruit device
//   Connections (For default I2C)
//   ===========
//   Connect SCL to analog 5
//   Connect SDA to analog 4
//   Connect VDD to 5V DC
//   Connect GROUND to common ground

// i2c
/* Assign a unique base ID for this sensor */  
// Set up an instance of the adafruit class



// Part 2 - Instances of classes, global variables define
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(); // ID not assigned yet
Metro minutetimer = Metro(60000);
int a = 7;
int Low_Threshold = -4000;
int High_Threshold = -100;
int lift_state = 0;  // state 0 - default, state -1 default. When it starts - its in default state.

// Part 3 - Functions belonging to the code
void Resp_to_key_motor(char);
// void Detect_Lift(void);

// Part 4 Set up

void IMUloop() {
  lsm.read();
  if (lift_state ==0) {
    if (lsm.gyroData.x > High_Threshold) {
      lift_state = 1;
    }
  }
  if (lift_state == 1) {
    if (lsm.gyroData.x < Low_Threshold) {
      lift_state = 0;
      Serial.println("One lift detected");
      totalDayCount = totalDayCount+1;
	    currentRepCount = currentRepCount + 1;
	    drawWorkout(10, 10);
    }
 
  }
}


// Main Loop
void testLSMloop() 
{ 
  if (Serial.available()){
    char key_serial_monitor = Serial.read();
    Serial.print("Read in key: ");
    Serial.println(key_serial_monitor);
    Resp_to_key_motor(key_serial_monitor);
  }
  lsm.read();
  if (lift_state ==0) {
    if (lsm.gyroData.x > High_Threshold) {
      lift_state = 1;
    }
  }
  if (lift_state == 1) {
    if (lsm.gyroData.x < Low_Threshold) {
      lift_state = 0;
      Serial.println("One lift detected");
      //liftcounter = liftcounter+1;
    }
  }
  if (a==1) {
  Serial.print("Accel x: "); Serial.print((int)lsm.accelData.x); Serial.println(" ");
  }
  else if (a ==2) {
  Serial.print("Y: "); Serial.print((int)lsm.accelData.y);       Serial.println(" ");
  }
  else if (a == 3) {
  Serial.print("Z: "); Serial.println((int)lsm.accelData.z);     Serial.println(" ");
  }
  else if (a == 4) {
  Serial.print("Mag X: "); Serial.print((int)lsm.magData.x);     Serial.println(" ");
  }
  else if (a == 5) {
  Serial.print("Y: "); Serial.print((int)lsm.magData.y);         Serial.println(" ");
  }
  else if (a == 6) {
  Serial.print("Z: "); Serial.println((int)lsm.magData.z);       Serial.println(" ");
  }
  else if (a ==7) {
  Serial.print("Gyro X: "); Serial.print((int)lsm.gyroData.x);   Serial.println(" ");
  }
  else if (a==8) {
  Serial.print("Y: "); Serial.print((int)lsm.gyroData.y);        Serial.println(" ");
  }
  else if (a==9) {
  Serial.print("Z: "); Serial.println((int)lsm.gyroData.z);      Serial.println(" ");
  }
  //Serial.print("Temp: "); Serial.print((int)lsm.temperature);    Serial.println(" ");
  delay(200);
}

// Debugging Loop
void Resp_to_key_motor(char b){
  if (b=='1'){
   a = 1;
  }
  else if (b=='2'){
    a = 2;
  }
  else if (b=='3'){
    a = 3;
  }
  else if (b=='4'){
    a = 4;
  }
  else if (b=='5'){
    a = 5;
  }
  
  else if (b=='6'){
    a = 6;
  }
  else if (b=='7'){
    a = 7;
  }
  else if (b=='8'){
    a = 8;
  }
  else if (b=='9'){
    a = 9;
  }
  else {
    a = 1;
  }

  }
