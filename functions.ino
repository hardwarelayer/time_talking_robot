void initDevices() {

  pinMode(outputRGBLED, OUTPUT);

  initPIR();

  initFace();
  lcd.begin();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  dht.begin();         // Khởi động cảm biến

  initMP3();

  
}

void initPIR() {
  pinMode(inputPinPIR, INPUT);
  delay(2000); //heat up
}

void initSpecialChars() {
  lcd.createChar(0, O_cham);
  lcd.createChar(1, E_sac);
  lcd.createChar(2, traitim);
  lcd.createChar(3, degree);
}

void testBacklight() {
  lcd.backlight();
  delay(150);
  lcd.noBacklight();
  delay(150);
}

//only onetime!!!
void initRTCTime() {
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(30, 34, 22, 6, 15, 9, 2019); //Here you write your actual time/date as shown above 
  //but remember to "comment/remove" this function once you're done
  //The setup is done only one time and the module will continue counting it automatically
}

void welcomeMode() {
  lcd.clear();//Xóa màn hình

  lcd.setCursor(i_cur_x1, 0);
  lcd.print(txtMsg1);
  lcd.write(byte(0));
  lcd.print(txtMsg2);
  lcd.write(byte(2));

  lcd.setCursor(i_cur_x2, 1);
  lcd.print(txtMsg3);
  lcd.write(byte(1));
  lcd.print(txtMsg4);
  lcd.write(byte(2));

  if (i_cur_x1 + 1 + i_1st_line_len < 17) {
    i_cur_x1++;
  }
  else {
    i_cur_x1 = 0;
  }
  
  if (i_cur_x2 + 1 + i_2nd_line_len < 17) {
    i_cur_x2++;
  }
  else {
    i_cur_x2 = 0;
  }

}

//show heat and humid
void dataModeA() {
  
  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ

   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0); //dong dau
  lcd.print("Nhiet do: ");
  lcd.print(round(t));               //Xuất nhiệt độ
  lcd.print(" ");
  lcd.write(3);
  lcd.print("C");
  
  lcd.setCursor(2, 1); //xuong dong
  lcd.print("Do am: ");
  lcd.print(round(h));               //Xuất độ ẩm
  lcd.print(" %");
  

}

//show heatIndex
void dataModeB() {

  float h = dht.readHumidity();    //Đọc độ ẩm
  float t = dht.readTemperature(); //Đọc nhiệt độ

   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0); //dong dau
    Serial.print(F("DHT sensor failed!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0); //dong dau
  lcd.print("Chi so nhiet do:");
  lcd.setCursor(6, 1); //dong 2
  lcd.print(round(hic)); //heat index
  lcd.write(3);
  lcd.print("C");
}

void dataModeC() {
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();

  lcd.setCursor(0, 0); //dong 1
  // Start printing elements as individuals
  lcd.print("Ngay: ");
  lcd.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  
  lcd.setCursor(2, 1); //dong 2
  lcd.print("Gio: ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");

  String mySecStr = "";
  if(myRTC.seconds < 10){
    mySecStr += '0';
  }
  mySecStr += myRTC.seconds;
  mySecStr += "  "; //ko hieu sao bi in ra 2 ky tu rac o phia sau
  lcd.println(mySecStr);
}
