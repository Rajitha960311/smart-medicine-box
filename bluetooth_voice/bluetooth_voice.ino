#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

int pushButton = 7;   // input pin (for a pushbutton)
int pushBtnStatus = 0;     // variable for reading the pin status

char ch;
String medInfo = "";
String voiceInput = "";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton, INPUT);    // declare pushbutton as input

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  //Serial.print("UID tag :");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  Serial.println(content.substring(1));
  delay(5000);

  
   pushBtnStatus = digitalRead(pushButton);  // read input value
   
  if(Serial.available()){
    //ch = Serial.read();
    //Serial.write(ch);

    voiceInput = Serial.readStringUntil('\n');
    Serial.println(voiceInput);
    
  }

  if (pushBtnStatus == HIGH) {         // check if the input is HIGH (button pressed)
    delay(1000);
    doWork1(voiceInput);
    voiceInput="";
  } else {
     
  }

}

void doWork1(String voiceInput){

 medInfo = medInfo +"/"+ voiceInput;
 Serial.println(medInfo);
  
}
void doWork(char ch){
  switch(ch){
    case 'A':
              //digitalWrite(LED_1,HIGH);

              break;
    case 'a':

              break;
    case 'B':

              break;
    case 'b':

              break;
    case 'C':

              break;
    case 'c':

              break;
  }
}
