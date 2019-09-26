#define SIZE_OF_DURATIONS 219
#define ADDITIONAL_TIME_FOR_MP3_HANDLING 200

int baygiolaPos = 0;
int humidNowPos = 1;
int helloPos = 2;
int tempNowPos = 3;
int beepPos = 216;
int robotStartPos = 217;
int robotStopPos = 218;

int dayOfMonthAudioStartPos = 4;
int tempAudioStartPos = 35;
int minTempVal = 18;
int maxTempVal = 50;
int hourAudioStartPos = 68;
int minHourVal24 = 6;
int maxHourVal24 = 23;
int humidAudioStartPos = 87;
int minHumidVal = 50;
int maxHumidVal = 99;
int minutesAudioStartPos = 137;
int monthAudioStartPos = 197;
int dayOfWeekAudioStartPos = 209;
int arDurations[SIZE_OF_DURATIONS] = {
    1227, // 1, a_bicoi_baygiola.mp3
    835, // 2, a_bicoi_doam.mp3
    1306, // 3, a_bicoi_hello_xinchao_mono_32kbps.mp3
    2533, // 4, a_bicoi_nhietdobaygiola.mp3
    600, // 5, day_01.mp3
    679, // 6, day_02.mp3
    600, // 7, day_03.mp3
    600, // 8, day_04.mp3
    600, // 9, day_05.mp3
    757, // 10, day_06.mp3
    653, // 11, day_07.mp3
    574, // 12, day_08.mp3
    705, // 13, day_09.mp3
    653, // 14, day_10.mp3
    705, // 15, day_11.mp3
    914, // 16, day_12.mp3
    835, // 17, day_13.mp3
    809, // 18, day_14.mp3
    862, // 19, day_15.mp3
    888, // 20, day_16.mp3
    835, // 21, day_17.mp3
    940, // 22, day_18.mp3
    914, // 23, day_19.mp3
    862, // 24, day_20.mp3
    992, // 25, day_21.mp3
    1201, // 26, day_22.mp3
    1044, // 27, day_23.mp3
    1097, // 28, day_24.mp3
    1071, // 29, day_25.mp3
    1149, // 30, day_26.mp3
    1123, // 31, day_27.mp3
    1071, // 32, day_28.mp3
    1123, // 33, day_29.mp3
    966, // 34, day_30.mp3
    1149, // 35, day_31.mp3
    1097, // 36, dc_18.mp3
    1175, // 37, dc_19.mp3
    1071, // 38, dc_20.mp3
    1253, // 39, dc_21.mp3
    1280, // 40, dc_22.mp3
    1227, // 41, dc_23.mp3
    1306, // 42, dc_24.mp3
    1253, // 43, dc_25.mp3
    1384, // 44, dc_26.mp3
    1593, // 45, dc_27.mp3
    1306, // 46, dc_28.mp3
    1306, // 47, dc_29.mp3
    1018, // 48, dc_30.mp3
    1280, // 49, dc_31.mp3
    1253, // 50, dc_32.mp3
    1227, // 51, dc_33.mp3
    1306, // 52, dc_34.mp3
    1227, // 53, dc_35.mp3
    1332, // 54, dc_36.mp3
    1306, // 55, dc_37.mp3
    1280, // 56, dc_38.mp3
    1410, // 57, dc_39.mp3
    1071, // 58, dc_40.mp3
    1280, // 59, dc_41.mp3
    1253, // 60, dc_42.mp3
    1280, // 61, dc_43.mp3
    1306, // 62, dc_44.mp3
    1253, // 63, dc_45.mp3
    1384, // 64, dc_46.mp3
    1332, // 65, dc_47.mp3
    1280, // 66, dc_48.mp3
    1332, // 67, dc_49.mp3
    1488, // 68, dc_50.mp3
    1018, // 69, hr_1_6am.mp3
    966, // 70, hr_2_7am.mp3
    1044, // 71, hr_3_8am.mp3
    835, // 72, hr_4_9am.mp3
    940, // 73, hr_5_10am.mp3
    1071, // 74, hr_6_11_noon.mp3
    1071, // 75, hr_7_12_noon.mp3
    783, // 76, hr_8_1_pm.mp3
    835, // 77, hr_9_2pm.mp3
    809, // 78, hr_A_3pm.mp3
    835, // 79, hr_B_4pm.mp3
    992, // 80, hr_C_5pm.mp3
    757, // 81, hr_D_6pm.mp3
    862, // 82, hr_E_7pm.mp3
    966, // 83, hr_F_8pm.mp3
    862, // 84, hr_G_9pm.mp3
    809, // 85, hr_H_10pm.mp3
    1071, // 86, hr_I_11pm.mp3
    1854, // 87, hr_J_12pm.mp3
    1201, // 88, humid_50.mp3
    1306, // 89, humid_51.mp3
    1306, // 90, humid_52.mp3
    1306, // 91, humid_53.mp3
    1358, // 92, humid_54.mp3
    1280, // 93, humid_55.mp3
    1410, // 94, humid_56.mp3
    1306, // 95, humid_57.mp3
    1358, // 96, humid_58.mp3
    1436, // 97, humid_59.mp3
    1149, // 98, humid_60.mp3
    1436, // 99, humid_61.mp3
    1436, // 100, humid_62.mp3
    1410, // 101, humid_63.mp3
    1410, // 102, humid_64.mp3
    1384, // 103, humid_65.mp3
    1515, // 104, humid_66.mp3
    1462, // 105, humid_67.mp3
    1567, // 106, humid_68.mp3
    1436, // 107, humid_69.mp3
    1097, // 108, humid_70.mp3
    1332, // 109, humid_71.mp3
    1384, // 110, humid_72.mp3
    1332, // 111, humid_73.mp3
    1410, // 112, humid_74.mp3
    1306, // 113, humid_75.mp3
    1384, // 114, humid_76.mp3
    1358, // 115, humid_77.mp3
    1410, // 116, humid_78.mp3
    1358, // 117, humid_79.mp3
    1097, // 118, humid_80.mp3
    1358, // 119, humid_81.mp3
    1358, // 120, humid_82.mp3
    1358, // 121, humid_83.mp3
    1358, // 122, humid_84.mp3
    1280, // 123, humid_85.mp3
    1488, // 124, humid_86.mp3
    1358, // 125, humid_87.mp3
    1410, // 126, humid_88.mp3
    1384, // 127, humid_89.mp3
    1097, // 128, humid_90.mp3
    1306, // 129, humid_91.mp3
    1306, // 130, humid_92.mp3
    1175, // 131, humid_93.mp3
    1436, // 132, humid_94.mp3
    1358, // 133, humid_95.mp3
    1410, // 134, humid_96.mp3
    1384, // 135, humid_97.mp3
    1384, // 136, humid_98.mp3
    1541, // 137, humid_99.mp3
    548, // 138, min_0_0.mp3
    653, // 139, min_0_1.mp3
    679, // 140, min_0_2.mp3
    626, // 141, min_0_3.mp3
    731, // 142, min_0_4.mp3
    731, // 143, min_0_5.mp3
    705, // 144, min_0_6.mp3
    653, // 145, min_0_7.mp3
    705, // 146, min_0_8.mp3
    705, // 147, min_0_9.mp3
    626, // 148, min_1_0.mp3
    835, // 149, min_1_1.mp3
    966, // 150, min_1_2.mp3
    992, // 151, min_1_3.mp3
    940, // 152, min_1_4.mp3
    862, // 153, min_1_5.mp3
    992, // 154, min_1_6.mp3
    914, // 155, min_1_7.mp3
    940, // 156, min_1_8.mp3
    966, // 157, min_1_9.mp3
    914, // 158, min_2_0.mp3
    1071, // 159, min_2_1.mp3
    1097, // 160, min_2_2.mp3
    1201, // 161, min_2_3.mp3
    1149, // 162, min_2_4.mp3
    1123, // 163, min_2_5.mp3
    1175, // 164, min_2_6.mp3
    1149, // 165, min_2_7.mp3
    1149, // 166, min_2_8.mp3
    1123, // 167, min_2_9.mp3
    862, // 168, min_3_0.mp3
    1071, // 169, min_3_1.mp3
    1175, // 170, min_3_2.mp3
    1044, // 171, min_3_3.mp3
    1149, // 172, min_3_4.mp3
    1071, // 173, min_3_5.mp3
    1149, // 174, min_3_6.mp3
    1071, // 175, min_3_7.mp3
    1123, // 176, min_3_8.mp3
    1097, // 177, min_3_9.mp3
    888, // 178, min_4_0.mp3
    1175, // 179, min_4_1.mp3
    1227, // 180, min_4_2.mp3
    1097, // 181, min_4_3.mp3
    1201, // 182, min_4_4.mp3
    1123, // 183, min_4_5.mp3
    1201, // 184, min_4_6.mp3
    1149, // 185, min_4_7.mp3
    1175, // 186, min_4_8.mp3
    1149, // 187, min_4_9.mp3
    888, // 188, min_5_0.mp3
    1306, // 189, min_5_1.mp3
    1123, // 190, min_5_2.mp3
    1149, // 191, min_5_3.mp3
    1201, // 192, min_5_4.mp3
    1123, // 193, min_5_5.mp3
    1201, // 194, min_5_6.mp3
    1149, // 195, min_5_7.mp3
    1149, // 196, min_5_8.mp3
    1253, // 197, min_5_9.mp3
    1488, // 198, mo_1_Jan.mp3
    1384, // 199, mo_2_Feb.mp3
    1358, // 200, mo_3_Mar.mp3
    1280, // 201, mo_4_Apr.mp3
    1227, // 202, mo_5_May.mp3
    1253, // 203, mo_6_Jun.mp3
    1201, // 204, mo_7_Jul.mp3
    1227, // 205, mo_8_Aug.mp3
    1306, // 206, mo_9_Sep.mp3
    1358, // 207, mo_A_Oct.mp3
    1332, // 208, mo_B_Nov.mp3
    1724, // 209, mo_C_Dec.mp3
    1253, // 210, t2_fem.mp3
    1227, // 211, t3_fem.mp3
    1201, // 212, t4_fem.mp3
    1123, // 213, t5_fem.mp3
    1175, // 214, t6_fem.mp3
    992, // 215, t7_fem.mp3
    992, // 216, t8_fem.mp3
    549, // 217 beep
    1515, // 218 R2D2 start
    522, // 219 R2D2 stop
};

int getDayOfMonthFileIndex(int dayVal) {
  if (dayVal >= 1 && dayVal <= 31)
    return dayOfMonthAudioStartPos + (dayVal - 1);
  return -1;
}

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

int getFileDuration(int fileIndex) {
  if (fileIndex >= 0 && fileIndex <= SIZE_OF_DURATIONS)
    return arDurations[fileIndex] + ADDITIONAL_TIME_FOR_MP3_HANDLING;
  return -1;
}

typedef struct
{
  int fileIndex;
  int duration;
} AudioItem;

AudioItem arScript[11];
int iScriptLen = 0;

int buildHelloAudioScript() {

  int allDuration = 0;
  
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
  int iDuration = 0;

  //1. hello
  arScript[arIdx++] = (AudioItem) {helloPos+1, arDurations[helloPos]};
  allDuration += getFileDuration(helloPos);

  //2. bay gio la
  arScript[arIdx++] = (AudioItem) {baygiolaPos+1, arDurations[baygiolaPos]};
  allDuration += getFileDuration(baygiolaPos);

  //3. hour
  iFileIdx = getHourFileIndex(hour);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }
  
  //4. minute
  iFileIdx = getMinutesFileIndex(minutes);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }

  //5. day of week
  iFileIdx = getDayOfWeekFileIndex(dayOfWeek);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }
  
  //6. day of month
  iFileIdx = getDayOfMonthFileIndex(dayOfMonth);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }

  //7. month
  iFileIdx = getMonthFileIndex(month);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }

  //8. nhiet do hien thoi
  arScript[arIdx++] = (AudioItem) {tempNowPos+1, getFileDuration(tempNowPos)};
  
  //9. temp
  iFileIdx = getTemperatureFileIndex(temp);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx++] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }
  
  //10. do am
  arScript[arIdx++] = (AudioItem) {humidNowPos+1, getFileDuration(humidNowPos)};
  
  //11. humid
  iFileIdx = getHumidFileIndex(humid);
  if (iFileIdx >= 0) {
    iDuration = getFileDuration(iFileIdx);
    if (iDuration >= 0) {
      arScript[arIdx] = (AudioItem) {iFileIdx+1, iDuration};
      allDuration += iDuration;
    }
  }

  iScriptLen = arIdx;

  return allDuration;
}
