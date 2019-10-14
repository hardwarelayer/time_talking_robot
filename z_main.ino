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

#define ANNOUNCE_STEP_HEAD_ON 0
#define ANNOUNCE_STEP_FACE_ON 1
#define ANNOUNCE_STEP_SPEAK 2
#define ANNOUNCE_STEP_LCD_ON 3
#define ANNOUNCE_STEP_LCD_OFF 4
#define ANNOUNCE_STEP_FACE_OFF 5
#define ANNOUNCE_STEP_HEAD_OFF 6
#define ANNOUNCE_STEP_END 7

//de tranh viec xung nhieu sau khi ta ngung cap nguon cho qua trinh setup hoac announce
//se anh huong toi PIR
#define DELAY_AFTER_SETUP 70000
#define DELAY_BETWEEN_ANNOUNCE_AND_HELLO 70000

boolean bWaveHandUp = false;
boolean bWaveHandDown = false;
int iHandWaveStep = 0;
unsigned long iHandWaveDuration = 1000;
unsigned long iLastHandWave = 0;

unsigned long iLastSetupTime = 0;

boolean bHelloProcess = false;
int iHelloStep = 0;
unsigned long lastHelloProcessStepUp = 0;
unsigned long currentWaitHelloProcess = 0;
unsigned long lastHelloProcessStop = 0;

byte bSkipFirstAnnounce = false;
boolean bAnnounceProcess = false;
int iAnnounceStep = 0;
unsigned long lastAnnounceProcessStepUp = 0;
unsigned long currentWaitAnnounceProcess = 0;
unsigned long lastAnnounceProcessStop = 0;
unsigned long iLastAnnounceTime = 0;

unsigned long lastCommonStep = 0;
unsigned long lastCommonClock = 0;
unsigned long lastCommonFaceStep = 0;
unsigned long lastHourCheck = 0;
unsigned long lastPIRCheck = 0;
unsigned long PIR_CHECK_INTERVAL = 100;
unsigned long HOUR_CHECK_INTERVAL = 10000;
unsigned long COMMON_CLOCK_INTERVAL = 600;
unsigned long LCD_STEP_INTERVAL = 3000;
int iCurrentLCDMode = 0;
boolean bPlaySound = false;
int iPlaySoundStep = 0;
unsigned long lastPlaySoundCheck = 0;
unsigned long iPlaySoundDelay = 0;

boolean flgChangingToHelloState = false;
boolean flgChangingToAnnounceState = false;

unsigned long iLastPIRHighTime = 0;
#define PIR_DELAY_BEFORE_REPEAT_HELLO 600000
#define PIR_DELAY_BETWEEN_BEEP 60000

void setup(){
  //set time for module (onetime)
//  initRTCTime();
 
  Serial.begin(9600);
  
  initDevices();
  initSpecialChars();
  testBacklight();

  offFace();

  delay(2000);
  //init servo last to add a little ensure for power consumption of the LCD
  initServos();
  delay(2000);

//  consoleTest();

  iLastSetupTime = millis();
}

void initServos() {
  rightServo.attach(servoRightPin);
//  leftServo.attach(servoLeftPin);
  delay(1000);

  rightServo.write(180);
//  leftServo.write(180);

  for (int i = 0; i <= 180; i+=40) {
    rightServo.write(i);
    delay(500);
  }
  delay(1000);
  rightServo.write(0);
//  leftServo.write(0);
  delay(1000);
 
}

void greetingByHands() {

  if (millis() - iLastHandWave > iHandWaveDuration) {

    //Serial.print(F("step:"));
    //Serial.println(iHandWaveStep);
    
    if (iHandWaveStep == 0) {
      rightServo.write(180);
    }
    else if (iHandWaveStep == 1) {
//      leftServo.write(180);
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
      //leftServo.write(0);
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

void startAnnouncingMode() {
  Serial.println(F("Starting announcing"));
  bAnnounceProcess = true;
  iAnnounceStep = HELLO_STEP_HEAD_ON;
  lastAnnounceProcessStepUp = 0; //needed  for processHello to detect first run

  flgChangingToAnnounceState = false;
}

void processAnnounce() {

  boolean steppingUp = false;
  
  if (millis() - lastAnnounceProcessStepUp > currentWaitAnnounceProcess) {
    if (iAnnounceStep < ANNOUNCE_STEP_END) {
      if (lastAnnounceProcessStepUp > 0) {
        iAnnounceStep++;
        steppingUp = true;
      }
      else {
        //first time
        steppingUp = true;
      }
    }

    lastAnnounceProcessStepUp = millis();
  }

  switch (iAnnounceStep) {
    case ANNOUNCE_STEP_HEAD_ON:
      if (steppingUp) {
        //just enter, do once
        currentWaitAnnounceProcess = 1000;
      }
      digitalWrite(outputRGBLED, HIGH); //turn head on
      break;
    case ANNOUNCE_STEP_FACE_ON:
      if (steppingUp) {
        //just enter, do once
        flgShowFace = true;
        iCurFaceStep = 0;
        lastCommonFaceStep = 0;
        currentWaitAnnounceProcess = 1000;
      }
      break;
    case ANNOUNCE_STEP_SPEAK:
      bWaveHandUp = false;
      if (steppingUp) {
        //just enter, do once
        unsigned long iTotalDuration = buildAnnounceAudioScript();
        Serial.print(F("playing with total duration:")); Serial.println(iTotalDuration);
        
        //Khi lam viec voi chip
        //do tong thoi gian phat MP3 co the bi keo dai vi cach su dung millis() compare
        //la khong the chinh xac hoan toan duoc do cac thao tac I/O
        //nen luon phai du tru thoi gian cho viec keo dai nay
        //Mac du, doi voi DFPlayer ta co the dung pin BUSY de check viec phat MP3 xong chua, 
        //tuy nhien cung khong hoan toan chinh xac.
        currentWaitAnnounceProcess = iTotalDuration * 1.1;

        bPlaySound = true;
        iPlaySoundStep = 0;
        iPlaySoundDelay = 0;
        lastPlaySoundCheck = 0; //first audio will be played immediately

        setVolumeMP3(23);

      }

      if (bPlaySound) {
        audioHandling();
      }

      break;
    case ANNOUNCE_STEP_LCD_ON:
      if (steppingUp) {
        //just enter, do once
        setVolumeMP3(12);

        lcd.backlight();
        iCurrentLCDMode = 0;
        currentWaitAnnounceProcess = LCD_STEP_INTERVAL * LCD_MODE_COUNT;
      }
      break;
    case ANNOUNCE_STEP_LCD_OFF:
      if (steppingUp) {
        //just enter, do once
        lcd.noBacklight();
        currentWaitAnnounceProcess = 1000;
      }
      break;
    case ANNOUNCE_STEP_FACE_OFF:
      bWaveHandDown = false;
      if (steppingUp) {
        //just enter, do once
        iCurFaceStep = 0;
        flgShowFace = false;
        currentWaitAnnounceProcess = 2000;
        offFace();
      }
      break;
    case ANNOUNCE_STEP_HEAD_OFF:
      if (steppingUp) {
        //just enter, do once
        currentWaitAnnounceProcess = 2000;
        soundRobotStop();
      }
      digitalWrite(outputRGBLED, LOW);
      break;
    case ANNOUNCE_STEP_END:
      if (steppingUp) {
        //just enter, do once
        stopAnnounceMode();
      }
      break;
  }

  if (steppingUp) {
    /*
    Serial.print(F("Step: "));
    Serial.print(iAnnounceStep);
    Serial.print(F("Step total duration: "));
    Serial.println(currentWaitAnnounceProcess);
    */
    steppingUp = false;
  }

  if (bAnnounceProcess) {
    visualHandling();
  }

}

void stopAnnounceMode() {
  Serial.println(F("Stopping announce"));
  
  bAnnounceProcess = false;
  iAnnounceStep = ANNOUNCE_STEP_END;
  lastAnnounceProcessStepUp = 0;

  offFace();
  
  flgChangingToAnnounceState = false;
  lastAnnounceProcessStop = millis();

  iLastAnnounceTime = millis();
}

void startHelloMode() {
  Serial.println(F("Starting hello"));
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
      else {
        //first time
        steppingUp = true;
      }
    }

    lastHelloProcessStepUp = millis();
  }

  switch (iHelloStep) {
    case HELLO_STEP_HEAD_ON:
      if (steppingUp) {
        //just enter, do once
        soundRobotStart();
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

        setVolumeMP3(24);

      }

      if (bPlaySound) {
        audioHandling();
      }

      break;
    case HELLO_STEP_LCD_ON:
      if (steppingUp) {
        //just enter, do once
        setVolumeMP3(12);

        lcd.backlight();
        iCurrentLCDMode = 0;
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
        offFace();
      }
      break;
    case HELLO_STEP_HEAD_OFF:
      if (steppingUp) {
        //just enter, do once
        currentWaitHelloProcess = 2000;
        soundRobotStop();
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
    /*
    Serial.print(F("Step: "));
    Serial.print(iHelloStep);
    Serial.print(F("Step total duration: "));
    Serial.println(currentWaitHelloProcess);
    */
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
  Serial.println(F("Stopping hello"));
  
  bHelloProcess = false;
  iHelloStep = HELLO_STEP_END;
  lastHelloProcessStepUp = 0;

  offFace();
  
  lastHelloProcessStop = millis();
}

void soundBeep() {
  playTrackMP3(beepPos+1);
  iPlaySoundDelay = getFileDuration(beepPos);
  lastPlaySoundCheck = millis();
}

void soundRobotStart() {
  playTrackMP3(robotStartPos+1);
  iPlaySoundDelay = getFileDuration(robotStartPos);
  lastPlaySoundCheck = millis();
}

void soundRobotStop() {
  playTrackMP3(robotStopPos+1);
  iPlaySoundDelay = getFileDuration(robotStopPos);
  lastPlaySoundCheck = millis();
}

bool bPlayingSound = false;
void audioPlayCurrentStep() {
  
  if (!bPlaySound) return;

  if (bPlayingSound) return;

  bPlayingSound = true;

  AudioItem aItem = arScript[iPlaySoundStep];
  Serial.print(F("playing file:"));Serial.print(aItem.fileIndex);Serial.print(F(" duration:"));Serial.println(aItem.duration);
    
  playTrackMP3(aItem.fileIndex);
  iPlaySoundDelay = aItem.duration; //+100
                                    //neu cong them thoi gian o day thi thoi gian tong se bi lech dan toi
                                    //chua phat xong thi processHello da skip step roi
                                    //neu cong thi cong o ben buildScript
  lastPlaySoundCheck = millis();
}

void audioHandling() {

  unsigned long ulMillis = millis();
  unsigned long ulTimePassed = ulMillis - lastPlaySoundCheck;
  if (ulTimePassed >= iPlaySoundDelay) {
    Serial.print(F("audioHandling: "));Serial.print(ulMillis);Serial.print(F("-"));Serial.print(lastPlaySoundCheck);Serial.print(F("="));Serial.println(ulTimePassed);

    bPlayingSound = false; //reset it

    Serial.print(F("playing step: ")); Serial.println(iPlaySoundStep);
    if (iPlaySoundStep == iScriptLen && bAnnounceProcess) {
      //Serial.println(F("setting volume down for music in announce"));
      setVolumeMP3(17);
      delay(100);
    }

    audioPlayCurrentStep();

    if (iPlaySoundStep < iScriptLen) {
      
      iPlaySoundStep++;

    }
    else {
      //Serial.println(F("end of last sound"));
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

    if (iCurrentLCDMode < 3) {
      iCurrentLCDMode++;
      lcd.clear();//Xóa màn hình truoc moi mode
    }
    else {
      iCurrentLCDMode = 0;
    }

    lastCommonStep = millis();
    lastCommonClock = 0; //reset it to change mode immediately
  }

  if (millis() - lastCommonClock >= COMMON_CLOCK_INTERVAL) {
 
    switch(iCurrentLCDMode) {
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

int iLastHour = 0;
int iLastMinute = 0;

bool isHourJustChange() {
  bool flgRes = false;
  
  myRTC.updateTime(); 
  int i_hour = myRTC.hours;
  int i_minutes = myRTC.minutes;

  //debug
  //Serial.print(F("check min "));
  //Serial.println(i_minutes);
  //i_hour = i_minutes;

  //reset to 0 when value move from 59->0
  if (i_minutes < iLastMinute) {
    iLastMinute = i_minutes;
  }
  //reset to 0 when value move from 23->0
  if (i_hour < iLastHour) {
    iLastHour = i_hour;
  }

  if (
      (i_hour != iLastHour) &&
      (i_hour >= 6 && i_hour <= 22) &&
      (!flgChangingToAnnounceState && !bAnnounceProcess)
     )
  {
    
    iLastHour = i_hour;
    flgRes = true;
  }

  if (!flgRes) {
    //only notify minute change
    if (i_minutes > iLastMinute) {
//      soundBeep();
      iLastMinute = i_minutes;
    }
  }
  else {
    Serial.print(F("isHourJustChange is true"));
  }
  return flgRes;
}

void loop()
{
  int iCurMillis = millis();

  if (millis() - lastHourCheck >= HOUR_CHECK_INTERVAL) {
    if (!bAnnounceProcess && !bHelloProcess && isHourJustChange()) {
      if (!bSkipFirstAnnounce) {
        bSkipFirstAnnounce = true;
        return;
      }
      Serial.println(F("change hour"));
      flgChangingToAnnounceState = true;
      startAnnouncingMode();
      iLastAnnounceTime = millis();
    }
    lastHourCheck = millis();
  }

  if (
      (!flgChangingToAnnounceState && !bAnnounceProcess) && 
      (millis() - lastPIRCheck >= PIR_CHECK_INTERVAL)
     )
    {
     
      processPIR();

      if (pirState == HIGH && 
        !bHelloProcess && 
        (millis() - iLastAnnounceTime > DELAY_BETWEEN_ANNOUNCE_AND_HELLO) &&
        (millis() - iLastSetupTime > DELAY_AFTER_SETUP)
        )
      {

        if (lastHelloProcessStop > 0) {
          if (millis() - lastHelloProcessStop < 120000) {
            //vi dong cua servo co the lam nhieu tin hieu cua PIR
            //nen ta bat buoc phai doi khoang 2 phut truoc khi xu ly tin hieu PIR tiep
            //neu trong thoi gian cho doi nay, ta nhan duoc tin hieu LOW thi reset lastHelloProcessStop
            //Serial.println(F("Skipping PIR signal"));
            return;
          }
        }

        if (!flgChangingToHelloState) {
          //switch state from off to on, just do it one time in HIGH state
          //no hello, no announce
          if (
            (millis() - lastHelloProcessStop < PIR_DELAY_BEFORE_REPEAT_HELLO)
            )
          {
            if (millis() - iLastPIRHighTime > PIR_DELAY_BETWEEN_BEEP) {
              //soundBeep();
              rightServo.write(180);
              //leftServo.write(30);
              delay(getFileDuration(beepPos));
              rightServo.write(0);
              //leftServo.write(0);

              iLastPIRHighTime = millis();
            }
          }
          else {
            startHelloMode();
            flgChangingToHelloState = true;
          }

        }
        
        //doing smt else each PIR_CHECK_INTERVAL
      }
      else {
        if (flgChangingToHelloState) {
          //reset variables once to off mode
          flgChangingToHelloState = false;
        }
        //reset this to allow new PIR status
        //lastHelloProcessStop = 0;

      }

      lastPIRCheck = millis();

  }

  if (bHelloProcess) {
    processHello();
  }
  else if (bAnnounceProcess) {
    processAnnounce();
  }

}
