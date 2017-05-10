#include <SoftwareSerial.h>

// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)

void setup()
{
  mySerial.begin(9600); // set up serial port for 9600 baud
  mySerial.flush();

  Serial.begin(9600); // baud rate
  Serial.flush();
    
  delay(500); // wait for display to boot up

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
  mySerial.write("                    "); // clear display
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(192);
  mySerial.write("                    "); // clear display
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(148);
  mySerial.write("                    "); // clear display
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(212);
  mySerial.write("                    "); // clear display
}

void loop() {
  String input = "";
 
  // Read any serial input
  while (Serial.available() > 0)
  {
      input += (char) Serial.read(); // Read in one char at a time
      delay(5); // Delay for 5 ms so the next char has time to be received
  }

  if(input.indexOf("line1=") > -1)
  {
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(128);
    for(int i=input.indexOf('"')+1;i<input.length();i++)
    {
      mySerial.write(input[i]);
    }
  }

  if(input.indexOf("line2=") > -1)
  {
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(192);
    for(int i=input.indexOf('"')+1;i<input.length();i++)
    {
      mySerial.write(input[i]);
    }
  }

  if(input.indexOf("line3=") > -1)
  {
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(148);
    for(int i=input.indexOf('"')+1;i<input.length();i++)
    {
      mySerial.write(input[i]);
    }
  }

  if(input.indexOf("line4=") > -1)
  {
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(212);
    for(int i=input.indexOf('"')+1;i<input.length();i++)
    {
      mySerial.write(input[i]);
    }
  }
}
