#define LCD_MODE_WELCOME 0
#define LCD_MODE_A 1
#define LCD_MODE_B 2
#define LCD_MODE_C 3
#define LCD_MODE_COUNT 4

#define HELLO_STEP_HEAD_ON 0
#define HELLO_STEP_FACE_ON 1
#define HELLO_STEP_HAND_WAVE 2
#define HELLO_STEP_SPEAK 3
#define HELLO_STEP_LCD_ON 4
#define HELLO_STEP_LCD_OFF 5
#define HELLO_STEP_HAND_DOWN 6
#define HELLO_STEP_FACE_OFF 7
#define HELLO_STEP_HEAD_OFF 8
#define HELLO_STEP_END 9

boolean bWaveHandUp = false;
boolean bWaveHandDown = false;
int iHandWaveStep = 0;
unsigned long iHandWaveDuration = 2000;
unsigned long iLastHandWave = 0;

boolean bHelloProcess = false;
int iHelloStep = 0;
unsigned long lastHelloProcessStepUp = 0;
unsigned long currentWaitHelloProcess = 0;
unsigned long lastHelloProcessStop = 0;

unsigned long lastCommonStep = 0;
unsigned long lastCommonClock = 0;
unsigned long lastCommonFaceStep = 0;
unsigned long PIR_CHECK_INTERVAL = 100;
unsigned long COMMON_CLOCK_INTERVAL = 600;
unsigned long LCD_STEP_INTERVAL = 3000;
int i_cur_lcd_mode = 0;
boolean bPlaySound = false;
int iPlaySoundStep = 0;
unsigned long lastPlaySoundCheck = 0;
int iPlaySoundDelay = 0;

boolean flgChangingState = false;


void setup(){
  initServos();
  
  Serial.begin(9600);
  
  initDevices();
  initSpecialChars();
  testBacklight();

  //set time for module (onetime)
  //initRTCTime();

  consoleTest();
  offFace();

}

void initServos() {
  rightServo.attach(servoRightPin);
  delay(1000);
  leftServo.attach(servoLeftPin);
  delay(1000);

  rightServo.write(0);
  delay(1000);
  rightServo.write(20);
  delay(1000);
  rightServo.write(0);
  delay(1000);
  rightServo.write(90);
  delay(1000);
  rightServo.write(0);
  delay(1000);

  leftServo.write(0);
  delay(1000);
  leftServo.write(20);
  delay(1000);
  leftServo.write(0);
  delay(1000);
  leftServo.write(90);
  delay(1000);
  leftServo.write(0);
  delay(1000);

}

void consoleTest() {
  myRTC.updateTime();
  Serial.print("Thu:");
  Serial.print(myRTC.dayofweek);
  Serial.print("Ngay: ");
  Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.println(myRTC.year);

  int iHour = myRTC.hours;
  int iMinutes = myRTC.minutes;
  Serial.print("Gio: ");
  Serial.print(iHour);
  Serial.print("Phut: ");
  Serial.println(iMinutes);
  
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ

   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  else {
    Serial.print("Do am:");
    Serial.print(h);
    Serial.print(" Nhiet do: ");
    Serial.println(t);
  }
}

void greetingByHands() {

  if (millis() - iLastHandWave > iHandWaveDuration) {

    Serial.print("step:");
    Serial.println(iHandWaveStep);
    
    if (iHandWaveStep == 0) {
      rightServo.write(90);
    }
    else if (iHandWaveStep == 1) {
      leftServo.write(90);
    }

    if (iHandWaveStep < 1) {
      iHandWaveStep++;
    }
    else {
      bWaveHandUp = false;
    }

    iLastHandWave = millis();
  
  }
}

void stopGreetingByHands() {
  if (millis() - iLastHandWave > iHandWaveDuration) {

    if (iHandWaveStep == 0) {
      rightServo.write(0);
    }
    else if (iHandWaveStep == 1) {
      leftServo.write(0);
    }

    if (iHandWaveStep < 1) {
      iHandWaveStep++;
    }
    else {
      bWaveHandDown = false;
    }

    iLastHandWave = millis();

  }

}

void startHelloMode() {
  Serial.println("Starting hello");
  bHelloProcess = true;
  iHelloStep = HELLO_STEP_HEAD_ON;
  lastHelloProcessStepUp = 0; //needed  for processHello to detect first run
}

void processHello() {

  boolean steppingUp = false;
  
  if (millis() - lastHelloProcessStepUp > currentWaitHelloProcess) {
    if (iHelloStep < HELLO_STEP_END) {
      if (lastHelloProcessStepUp > 0) {
        iHelloStep++;
        steppingUp = true;
      }
    }

    lastHelloProcessStepUp = millis();
  }

  switch (iHelloStep) {
    case HELLO_STEP_HEAD_ON:
      if (steppingUp) {
        //just enter, do once
        currentWaitHelloProcess = 1000;       
      }
      digitalWrite(outputRGBLED, HIGH); //turn head on
      break;
    case HELLO_STEP_FACE_ON:
      if (steppingUp) {
        //just enter, do once
        flgShowFace = true;
        iCurFaceStep = 0;
        lastCommonFaceStep = 0;
        currentWaitHelloProcess = 1000;
      }
      break;
    case HELLO_STEP_HAND_WAVE:
      if (steppingUp) {
        //just enter, do once
        bWaveHandUp = true;
        iHandWaveStep = 0;
        iLastHandWave = 0;

        currentWaitHelloProcess = 5000;
      }
      break;
    case HELLO_STEP_SPEAK:
      bWaveHandUp = false;
      if (steppingUp) {
        //just enter, do once
        int iTotalDuration = buildHelloAudioScript();
        //Khi lam viec voi chip
        //do tong thoi gian phat MP3 co the bi keo dai vi cach su dung millis() compare
        //la khong the chinh xac hoan toan duoc do cac thao tac I/O
        //nen luon phai du tru thoi gian cho viec keo dai nay
        //Mac du, doi voi DFPlayer ta co the dung pin BUSY de check viec phat MP3 xong chua, 
        //tuy nhien cung khong hoan toan chinh xac.
        currentWaitHelloProcess = int(iTotalDuration * 1.5);

        bPlaySound = true;
        iPlaySoundStep = 0;
        iPlaySoundDelay = 0;
        lastPlaySoundCheck = 0; //first audio will be played immediately

        setVolumeMP3(12);

      }

      if (bPlaySound) {
        audioHandling();
      }

      break;
    case HELLO_STEP_LCD_ON:
      if (steppingUp) {
        //just enter, do once
        lcd.backlight();
        i_cur_lcd_mode = 0;
        currentWaitHelloProcess = LCD_STEP_INTERVAL * LCD_MODE_COUNT;
      }
      break;
    case HELLO_STEP_LCD_OFF:
      if (steppingUp) {
        //just enter, do once
        lcd.noBacklight();
        currentWaitHelloProcess = 1000;
      }
      break;
    case HELLO_STEP_HAND_DOWN:
      if (steppingUp) {
        //just enter, do once
        bWaveHandDown = true;
        iHandWaveStep = 0;
        iLastHandWave = 0;

        currentWaitHelloProcess = 5000;
      }
      break;
    case HELLO_STEP_FACE_OFF:
      bWaveHandDown = false;
      if (steppingUp) {
        //just enter, do once
        iCurFaceStep = 0;
        flgShowFace = false;
        currentWaitHelloProcess = 2000;
      }
      offFace();
      break;
    case HELLO_STEP_HEAD_OFF:
      if (steppingUp) {
        //just enter, do once
        currentWaitHelloProcess = 2000;
        soundBeep();
      }
      digitalWrite(outputRGBLED, LOW);
      break;
    case HELLO_STEP_END:
      if (steppingUp) {
        //just enter, do once
        stopHelloMode();
      }
      break;
  }

  if (steppingUp) {
    Serial.print("Step: ");
    Serial.print(iHelloStep);
    Serial.print("Step total duration: ");
    Serial.println(currentWaitHelloProcess);
    steppingUp = false;
  }

  if (bHelloProcess) {
    visualHandling();
  }

  if (bWaveHandUp) {
    greetingByHands();
  }
  else if (bWaveHandDown) {
    stopGreetingByHands();
  }

}

void stopHelloMode() {
  Serial.println("Stopping hello");
  
  bHelloProcess = false;
  iHelloStep = HELLO_STEP_END;
  lastHelloProcessStepUp = 0;

  offFace();
  
  lastHelloProcessStop = millis();
}

void soundBeep() {
  playTrackMP3(beepPos+1);
  iPlaySoundDelay = 300;
  lastPlaySoundCheck = millis();
}

void audioPlayCurrentStep() {
  AudioItem aItem = arScript[iPlaySoundStep];
  playTrackMP3(aItem.fileIndex);
  iPlaySoundDelay = aItem.duration; //+100
                                    //neu cong them thoi gian o day thi thoi gian tong se bi lech dan toi
                                    //chua phat xong thi processHello da skip step roi
                                    //neu cong thi cong o ben buildScript
}

void audioHandling() {
 
  if (millis() - lastPlaySoundCheck >= iPlaySoundDelay) {

    audioPlayCurrentStep();

    if (iPlaySoundStep < iScriptLen) {
      lastPlaySoundCheck = millis();
      
      iPlaySoundStep++;

    }
    else {
      Serial.println("play music");
      //setVolumeMP3(12);
      //playTrackMP3(6);
      bPlaySound = false;

    }
  }
}

void visualHandling() {

  if (millis() - lastCommonFaceStep >= FACE_STEP_INTERVAL) {
    pushDataForFace(faceFaceSteps[iCurFaceStep] | TWO_EYE_ON);
    if (iCurFaceStep < 6)
      iCurFaceStep++;
    else
      iCurFaceStep = 0;
    lastCommonFaceStep = millis();
  }

  if (millis() - lastCommonStep >= LCD_STEP_INTERVAL) {

    if (i_cur_lcd_mode < 3) {
      i_cur_lcd_mode++;
      lcd.clear();//Xóa màn hình truoc moi mode
    }
    else {
      i_cur_lcd_mode = 0;
    }

    lastCommonStep = millis();
    lastCommonClock = 0; //reset it to change mode immediately
  }

  if (millis() - lastCommonClock >= COMMON_CLOCK_INTERVAL) {
 
    switch(i_cur_lcd_mode) {
      case LCD_MODE_WELCOME:
        welcomeMode();
        break;
      case LCD_MODE_A:
        dataModeA();
        break;
      case LCD_MODE_B:
        dataModeB();
        break;
      case LCD_MODE_C:
       dataModeC();
       break;
    }

    lastCommonClock = millis();
  }

}

void loop()
{
  int iCurMillis = millis();
  
  if (millis() - lastCommonStep >= PIR_CHECK_INTERVAL) {

      processPIR();

      if (pirState == HIGH && !bHelloProcess) {

        if ((lastHelloProcessStop > 0) && (millis() - lastHelloProcessStop < 120000)) {
          //vi servo co the lam nhieu PIR
          //nen ta bat buoc phai doi khoang 2 phut truoc khi xu ly tin hieu PIR tiep
          //neu trong thoi gian cho doi nay, ta nhan duoc tin hieu LOW thi reset lastHelloProcessStop
          //Serial.println("Skipping PIR signal");
          return;
        }

        if (!flgChangingState) {
          //switch state from off to on, just do it one time in HIGH state
          startHelloMode();
          flgChangingState = true;
        }
        
        //doing smt else each PIR_CHECK_INTERVAL
      }
      else {
        if (flgChangingState) {
          //reset variables once to off mode
          flgChangingState = false;
        }
        //reset this to allow new PIR status
        lastHelloProcessStop = 0;
      }
  }

  if (bHelloProcess) {
    processHello();
  }
 
}
