#define I2C_ADDR 0x27
const int DHTPIN = 2;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22

LiquidCrystal_I2C lcd(I2C_ADDR,16,2);
DHT dht(DHTPIN, DHTTYPE);

//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8
virtuabotixRTC myRTC(6, 7, 8);

//0x27 là địa chỉ màn hình trong bus I2C. Phần này chúng ta không cần phải quá bận tâm vì hầu hết màn hình (20x4,...) đều như thế này!
//16 là số cột của màn hình (nếu dùng loại màn hình 20x4) thì thay bằng 20
//2 là số dòng của màn hình (nếu dùng loại màn hình 20x4) thì thay bằng 4
byte traitim[8]={
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

byte O_cham[8] = {
  B00000,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00100,
};

byte E_sac[8] = {
  B00010,
  B00100,
  B01110,
  B10001,
  B11111,
  B10000,
  B01111,
  B00000,
};

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

int i_cur_x1 = 0;
int i_cur_x2 = 0;
String txtMsg1 = "Hi, Ng";
String txtMsg2 = "c Trung";
int i_1st_line_len = txtMsg1.length() + 1 + txtMsg2.length() + 1;
String txtMsg3 = "Hi, B";
String txtMsg4 = " Na";
int i_2nd_line_len = txtMsg3.length() + 1 + txtMsg4.length() + 1;


int inputPinPIR = 5;       //Chân tín hiệu cảm biến PIR
int pirState = LOW;     //Bắt đầu với không có báo động
boolean flgFirstPIRSignal = false;

int outputRGBLED = 13;
int servoRightPin = 17; //A3
int servoLeftPin = 14; //A0

Servo rightServo;
Servo leftServo;
