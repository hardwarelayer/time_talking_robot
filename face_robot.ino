//CHIP setting for face
//chân ST_CP - 12 của 74HC595
int faceLatchPin = 9;
//chân SH_CP - 11 của 74HC595
int faceClockPin = 12;
//Chân DS - 14 của 74HC595
int faceDataPin = 11;

//thu tu bit tuong ung led robot face la tu phai qua trai
//den theo thu tu:
//3      2
//1      4
//  8765
#define ALL_FACE_OFF 0
#define ALL_FACE_ON 0b11111111
#define TWO_EYE_ON 0b00000110
byte faceFaceSteps[7] = {
  0b00000001,
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0
};
#define FACE_STEP_INTERVAL 150

void initFace() {
  pinMode(faceLatchPin, OUTPUT);
  pinMode(faceClockPin, OUTPUT);
  pinMode(faceDataPin, OUTPUT);

  pushDataForFace(ALL_FACE_OFF);
  delay(1000);
  pushDataForFace(ALL_FACE_ON);
  delay(1000);
}


void pushDataForFace(int ledStatus) {
  digitalWrite(faceLatchPin, LOW); //các đèn LED sẽ không sáng khi bạn digital LOW
  shiftOut(faceDataPin, faceClockPin, MSBFIRST, ledStatus);  
  digitalWrite(faceLatchPin, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
}

void offFace() {
  pushDataForFace(ALL_FACE_OFF);
}

void blinkEyesOnly() {
  delay(200); 
  pushDataForFace(ALL_FACE_OFF);
  delay(250);
  pushDataForFace(TWO_EYE_ON);
  delay(250); 
}

int iCurFaceStep = 0;
boolean flgShowFace = false;
