# arduino-smartrix
A message protocol for turning on or off LEDs in up to 16 MAX72xx matrices.

Info about the wiring: http://playground.arduino.cc/Main/MAX72XXHardware

## Message structure

One message contains information for up to 64 LEDs in a Matrix connected to one MAX72xx device (up to 16 devices are addressable)

* Byte 1: A hex char identifying the MAX72xx device (0 to 15)
* Byte 2: A hex char defining the number of rows (up to 8)
* Byte 3: A hex char defining the number of columns (up to 8)
* Bytes 4 to 19: Each byte is a hex char containing status information (on/off) for 4 LEDs (1 to 16 bytes)
* The last byte is a termination character (`;`)

## Example for a 4x3 LED Matrix

`1`: LED is on

`0`: LED is off

```
[[ 0, 0, 1 ],
 [ 0, 1, 0 ],
 [ 1, 1, 1 ],
 [ 0, 0, 0 ]]
```

Binary representation of the matrix:
`0010 1011 1000`

Hex representation of the matrix:
`2 B 8`

Serial message sent to the arduino:
`0432B8;`

The first byte (`0`) addresses the first MAX72xx device, the second byte (`4`) defines a number of 4 rows, the third byte (`3`) defines a number of 3 columns, bytes 4 to 6 (`2B8`) are the hex representation of the 4x3 matrix (see above). The last byte (`;`) is the termination byte.

## Example for a 8x8 LED Matrix

To turn on all LEDs of a 8x8 Matrix send this message to the Arduino

`088FFFFFFFFFFFFFFFF;`
