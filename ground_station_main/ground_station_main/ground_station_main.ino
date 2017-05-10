
#include <SoftwareSerial.h>


int alarmLED = 13;
int powerLED = 4;
int sError = 5;
int sComms = 9;
int sIgnite = 10;
int bError = 12;
int bComms = 14;
int bIgnite = 15;
 
int sArm = 1;
int sLaunch = 0;

int ledPins[] = {4, 5, 9, 10, 12, 13, 14, 15}; // an array of pin numbers to which LEDs are attached
int pinCount = 8;


// Attach the serial display's RX line to digital pin 2
//SoftwareSerial Serial1(3, 2); // pin 2 = TX, pin 3 = RX (unused)

String input = "";

void setup() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  pinMode(sArm, INPUT);
  pinMode(sLaunch, INPUT);

  digitalWrite(powerLED, HIGH);
  /*
  digitalWrite(alarmLED,HIGH);
  delay(10);
  digitalWrite(alarmLED,LOW);
  delay(300);
  digitalWrite(alarmLED,HIGH);
  delay(10);
  digitalWrite(alarmLED,LOW);
*/
  Serial.begin(9600); // baud rate
  Serial.flush();


  delay(500);
  Serial1.begin(9600); // set up serial port for 9600 baud
  //Serial1.flush();

  delay(1000); // wait for display to boot up
  Serial1.write(0x01);
  delay(10);
/*
  Serial1.write(254); // move cursor to beginning of first line
  Serial1.write(128);
  Serial1.write("                    "); // clear display
  delay(10); 
  Serial1.write(254); // move cursor to beginning of second line
  Serial1.write(192);
  Serial1.write("                    "); // clear display
  delay(10);
  Serial1.write(254); // move cursor to beginning of third line
  Serial1.write(148);
  Serial1.write("                    "); // clear display
  delay(10);
  Serial1.write(254); // move cursor to beginning of fourth line
  Serial1.write(212);
  Serial1.write("                    "); // clear display
  delay(50);
  */
}

void loop() {

  int sarm = digitalRead(sArm);
  int slaunch = digitalRead(sLaunch);
  input = "";
  if (Serial.available() > 0)
  {
    input = Serial.readStringUntil('\n');
  }

  if(input.indexOf("arm") > -1)
  {
    if(sarm)
    {
      Serial.println('A');
    }
    else
    {
      Serial.println('a');
    }
  }

  if(input.indexOf("launch") > -1)
  {
    if(slaunch)
    {
      Serial.println('L');
    }
    else
    {
      Serial.println('l');
    }
  }

  if (input.indexOf("serror") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(sError, HIGH);
    }
    else
      digitalWrite(sError, LOW);
  }

  else if (input.indexOf("scomm") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(sComms, HIGH);
    }
    else
      digitalWrite(sComms, LOW);
  }

  else if (input.indexOf("signite") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(sIgnite, HIGH);
    }
    else
      digitalWrite(sIgnite, LOW);
  }

  else if (input.indexOf("berror") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(bError, HIGH);
    }
    else
      digitalWrite(bError, LOW);
  }

  else if (input.indexOf("bcomm") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(bComms, HIGH);
    }
    else
      digitalWrite(bComms, LOW);
  }

  else if (input.indexOf("bignite") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(bIgnite, HIGH);
    }
    else
      digitalWrite(bIgnite, LOW);
  }

  else if (input.indexOf("alarm") > -1)
  {
    if ((input.indexOf("on")) > -1)
    {
      digitalWrite(alarmLED, HIGH);
    }
    else
      digitalWrite(alarmLED, LOW);
  }

  //display

  else if (input.indexOf("line1=") > -1)
  {
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(128);
    for (int i = input.indexOf('"') + 1; i < input.length(); i++)
    {
      Serial1.write(input[i]);
    }
  }

  else if (input.indexOf("line2=") > -1)
  {
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(192);
    for (int i = input.indexOf('"') + 1; i < input.length(); i++)
    {
      Serial1.write(input[i]);
    }
  }

  else if (input.indexOf("line3=") > -1)
  {
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(148);
    for (int i = input.indexOf('"') + 1; i < input.length(); i++)
    {
      Serial1.write(input[i]);
    }
  }

  else if (input.indexOf("line4=") > -1)
  {
    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(212);
    for (int i = input.indexOf('"') + 1; i < input.length(); i++)
    {
      Serial1.write(input[i]);
    }
  }
}

