/*
 Created by Tamás Szabó
  13.04.2020

  E-mail: szabotamas6@gmail.com
  
  -IR Transmitter for Samsung TV remote controller
  -Main buttons like: Power, Source, Volume UP, Volume DOWN, Control arrows, OK (middle) button, Return
  
  Tested on SAMSUNG LE40B530p7 
            SAMSUNG UE43NV7122
*/
 
// Include IR Remote Library

/* PIN 3 is occupied for IR LED according to IR remote library
   Dedicated PIN for sending IR signals
   Tested on Arduino UNO and NANO
*/
#include <IRremote.h>
 
// Define remote buttons
const int Power_b = 2; // Power ON/OFF
const int SRC_b = 4; // Source button
const int V_UP_b = 5; // Volume UP button
const int V_DOWN_b = 6; // Volume DOWN button
const int UP_b = 7; // UP button (control)
const int DOWN_b = 8; // DOWN button (control)
const int LEFT_b = 9; // LEFT button (control)
const int RIGHT_b = 10; // RIGHT button (control)
const int OK_b = 11; // OK button (control)
const int Return_b = 12; //Return button (control)
 
// Define a variable for the button state
int Power_b_State = 0; // Power button state
int SRC_b_State = 0; // Source button state
int V_UP_b_State = 0; // Volume UP button state
int V_DOWN_b_State = 0; // Volume DOWN button state
int UP_b_State = 0; // UP button (control) state
int DOWN_b_State = 0; // DOWN button (control) state
int LEFT_b_State = 0; // LEFT button (control) state
int RIGHT_b_State = 0; // RIGHT button (control) state
int OK_b_State = 0; // OK button (control) state
int Return_b_State = 0; //Return button (control) state


// Create IR Send Object
IRsend irsend;
 
void setup()
{
  // Set Switch pin as Input
  // 10 pcs push-button all set INPUT
  
  pinMode(Power_b, INPUT);
  pinMode(SRC_b, INPUT);
  pinMode(V_UP_b, INPUT);
  pinMode(V_DOWN_b, INPUT);
  pinMode(UP_b, INPUT);
  pinMode(DOWN_b, INPUT);
  pinMode(LEFT_b, INPUT);
  pinMode(RIGHT_b, INPUT);
  pinMode(OK_b, INPUT);
  pinMode(Return_b, INPUT);

}
 
void loop() {
  
  // Set button state 
  Power_b_State = digitalRead(Power_b);
  SRC_b_State = digitalRead(SRC_b);
  V_UP_b_State = digitalRead(V_UP_b);
  V_DOWN_b_State = digitalRead(V_DOWN_b);
  UP_b_State = digitalRead(UP_b);
  DOWN_b_State = digitalRead(DOWN_b);
  LEFT_b_State = digitalRead(LEFT_b);
  RIGHT_b_State = digitalRead(RIGHT_b);
  OK_b_State = digitalRead(OK_b);
  Return_b_State = digitalRead(Return_b);


 
  // If button is pressed send the given code command
  
  if (Power_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E040BF, 32); // TV power ON/OFF
  };
  if (SRC_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E0807F, 32); // TV Source 
  };
  if (V_UP_b_State == HIGH ) {
      irsend.sendSAMSUNG(0xE0E0E01F, 32); // TV Volume UP
  };    
  if (V_DOWN_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E0D02F, 32); // TV Volume DOWN
  };
  if (UP_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E006F9, 32); // TV UP (control button)
  };
  if (DOWN_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E08679, 32); // TV DOWN (control button)
  };
  if (LEFT_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E0A659, 32); // TV LEFT (control button)
  };
  if (RIGHT_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E046B9, 32); // TV RIGHT (control button)
  };
  if (OK_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E016E9, 32); // TV OK (control button)
  };
  if (Return_b_State == HIGH) {
      irsend.sendSAMSUNG(0xE0E01AE5, 32); // TV Return (control button)
  };
     
    // Add a small delay before repeating
    delay(200);
 
};
