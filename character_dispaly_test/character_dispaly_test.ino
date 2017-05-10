#include <SoftwareSerial.h>

// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)

void setup()
{
  mySerial.begin(9600); // set up serial port for 9600 baud
  mySerial.flush();
  delay(500); // wait for display to boot up
}

void loop()
{

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("                "); // clear display
  mySerial.write("                ");

  //line 1
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  mySerial.write("Hello, world!");

  //line 2
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(192);
  mySerial.write("goodnight moon");

  //line 3
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(148);
  mySerial.write("morning mars");

  //line 4
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(212);
  mySerial.write("goodnight phobos");
  
  while(1); // wait forever
}
