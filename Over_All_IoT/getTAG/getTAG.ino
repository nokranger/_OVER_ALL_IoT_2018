/* getTAG.ino
 *
 * Created by Danilo Queiroz Barbosa, August 26, 2016.
 * Member of electronicdrops.com
 *
 * This example shows how to use the RFIDRdm630 library.
 * When a card is read, an ASCII TAG and a Card Number
 * will be show in the Serial.*
 *
 *
 *   This example code is in the public domain.

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 */

#include "RFIDRdm630mod.h"
//char * tag;

RFIDtag  in_tag;  // RFIDtag object
RFIDtag  out_tag;  // RFIDtag object

RFIDRdm630 in_reader = RFIDRdm630(&Serial1);    // the reader object.
RFIDRdm630 out_reader = RFIDRdm630(&Serial2);    // the reader object.

int updates;
int failedUpdates;
int pos;
int stringplace = 0;

String latitude = "";
String longitude = "";

String timeUp;
String nmea[15];

int count;
const int MAX = 4;
String tags[4] ;
int memberTag ;

const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
void setup() {
  memberTag=0;
  count=0;
  Serial.begin(9600);   // open the Serial for show data
  gps_setup();
    pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

}

void countLED(){
  if(count==0){
    
  }else if(count==1){
    
  }else if(count==2){
    
  }else if(count==3){
    
  }else if(count==4){
    
  }
}

bool isSame(String cardIn){
  for(int i=0;i<memberTag;i++){
    if (cardIn.equals(tags[i])) {
      return true;    
    }
  }
  return false;
}

void movePosAndDel(String cardIn){
  for(int i=0;i<memberTag;i++){
    if(cardIn.equals(tags[i])){
      tags[i] = String("");
      for(int j=i+1;j<=memberTag-1;j++){
        tags[i] = String(tags[j]);
      }    
    }
  }
  tags[memberTag-1] = String("");
  memberTag--;
}

void loop() {
  digitalWrite(ledPin, state);
  if(state==RISING){
    //Serial.println("r");
    }else{
      if(state==FALLING){
              //Serial.prinln("s");
        }
      }
  if (in_reader.isAvailable()){  // tests if a card was read by the module
    
    in_tag = in_reader.getTag();  // if true, then receives a tag object
    Serial.print("IN Card Number: ");
    Serial.println(in_tag.getCardNumber());  // get cardNumber in long format

    gps_loop();
    
    Serial.print(" GPS Latitude: ");
    Serial.print(latitude);  // get cardNumber in long format
    Serial.print(" GPS Longitude: ");
    Serial.print(longitude);  // get cardNumber in long format
    Serial.print("\r\n");

    if(count<MAX){
      if(!(isSame(String(in_tag.getCardNumber())))){   
        tags[memberTag] = String(in_tag.getCardNumber());
        memberTag++;
        count++;
        countLED();
      }
    }
    //Serial.print("In tag is ");
    //Serial.println(tags[memberTag-1]);
    //Serial.print("member tag is ");
    //Serial.println(memberTag);
    Serial.print("count is ");
    Serial.println(count);
  }

  if (out_reader.isAvailable()){  // tests if a card was read by the module

    out_tag = out_reader.getTag();  // if true, then receives a tag object
    Serial.print("OUT Card Number: ");
    Serial.println(out_tag.getCardNumber());  // get cardNumber in long format
    
    gps_loop();
    
    Serial.print(" GPS Latitude: ");
    Serial.print(latitude);  // get cardNumber in long format
    Serial.print(" GPS Longitude: ");
    Serial.print(longitude);  // get cardNumber in long format
    Serial.print("\r\n");
    
    if(count>0){
      if(isSame(String(out_tag.getCardNumber()))){
        movePosAndDel(String(out_tag.getCardNumber()));
        count--;
        countLED();
      }
    }
    //Serial.print("Out member tag is ");
    //Serial.println(memberTag);
    Serial.print("count is ");
    Serial.println(count);
  }

}
  void blink() {
  state = !state;
}
