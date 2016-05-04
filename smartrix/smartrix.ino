#include "LedControl.h"

LedControl lc=LedControl(12,11,10,1); 

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,15);
  
  Serial.begin(9600);
  Serial.println("Ready");
}

byte getByte(char inChar) {
  // returns the correct byte representation of an ASCII hex char
  // Example: inChar = 'D' = 68  -->  13 = 1101
  return inChar < 58 ? (inChar - 48) : (inChar - 55);
}

void loop() {
  
  if (Serial.available()) {
  
    char ledBuffer[10];
    
    // read the first byte - a hex char idenifying the device (0-15)
    byte device = getByte(Serial.read());
    
    // read the next 10 bytes - each byte is a hex char which contains
    // the binary status of four LEDs. Example: D = 1101
    Serial.readBytes(ledBuffer, 10);
    
    boolean leds[40];
    
    for(int i=0; i<10; i++) {
      // for each char in the ledBuffer
      // get the byte value
      byte ledByte = getByte(ledBuffer[i]);
      
      for(int j=0; j<4; j++) {
        // for the first four bits of the byte
        // get the boolean value (0 or 1)
        leds[(i*4)+j] = bitRead(ledByte, j);
      }
    }
    
    for(int i=0; i<8; i++) {
      // for each row i...
      for(int j=0; j<5; j++) {
        // for each column j...
        lc.setLed(device, i, j, leds[(i*5)+j]);
      }
    }
  }
}
