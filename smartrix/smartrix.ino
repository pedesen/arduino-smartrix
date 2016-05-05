#include "LedControl.h"

LedControl lc=LedControl(12,11,10,1);

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,15);

  Serial.begin(9600);
  Serial.println("Ready");
}

// Return the correct byte representation of an ASCII hex char
// Example: inChar = 'D' = 68  -->  13 = 1101
byte getByte(char inChar) {
  return inChar < 58 ? (inChar - 48) : (inChar - 55);
}

void loop() {

  if (Serial.available()) {

    char buffer[19];

    Serial.readBytesUntil(';', buffer, 19);

    // read the first byte - a hex char identifying the device (0-15)
    byte device = getByte(buffer[0]);

    // read the second byte - a hex char defining the number of rows
    byte num_rows = getByte(buffer[1]);

    // read the third byte - a hex char defining the number of columns
    byte num_cols = getByte(buffer[2]);

    // the number of bytes (must be a divisor of 4)
    byte num_bytes = ceil(float(num_rows * num_cols)/4);

    boolean leds[num_bytes*4];

    // read all remaining bytes
    for(int i=0; i<num_bytes; i++) {
      byte ledByte = getByte(buffer[i+3]);

      // for the first four bits of the byte get the boolean value (0 or 1)
      for(int j=0; j<4; j++) {
        leds[(i*4)+j] = bitRead(ledByte, 3-j);
      }
    }

    // iterate over rows and columns and set the LEDs
    for(int row=0; row<num_rows; row++) {
      for(int col=0; col<num_cols; col++) {
        lc.setLed(device, row, col, leds[(row*num_cols)+col]);
      }
    }
  }
}