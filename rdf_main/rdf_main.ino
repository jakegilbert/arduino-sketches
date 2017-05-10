
byte ATrssi[] = {0x7E,0x00,0x04,0x08,0x01,0x64,0x62,0x30}; //atcommand to retrive rssi

byte groundStation[] = {0x7E,0x00,0x0D,0x00,0x01,0x00,0x7D,0x33,0xA2,0x00,0x41,0x26,0x47,0x58,0x00,0x30,0x31,0xE2}; //ground station ping request
byte booster[] = {0x7E,0x00,0x0C,0x00,0x01,0x00,0x7D,0x33,0xA2,0x00,0x41,0x25,0xD1,0xF6,0x00,0x01,0x1B};
byte sustainer[]= {0x7E,0x00,0x0C,0x00,0x01,0x00,0x7D,0x33,0xA2,0x00,0x41,0x5A,0xD2,0x0B,0x00,0x01,0xD0};

int led1 = 19;
int led2 = 23;
int led3 = 21;
int led4 = 20;
int led5 = 22;

int sMode = 3; //when high sustainer
int bMode = 2; //when high booster

void setup() {
  Serial3.begin(38400);    //rdf radio serial port
  //Serial.begin(9600);     //usb serial port

  pinMode(sMode, INPUT_PULLUP);
  pinMode(bMode, INPUT_PULLUP);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);

  digitalWrite(led1,HIGH);
  delay(500);
  digitalWrite(led2,HIGH);
  delay(500);
  digitalWrite(led3,HIGH);
  delay(500);
  digitalWrite(led4,HIGH);
  delay(500);
  digitalWrite(led5,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);

}

void loop() {
  sendPing(groundStation);
  /*
  if(digitalRead(bMode) == 1){
    Serial.println("sending booster ping");
    sendPing(booster);
  }
  else if(digitalRead(sMode) == 1){
    Serial.println("sending sustainer ping");
    sendPing(sustainer);
  }
  */
  int rssival = rssi();
  Serial.print("rssi value is = ");
  Serial.println(rssival);
  
  int ledval = map(rssival,40,80,4,0); //110
  if(ledval == 0){
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
  else if(ledval == 1){
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
  else if(ledval == 2){
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
  else if(ledval == 3){
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,LOW);
  }
  else if(ledval == 4){
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,HIGH);
  }
  else {
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
  }
  
  delay(500);
}

void sendPing(byte *packet){
  char input[20] = {};
  int count = 0;
  
  Serial3.write(groundStation,sizeof(groundStation)); //send packet to remoteradio for ack back
  delay(500);

  while(Serial3.available() > 0){
    input[count] = Serial3.read();
    delay(5);
    count++;
    //Serial.println(count);
  }
  Serial.print("the recived count is = ");
  Serial.println(count);

  if(count == 7){
    digitalWrite(led1,HIGH);
  }
  else digitalWrite(led1,LOW);
  
  //for(int i =0;i<count;i++){
  //  Serial.println(input[i],HEX);
  //}
}

int rssi(){ //send rssi at command and read responce, send back db
  char input[20] = {};
  int count = 0;

  Serial3.write(ATrssi,sizeof(ATrssi));   //send at command for last rssi reading
  delay(100);
  while(Serial3.available() > 0){
    input[count] = Serial3.read();
    delay(5);
    count++;
    Serial.println(count);
  }
  //for(int i =0;i<count;i++){
  //  Serial.println(input[i],HEX);
  //}

  if(input[7] == 0 && input[8] != 0){
    return input[8];
  }
  
  else return -1;
}

