void processPIR() {
  int val = digitalRead(inputPinPIR);    //đọc giá trị đầu vào.

  if (val == HIGH)                //nếu giá trị ở mức cao.(HIGH - 1)
  {
    if (flgFirstPIRSignal == true) {
      return; //don't do anything on FIRST HIGH
    }

    if (pirState == LOW)
    {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  }
  else                      //Ngược lại
  {
    if (pirState == HIGH)
    {
      if (flgFirstPIRSignal == true) {
        flgFirstPIRSignal = false;
        return;
      }

      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}
