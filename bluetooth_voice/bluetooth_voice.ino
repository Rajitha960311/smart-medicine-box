#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

int pushButton = 7;   // input pin (for a pushbutton)
int pushBtnStatus = 0;     // variable for reading the pin status

SoftwareSerial espSerial(5, 6); //TX,RX

void setup() {
  
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(pushButton, INPUT);    // declare pushbutton as input

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {

  String tagID = "";
  String voiceInput = "";
  //String medInfo = "/893C0E21/Vitamin B/Capsule/Before food/40/No/7:30 a.m./1/1:30 p.m./1/7:30 p.m/1";
  //String medInfo = "/679E6DB4/Vitamin E/Capsule/After food/50/No/8:30 a.m./1/2:30 p.m./1/8:30 p.m/2";
  String medInfo = "";
  String payload = "{}";

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
  
  Serial.println("Your pill bottle is now being scanned. Please wait !");
  
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
  tagID = content.substring(1);
  tagID.replace(" ","");
  //Serial.println(tagID);
  espSerial.println(tagID); 
  delay(8000);
  
  payload = espSerial.readStringUntil('\n');
  payload.trim();
  //Serial.println("payload :"+payload);
  
  if(payload=="a"){
    
    medInfo = medInfo +"/"+ tagID;
    
    for (int i = 0; i < 11; i++){
      
      newPillBottleGuide(i);     
      voiceInput = Serial.readStringUntil('\n');
      //Serial.println(voiceInput);
        
      if(voiceInput==""){
        i--;
      }else{
        medInfo = medInfo +"/"+ voiceInput;
        //Serial.println(medInfo);
      }
      
    }

    espSerial.println(medInfo);
    delay(8000);
    payload = espSerial.readStringUntil('\n');
    payload.trim();
    if(payload=="success"){
      Serial.println("Good job. Your medication information has been successfully saved.");      
    }
    else{
      Serial.println("Please try again later");
      }
    
  }else{   
      Serial.println(payload);
      delay(8000);
      //Serial.println("Do you want to replay the instructions?");
  }


}

void newPillBottleGuide(int ch){
  
  switch(ch){
    case 0:
            Serial.println("This is a new pill bottle.");
            delay(5000);
            Serial.println("Please tell me the name of the medicine first");
            delay(11000);
              break;
    case 1:
            Serial.println("What is its unit?");
            delay(11000);  
            break;
    case 2:
            Serial.println("Please tell me the inatake advice");
            delay(11000);
              break;
    case 3:
            Serial.println("How many did you put in the pill bottle?");       
            delay(11000);
             break;
    case 4:
            Serial.println("Is this a medicine you only take when you need it?");
            delay(11000);
            break;

    case 5:
              Serial.println("What is the first time you need to be reminded?");
              delay(11000);        
              break;
    case 6:
              Serial.println("What dose should you take at this time?");
              delay(11000);        
              break;
    case 7:
              Serial.println("What is the second time you need to be reminded?");
              delay(11000);        
              break;
    case 8:
              Serial.println("What dose should you take at this time?");
              delay(11000);        
              break;
    case 9:
              Serial.println("What is the third time you need to be reminded?");
              delay(11000);        
              break;
    case 10:
              Serial.println("What dose should you take at this time?");
              delay(11000);        
              break;
  }  
  
}
