//http://www.electronics-lab.com/project/mp3-player-using-arduino-dfplayer-mini/
#include "SoftwareSerial.h"

SoftwareSerial serialConnMP3(3, 4);

#define MP3_START_BYTE 0x7E
#define MP3_VERSION_BYTE 0xFF
#define MP3_CMD_LEN 0x06
#define MP3_END_BYTE 0xEF
#define MP3_ACKNOWLEDGE 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
#define ACTIVATED LOW

boolean isPlaying = false;

void initMP3() {
  serialConnMP3.begin (9600);
  delay(1000);

  //init
  execute_serial_CMD(0x3F, 0, 1);
  delay(500);
  setVolumeMP3(18);
}

void playTrackMP3(int num)
{
  execute_serial_CMD(0x03, 0, num); 
}

void pauseMP3()
{
  execute_serial_CMD(0x0E,0,0);
  delay(500);
}

void playMP3()
{
  execute_serial_CMD(0x0D,0,1); 
  delay(500);
}

void playNextMP3()
{
  execute_serial_CMD(0x01,0,1);
  delay(500);
}

void playPreviousMP3()
{
  execute_serial_CMD(0x02,0,1);
  delay(500);
}

void setVolumeMP3(int volume)
{
  execute_serial_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(500);
}

void execute_serial_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
  // Calculate the checksum (2 bytes)
  word checksum = -(MP3_VERSION_BYTE + MP3_CMD_LEN + CMD + MP3_ACKNOWLEDGE + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { 
    MP3_START_BYTE, 
    MP3_VERSION_BYTE, 
    MP3_CMD_LEN, 
    CMD, 
    MP3_ACKNOWLEDGE,
    Par1, Par2, 
    highByte(checksum), 
    lowByte(checksum), 
    MP3_END_BYTE
    };
    
  //Send the command line to the module
  for (byte k=0; k<10; k++)
  {
    serialConnMP3.write( Command_line[k]);
  }
}
