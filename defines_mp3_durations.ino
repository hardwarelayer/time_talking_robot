const short SIZE_OF_DURATIONS = 253;
#define ADDITIONAL_TIME_FOR_MP3_HANDLING 200

byte baygiolaPos = 0;
byte humidNowPos = 1;
byte helloPos = 2;
byte tempNowPos = 3;
byte beepPos = 216;
byte robotStartPos = 217;
byte robotStopPos = 218;
byte tcMusicStartPos = 219;
byte tcMusicStopPos = 251;
byte tcMusicIndex = 0;
byte spunikBeep = 252; //beware for the byte limit

byte dayOfMonthAudioStartPos = 4;
byte tempAudioStartPos = 35;
byte minTempVal = 18;
byte maxTempVal = 50;
byte hourAudioStartPos = 68;
byte minHourVal24 = 6;
byte maxHourVal24 = 23;
byte humidAudioStartPos = 87;
byte minHumidVal = 50;
byte maxHumidVal = 99;
byte minutesAudioStartPos = 137;
byte monthAudioStartPos = 197;
byte dayOfWeekAudioStartPos = 209;

const unsigned long arDurations[SIZE_OF_DURATIONS] PROGMEM = {
    1227UL, // 1, a_bc_baygiola.mp3
    835UL, // 2, a_bc_doam.mp3
    1306UL, // 3, a_bc_hello_xinchao_mono_32kbps.mp3
    2533UL, // 4, a_bc_nhietdobaygiola.mp3
    600UL, // 5, day_01.mp3
    679UL, // 6, day_02.mp3
    600UL, // 7, day_03.mp3
    600UL, // 8, day_04.mp3
    600UL, // 9, day_05.mp3P
    757UL, // 10, day_06.mp3
    653UL, // 11, day_07.mp3
    574UL, // 12, day_08.mp3
    705UL, // 13, day_09.mp3
    653UL, // 14, day_10.mp3
    705UL, // 15, day_11.mp3
    914UL, // 16, day_12.mp3
    835UL, // 17, day_13.mp3
    809UL, // 18, day_14.mp3
    862UL, // 19, day_15.mp3
    888UL, // 20, day_16.mp3
    835UL, // 21, day_17.mp3
    940UL, // 22, day_18.mp3
    914UL, // 23, day_19.mp3
    862UL, // 24, day_20.mp3
    992UL, // 25, day_21.mp3
    1201UL, // 26, day_22.mp3
    1044UL, // 27, day_23.mp3
    1097UL, // 28, day_24.mp3
    1071UL, // 29, day_25.mp3
    1149UL, // 30, day_26.mp3
    1123UL, // 31, day_27.mp3
    1071UL, // 32, day_28.mp3
    1123UL, // 33, day_29.mp3
    966UL, // 34, day_30.mp3
    1149UL, // 35, day_31.mp3
    1097UL, // 36, dc_18.mp3
    1175UL, // 37, dc_19.mp3
    1071UL, // 38, dc_20.mp3
    1253UL, // 39, dc_21.mp3
    1280UL, // 40, dc_22.mp3
    1227UL, // 41, dc_23.mp3
    1306UL, // 42, dc_24.mp3
    1253UL, // 43, dc_25.mp3
    1384UL, // 44, dc_26.mp3
    1593UL, // 45, dc_27.mp3
    1306UL, // 46, dc_28.mp3
    1306UL, // 47, dc_29.mp3
    1018UL, // 48, dc_30.mp3
    1280UL, // 49, dc_31.mp3
    1253UL, // 50, dc_32.mp3
    1227UL, // 51, dc_33.mp3
    1306UL, // 52, dc_34.mp3
    1227UL, // 53, dc_35.mp3
    1332UL, // 54, dc_36.mp3
    1306UL, // 55, dc_37.mp3
    1280UL, // 56, dc_38.mp3
    1410UL, // 57, dc_39.mp3
    1071UL, // 58, dc_40.mp3
    1280UL, // 59, dc_41.mp3
    1253UL, // 60, dc_42.mp3
    1280UL, // 61, dc_43.mp3
    1306UL, // 62, dc_44.mp3
    1253UL, // 63, dc_45.mp3
    1384UL, // 64, dc_46.mp3
    1332UL, // 65, dc_47.mp3
    1280UL, // 66, dc_48.mp3
    1332UL, // 67, dc_49.mp3
    1488UL, // 68, dc_50.mp3
    1018UL, // 69, hr_1_6am.mp3
    966UL, // 70, hr_2_7am.mp3
    1044UL, // 71, hr_3_8am.mp3
    835UL, // 72, hr_4_9am.mp3
    940UL, // 73, hr_5_10am.mp3
    1071UL, // 74, hr_6_11_noon.mp3
    1071UL, // 75, hr_7_12_noon.mp3
    783UL, // 76, hr_8_1_pm.mp3
    835UL, // 77, hr_9_2pm.mp3
    809UL, // 78, hr_A_3pm.mp3
    835UL, // 79, hr_B_4pm.mp3
    992UL, // 80, hr_C_5pm.mp3
    757UL, // 81, hr_D_6pm.mp3
    862UL, // 82, hr_E_7pm.mp3
    966UL, // 83, hr_F_8pm.mp3
    862UL, // 84, hr_G_9pm.mp3
    809UL, // 85, hr_H_10pm.mp3
    1071UL, // 86, hr_I_11pm.mp3
    1854UL, // 87, hr_J_12pm.mp3
    1201UL, // 88, humid_50.mp3
    1306UL, // 89, humid_51.mp3
    1306UL, // 90, humid_52.mp3
    1306UL, // 91, humid_53.mp3
    1358UL, // 92, humid_54.mp3
    1280UL, // 93, humid_55.mp3
    1410UL, // 94, humid_56.mp3
    1306UL, // 95, humid_57.mp3
    1358UL, // 96, humid_58.mp3
    1436UL, // 97, humid_59.mp3
    1149UL, // 98, humid_60.mp3
    1436UL, // 99, humid_61.mp3
    1436UL, // 100, humid_62.mp3
    1410UL, // 101, humid_63.mp3
    1410UL, // 102, humid_64.mp3
    1384UL, // 103, humid_65.mp3
    1515UL, // 104, humid_66.mp3
    1462UL, // 105, humid_67.mp3
    1567UL, // 106, humid_68.mp3
    1436UL, // 107, humid_69.mp3
    1097UL, // 108, humid_70.mp3
    1332UL, // 109, humid_71.mp3
    1384UL, // 110, humid_72.mp3
    1332UL, // 111, humid_73.mp3
    1410UL, // 112, humid_74.mp3
    1306UL, // 113, humid_75.mp3
    1384UL, // 114, humid_76.mp3
    1358UL, // 115, humid_77.mp3
    1410UL, // 116, humid_78.mp3
    1358UL, // 117, humid_79.mp3
    1097UL, // 118, humid_80.mp3
    1358UL, // 119, humid_81.mp3
    1358UL, // 120, humid_82.mp3
    1358UL, // 121, humid_83.mp3
    1358UL, // 122, humid_84.mp3
    1280UL, // 123, humid_85.mp3
    1488UL, // 124, humid_86.mp3
    1358UL, // 125, humid_87.mp3
    1410UL, // 126, humid_88.mp3
    1384UL, // 127, humid_89.mp3
    1097UL, // 128, humid_90.mp3
    1306UL, // 129, humid_91.mp3
    1306UL, // 130, humid_92.mp3
    1175UL, // 131, humid_93.mp3
    1436UL, // 132, humid_94.mp3
    1358UL, // 133, humid_95.mp3
    1410UL, // 134, humid_96.mp3
    1384UL, // 135, humid_97.mp3
    1384UL, // 136, humid_98.mp3
    1541UL, // 137, humid_99.mp3
    548UL, // 138, min_0_0.mp3
    653UL, // 139, min_0_1.mp3
    679UL, // 140, min_0_2.mp3
    626UL, // 141, min_0_3.mp3
    731UL, // 142, min_0_4.mp3
    731UL, // 143, min_0_5.mp3
    705UL, // 144, min_0_6.mp3
    653UL, // 145, min_0_7.mp3
    705UL, // 146, min_0_8.mp3
    705UL, // 147, min_0_9.mp3
    626UL, // 148, min_1_0.mp3
    835UL, // 149, min_1_1.mp3
    966UL, // 150, min_1_2.mp3
    992UL, // 151, min_1_3.mp3
    940UL, // 152, min_1_4.mp3
    862UL, // 153, min_1_5.mp3
    992UL, // 154, min_1_6.mp3
    914UL, // 155, min_1_7.mp3
    940UL, // 156, min_1_8.mp3
    966UL, // 157, min_1_9.mp3
    914UL, // 158, min_2_0.mp3
    1071UL, // 159, min_2_1.mp3
    1097UL, // 160, min_2_2.mp3
    1201UL, // 161, min_2_3.mp3
    1149UL, // 162, min_2_4.mp3
    1123UL, // 163, min_2_5.mp3
    1175UL, // 164, min_2_6.mp3
    1149UL, // 165, min_2_7.mp3
    1149UL, // 166, min_2_8.mp3
    1123UL, // 167, min_2_9.mp3
    862UL, // 168, min_3_0.mp3
    1071UL, // 169, min_3_1.mp3
    1175UL, // 170, min_3_2.mp3
    1044UL, // 171, min_3_3.mp3
    1149UL, // 172, min_3_4.mp3
    1071UL, // 173, min_3_5.mp3
    1149UL, // 174, min_3_6.mp3
    1071UL, // 175, min_3_7.mp3
    1123UL, // 176, min_3_8.mp3
    1097UL, // 177, min_3_9.mp3
    888UL, // 178, min_4_0.mp3
    1175UL, // 179, min_4_1.mp3
    1227UL, // 180, min_4_2.mp3
    1097UL, // 181, min_4_3.mp3
    1201UL, // 182, min_4_4.mp3
    1123UL, // 183, min_4_5.mp3
    1201UL, // 184, min_4_6.mp3
    1149UL, // 185, min_4_7.mp3
    1175UL, // 186, min_4_8.mp3
    1149UL, // 187, min_4_9.mp3
    888UL, // 188, min_5_0.mp3
    1306UL, // 189, min_5_1.mp3
    1123UL, // 190, min_5_2.mp3
    1149UL, // 191, min_5_3.mp3
    1201UL, // 192, min_5_4.mp3
    1123UL, // 193, min_5_5.mp3
    1201UL, // 194, min_5_6.mp3
    1149UL, // 195, min_5_7.mp3
    1149UL, // 196, min_5_8.mp3
    1253UL, // 197, min_5_9.mp3
    1488UL, // 198, mo_1_Jan.mp3
    1384UL, // 199, mo_2_Feb.mp3
    1358UL, // 200, mo_3_Mar.mp3
    1280UL, // 201, mo_4_Apr.mp3
    1227UL, // 202, mo_5_May.mp3
    1253UL, // 203, mo_6_Jun.mp3
    1201UL, // 204, mo_7_Jul.mp3
    1227UL, // 205, mo_8_Aug.mp3
    1306UL, // 206, mo_9_Sep.mp3
    1358UL, // 207, mo_A_Oct.mp3
    1332UL, // 208, mo_B_Nov.mp3
    1724UL, // 209, mo_C_Dec.mp3
    1253UL, // 210, t2_fem.mp3
    1227UL, // 211, t3_fem.mp3
    1201UL, // 212, t4_fem.mp3
    1123UL, // 213, t5_fem.mp3
    1175UL, // 214, t6_fem.mp3
    992UL, // 215, t7_fem.mp3
    992UL, // 216, t8_fem.mp3
    548UL, // 217, z_beep.mp3
    1515UL, // 218, z_r2d2_start.mp3
    470UL, // 219, z_r2d2_stop.mp3
    79072, // 220, z_TC_00.mp3
    323186, // 221, z_TC_01.mp3
    138344, // 222, z_TC_02.mp3
    161175, // 223, z_TC_03.mp3
    178285, // 224, z_TC_04.mp3
    148088, // 225, z_TC_05.mp3
    117080, // 226, z_TC_06.mp3
    208431, // 227, z_TC_07.mp3
    201116, // 228, z_TC_08.mp3
    292493, // 229, z_TC_09.mp3
    201665, // 230, z_TC_10.mp3
    176378, // 231, z_TC_11.mp3
    354351, // 232, z_TC_12.mp3
    218827, // 233, z_TC_13.mp3
    227944, // 234, z_TC_14.mp3
    196545, // 235, z_TC_15.mp3
    309577, // 236, z_TC_16.mp3
    156133, // 237, z_TC_17.mp3
    162089, // 238, z_TC_18.mp3
    179173, // 239, z_TC_19.mp3
    336744, // 240, z_TC_20.mp3
    215902, // 241, z_TC_21.mp3
    283898, // 242, z_TC_22.mp3
    232176, // 243, z_TC_23.mp3
    101982, // 244, z_TC_24.mp3
    60917, // 245, z_TC_25.mp3
    351608, // 246, z_TC_26.mp3
    162089, // 247, z_TC_27.mp3
    164911, // 248, z_TC_28.mp3
    190328, // 249, z_TC_29.mp3
    227840, // 250, z_TC_30.mp3
    132963, // 251, z_TC_31.mp3
    310151, // 252, z_TC_32.mp3 
    2256UL, // 253, z_u_sputnik-beep.mp3 
};

int getTemperatureFileIndex(int tempVal) {
  if (tempVal >= minTempVal && tempVal <= maxTempVal) {
    return tempAudioStartPos + (tempVal - minTempVal);
  }

  return -1;
}

int getHourFileIndex(int hourVal) {
  if (hourVal >= minHourVal24 && hourVal <= maxHourVal24) {
    return hourAudioStartPos + (hourVal - minHourVal24);
  }

  return -1;
}

int getHumidFileIndex(int humidVal) {
  if (humidVal >= minHumidVal && humidVal <= maxHumidVal) {
    return humidAudioStartPos + (humidVal - minHumidVal);
  }

  return -1;
}

int getMinutesFileIndex(int minuteVal) {
  if (minuteVal >= 0 && minuteVal <= 59)
    return minutesAudioStartPos + (minuteVal);
  return -1;
}

int getMonthFileIndex(int monthVal) {
  if (monthVal >= 1 && monthVal <= 12)
    return monthAudioStartPos + (monthVal - 1);
  return -1;
}

int getDayOfWeekFileIndex(int dowVal) {
  if (dowVal >= 0 && dowVal <= 6)
    return dayOfWeekAudioStartPos + (dowVal);
  return -1;
}


unsigned long getFileDuration(int fileIndex) {

  if (fileIndex >= 0 && fileIndex <= SIZE_OF_DURATIONS) {
    unsigned long ulDuration;
    PROGMEM_readAnything (&arDurations[fileIndex], ulDuration);
    return ulDuration;
  }
  return 0;
}

typedef struct
{
  int fileIndex;
  unsigned long duration;
} AudioItem;

AudioItem arScript[11];
byte iScriptLen = 0;

unsigned long buildHelloAudioScript() {

  unsigned long allDuration = 0;
  
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
   // Check if any reads failed && exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  else {
    Serial.print(h);
    Serial.print(" ");
    Serial.println(t);
  }
  int hour = myRTC.hours;
  int minutes = myRTC.minutes;
  int dayOfWeek = myRTC.dayofweek;
  int dayOfMonth = myRTC.dayofmonth;
  int month = myRTC.month;
  int temp = int(t);
  int humid = int(h);

  int arIdx = 0;
  int iFileIdx = 0;
  unsigned long ulDuration;

  //1. hello
  arScript[arIdx++] = (AudioItem) {helloPos+1, getFileDuration(helloPos) };
  allDuration += getFileDuration(helloPos);

  //2. bay gio la
  arScript[arIdx++] = (AudioItem) {baygiolaPos+1, getFileDuration(baygiolaPos)};
  allDuration += getFileDuration(baygiolaPos);

  //3. hour
  iFileIdx = getHourFileIndex(hour);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }
  
  //4. minute
  iFileIdx = getMinutesFileIndex(minutes);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }

  //5. day of week
  iFileIdx = getDayOfWeekFileIndex(dayOfWeek);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }
  
  //6. day of month
  if (dayOfMonth >= 1 && dayOfMonth <= 31) {
    iFileIdx = dayOfMonthAudioStartPos + (dayOfMonth - 1);
    
    if (iFileIdx >= 0) {
      ulDuration = getFileDuration(iFileIdx);
      if (atol(ulDuration) >= 0); {
        arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
        allDuration += ulDuration;
      }
    }
    
  }

  //7. month
  iFileIdx = getMonthFileIndex(month);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }

  //8. nhiet do hien thoi
  arScript[arIdx++] = (AudioItem) {tempNowPos+1, getFileDuration(tempNowPos)};
  
  //9. temp
  iFileIdx = getTemperatureFileIndex(temp);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }
  
  //10. do am
  arScript[arIdx++] = (AudioItem) {humidNowPos+1, getFileDuration(humidNowPos)};
  
  //11. humid
  iFileIdx = getHumidFileIndex(humid);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }

  iScriptLen = arIdx;

  return allDuration;
}

/////////////////////////////////////////////

unsigned long buildAnnounceAudioScript() {

  unsigned long allDuration = 0;
  
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ
   // Check if any reads failed && exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("DHT err!"));
  }
  else {
    Serial.print(h);
    Serial.print(F(" "));
    Serial.println(t);
  }
  int hour = myRTC.hours;
  int minutes = myRTC.minutes;
  int dayOfWeek = myRTC.dayofweek;
  int dayOfMonth = myRTC.dayofmonth;
  int month = myRTC.month;

  int arIdx = 0;
  int iFileIdx = 0;
  int ulDuration = 0;

  //1. Sputnik beep
  arScript[arIdx++] = (AudioItem) {spunikBeep+1, getFileDuration(spunikBeep) };
  allDuration += getFileDuration(spunikBeep);

  //2. bay gio la
  arScript[arIdx++] = (AudioItem) {baygiolaPos+1, getFileDuration(baygiolaPos)};
  allDuration += getFileDuration(baygiolaPos);

  //3. hour
  iFileIdx = getHourFileIndex(hour);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }
  
  //4. minute
  iFileIdx = getMinutesFileIndex(minutes);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }

  //5. day of week
  iFileIdx = getDayOfWeekFileIndex(dayOfWeek);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }
  
  //6. day of month
  if (dayOfMonth >= 1 && dayOfMonth <= 31) {
    iFileIdx = dayOfMonthAudioStartPos + (dayOfMonth - 1);
    if (iFileIdx >= 0) {
      ulDuration = getFileDuration(iFileIdx);
      if (atol(ulDuration) >= 0); {
        arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
        allDuration += ulDuration;
      }
    }
  }

  //7. month
  iFileIdx = getMonthFileIndex(month);
  if (iFileIdx >= 0) {
    ulDuration = getFileDuration(iFileIdx);
    if (atol(ulDuration) >= 0); {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, ulDuration};
      allDuration += ulDuration;
    }
  }

  //music
  if (dayOfMonth % 2 == 0) {
    //ngay chan, TC start from 0
    tcMusicIndex = hour - minHourVal24;
  }
  else {
    //ngay le
    //TC start from 16
    tcMusicIndex = (hour+16)-minHourVal24;
  }
  
  int iSelectedMusic = tcMusicIndex + tcMusicStartPos;
  Serial.print(F("Music: "));
  Serial.println(iSelectedMusic);
  ///last script item, don't count
  arScript[arIdx] = (AudioItem) {iSelectedMusic+1, getFileDuration(iSelectedMusic)};
  allDuration += getFileDuration(iSelectedMusic);

  iScriptLen = arIdx;

  return allDuration;
}
