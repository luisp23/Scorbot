// voltage polarity pins
const int M1[6] = {31,35,39,43,47,48};
const int M2[6] = {33,37,41,45,49,46};

// used for array iteration ; index corresponds to specific axis
const int base = 0;
const int shoulder = 1;
const int elbow = 2;
const int gripper1 = 3;
const int gripper2 = 4;
const int gripper = 5;

//joystick inputs
const int joyBase = A0;
const int joyShoulder = A1;
const int joyElbow = A2;
const int joyGrpPitch = A3;
const int joyGrpRoll = A2;
const int joyGrp = A3;
const int joyLeftBtn = 2; // button on left joystick; used to switch modes

// joystick ranges
const int minJoyVal = 0;
const int midJoyVal = 512;
const int maxJoyVal = 1024;
const int neutralLower = midJoyVal - 100;
const int neutralUpper = midJoyVal + 100;

// joystick value ranges
int baseVal = midJoyVal;
int shoulderVal = midJoyVal;
int elbowVal = midJoyVal;
int grpPitchVal = midJoyVal;
int grpRollVal = midJoyVal;
int grpVal = midJoyVal;


void setup() {
  Serial.begin(9600);

// motors start stopped
  for (int i=0;i<6;i++) {
    pinMode(M1[i],OUTPUT);
    pinMode(M2[i],OUTPUT);
    motorSTT(M1[i],M2[i]);
  }
}

void loop() {
  scorbotControl();
  //armControl();
}

void scorbotControl(){

// determines mode based on whether the botton is pressed;  1 = pressed  0 = unpressed
  int leftBtnVal= digitalRead(joyLeftBtn);
  if(leftBtnVal == 0){
    readJoyMode1();
    armControl();
  } else if(leftBtnVal = 1){
    readJoyMode2();
    armControl2();
  }
}


void readJoyMode1(){                      // reads values for base shoulder elbow and gripper pitch
  baseVal = analogRead(joyBase);
//    Serial.print("Base Val: ");
//    Serial.println(baseVal);
  shoulderVal = analogRead(joyShoulder);
//    Serial.print("Shoulder Val: ");
//    Serial.println(shoulderVal);
  elbowVal = analogRead(joyElbow);
//    Serial.print("Elbow Val: ");
//    Serial.println(elbowVal);
  grpPitchVal = analogRead(joyGrpPitch);
//    Serial.print("GRP Pitch Val: ");
 //   Serial.println(grpPitchVal);

}

void readJoyMode2(){                    // reads values for base shoulder (left stick )        gripper roll / gripper (right stick)
  baseVal = analogRead(joyBase);
 //   Serial.print("Base Val: ");
 //   Serial.println(baseVal);
  shoulderVal = analogRead(joyShoulder);
 //   Serial.print("Shoulder Val: ");
 //   Serial.println(shoulderVal);
  grpRollVal = analogRead(joyGrpRoll);
    Serial.print("GRP ROLL Val: ");
    Serial.println(grpRollVal);
  grpVal = analogRead(joyGrp);
  //   Serial.println("GRIPPER: ");
  //   Serial.println(grpVal);
}


void armControl(){                  // control for mode 1
  if(baseVal > neutralUpper){
    FW(base);
  }else if(baseVal < neutralLower){
    BW(base);
  }else{
    motorST(base);
  }

  if(shoulderVal > neutralUpper ){
    FW(shoulder);
  }else if(shoulderVal < neutralLower){
    BW(shoulder);
  }else{
    motorST(shoulder);
  }

  if(elbowVal > neutralUpper){
    FW(elbow);
  }else if(elbowVal < neutralLower){
    BW(elbow);
  }else{
    motorST(elbow);
  }

  if(grpPitchVal > neutralUpper){
    grpPitchFW();
  }else if(grpPitchVal < neutralLower){
    grpPitchBW();
  }else{
    grpPRStop();
  }

}

void armControl2(){                 // control for mode 2

  if(grpRollVal > neutralUpper){
    grpRollFW();
    Serial.println("roll forward");
  }else if(grpRollVal < neutralLower){
    grpRollBW();
    Serial.println("roll backward");
  }else{
    grpPRStop();
  }

  if(grpVal > neutralUpper){
    grpClose();
  }else if(grpVal < neutralLower){
    grpOpen();
  }else{
    grpStop();
  }

}

//forward motion
void FW(int mtr){
  int MTR1 = M1[mtr];
  int MTR2 = M2[mtr];
  digitalWrite(MTR1, HIGH);
  digitalWrite(MTR2, LOW);
}

// backwards motion
void BW(int mtr){
  int MTR1 = M1[mtr];
  int MTR2 = M2[mtr];
  digitalWrite(MTR1, LOW);
  digitalWrite(MTR2, HIGH);
}

//motor stop Functions
void motorSTT(int mtr1, int mtr2  ){
  digitalWrite(mtr1, LOW);
  digitalWrite(mtr2, LOW);
}
void motorST(int mtr){
 int MTR1 = M1[mtr];
  int MTR2 = M2[mtr];
  digitalWrite(MTR1, LOW);
  digitalWrite(MTR2, LOW);
}

//gripper roll
void grpRollFW(){
  digitalWrite(M1[gripper1], HIGH);
  digitalWrite(M2[gripper1], LOW);
  digitalWrite(M1[gripper2], HIGH);
  digitalWrite(M2[gripper2], LOW);
}
void grpRollBW(){
  digitalWrite(M1[gripper1], LOW);
  digitalWrite(M2[gripper1], HIGH);
  digitalWrite(M1[gripper2], LOW);
  digitalWrite(M2[gripper2], HIGH);
}

//gripper pitch
void grpPitchFW(){               //TODO: figure out directions for roll;  FW = CW   BW = CCW
  digitalWrite(M1[gripper1], HIGH);
  digitalWrite(M2[gripper1], LOW);
  digitalWrite(M1[gripper2], LOW);
  digitalWrite(M2[gripper2], HIGH);
}
void grpPitchBW(){
  digitalWrite(M1[gripper1], LOW);
  digitalWrite(M2[gripper1], HIGH);
  digitalWrite(M1[gripper2], HIGH);
  digitalWrite(M2[gripper2], LOW);
}
void grpPRStop(){
  digitalWrite(M1[gripper1], LOW);
  digitalWrite(M2[gripper1], LOW);
  digitalWrite(M1[gripper2], LOW);
  digitalWrite(M2[gripper2], LOW);
}

// gripper open/close
void grpOpen(){
  digitalWrite(M1[gripper], HIGH);
  digitalWrite(M2[gripper], LOW);
}
void grpClose(){
  digitalWrite(M1[gripper], LOW);
  digitalWrite(M2[gripper], HIGH);
}
void grpStop(){
  digitalWrite(M1[gripper], LOW);
  digitalWrite(M2[gripper], LOW);
}
