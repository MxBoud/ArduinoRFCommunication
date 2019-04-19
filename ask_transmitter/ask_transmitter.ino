// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

//RH_ASK driver;
 RH_ASK driver(2000, 11, 12, 0); // ESP8266 or ESP32: do not use pin 11 or 2
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 
int i = 0;


//TO PROCESS SERIAL COMMAND 
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
	;
#endif
}

void loop()
{
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    char  cmdChar[inputString.length()]; 
      for (int i = 0; i< sizeof(cmdChar); i++){
        cmdChar[i] = (char *) inputString[i];
      }
    SendRFCmd(cmdChar); 
    inputString = "";
    stringComplete = false;
    
    
  }
  

    //SendRFCmd("T1");
 //delay(1000); 
  
    //const char *msg = "HelloWE";//+(char *) i;

    
}
void SendRFCmd(const char *cmd) {
  driver.send((uint8_t *)cmd, strlen(cmd));
    driver.waitPacketSent();
    Serial.print("CMD Sent:");
    Serial.println(cmd);
    delay(200);
    
  
}


/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    }
    else {
      inputString += inChar;
    }
    // add it to the inputString:
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    
  }
}
