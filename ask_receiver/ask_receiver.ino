// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

//RH_ASK driver;
 RH_ASK driver(2000, 11, 12, 0); // ESP8266 or ESP32: do not use pin 11 or 2
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 


//TO CONTROL LED 
bool ledStates[] = {false,false,false,false}; 
byte ledPins[] = {8,7,3,2}; 

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

for (int i = 0; i<sizeof(ledStates);i++){
  pinMode(ledPins[i],OUTPUT);
  digitalWrite(ledPins[i],ledStates[i]);
}
//pinMode(led1Pin,OUTPUT);

}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	  
   Serial.print("Buflen:");
   Serial.println(buflen); 
   Serial.print("bufSize:");
   Serial.println(sizeof(buf));
   String cmd = "";
   int j =0; 
   while (j<buflen){
    cmd = cmd + (char )buf[j];
    j++;
   }
   Serial.print("Received CMD : ");
   Serial.println(cmd);
  // ToggleLED1();
    ProcessCMD(cmd); 
    }
   
}

void ProcessCMD(String cmd) {
  if (cmd == "T0") {
    ToggleLED(0);
  }
  else if (cmd == "T1") {
    ToggleLED(1);
  }
  else if (cmd == "T2") {
    ToggleLED(2);
  }
  else if (cmd == "T3") {
    ToggleLED(3);
  }
  else {
    Serial.println("Unknown command");
  }
  
  
}

void ToggleLED(int cmdNum) {
  ledStates[cmdNum] = !ledStates[cmdNum]; //if true, will make it false. if false, will make it true
  digitalWrite(ledPins[cmdNum],ledStates[cmdNum]);
  if (ledStates[cmdNum]) {
    Serial.println("Led"+String(cmdNum)+" On");
    
  }
  else {
    Serial.println("Led"+String(cmdNum)+" Off");
  }
}
