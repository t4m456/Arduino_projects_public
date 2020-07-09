#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


//LCD display hints-------------
//    lcd.clear(); 
//    lcd.print("PM2.5/ugm3 : ");
//    lcd.setCursor(0,1);
//    lcd.print(ugm3, 3);
//------------------

int Button_UP = 2;
int Button_DOWN = 11;
int Button_FunctionSelect = 4;
int Relay_UP = 7; 
int Relay_DOWN = 8; 

int toggle_up = 0;
int toggle_down = 0;
int toggle_switch = 0;

int toggle_auto = 0;
//int toggle_auto_down = 0;

const unsigned long timeDuration_UP = 40000;
const unsigned long timeDuration_DOWN = 40000;
unsigned long previousTime = 0;

const unsigned long timeDurationBalcklight = 60000;

const unsigned long timeDurationAuto = 40000;


int LDR_value;

void setup() {
lcd.begin();
lcd.backlight();

//fun operation-------------

       lcd.clear();
       lcd.print("Rendszer");
       lcd.setCursor(0,1);
       lcd.print("kesz");

//fun operation

pinMode(Button_UP, INPUT);
pinMode(Button_DOWN, INPUT);
pinMode(Button_FunctionSelect, INPUT);

pinMode(Relay_UP, OUTPUT);
pinMode(Relay_DOWN, OUTPUT);

//Serial.begin(9600);
pinMode(A0, INPUT);

digitalWrite(Relay_UP, HIGH);
digitalWrite(Relay_DOWN, HIGH);
 

}

void loop() {
    int automaticOperation();
    int manualOperation();

unsigned long safetyTime = millis();
  
 int optionSwitch;
 

    if (digitalRead(Button_FunctionSelect) == HIGH && toggle_switch == 0){
        delay(250);
        toggle_switch = 1; 
        lcd.clear();
        lcd.print("Automata uzem");
        digitalWrite(Relay_UP, HIGH);
        digitalWrite(Relay_DOWN, HIGH);
        
   };
   if (digitalRead(Button_FunctionSelect) == HIGH && toggle_switch == 1){
       delay(250);
       toggle_switch = 0;
       lcd.clear();
       lcd.print("Manualis uzem");
       digitalWrite(Relay_UP, HIGH);
       digitalWrite(Relay_DOWN, HIGH);
      
    };

    if (toggle_switch == 1) {
      optionSwitch = automaticOperation();
      
      };
    if (toggle_switch == 0) {
      optionSwitch = manualOperation();
      
      };

      LDR_value = analogRead(A0);
      delay(150);
      //Serial.println(LDR_value);

      // Biztonsági leállítás

      if (safetyTime > 2147364800) { // Ez kb. 25 nap vagyis 2147364800
       digitalWrite(Relay_UP, HIGH);
       digitalWrite(Relay_DOWN, HIGH);
       lcd.backlight();
       lcd.clear();
       lcd.print("SERVICE");
   
    exit(0);
   }
      

};
 //--------------------------------------------AUTOMATA UZEM------------------------------// 
int automaticOperation(){
  unsigned long currentTime = millis();
  
  // ----- AUTO Redony mozgatas felfele
    
    if (LDR_value >= 550 && digitalRead(Relay_DOWN) == HIGH && toggle_auto == 0) {
      digitalWrite(Relay_UP, LOW);

       lcd.clear();
       lcd.print("Automata uzem");
       lcd.setCursor(0,1);
       lcd.print("Redony FEL");
       
     previousTime = currentTime;
     toggle_auto = 1;
     delay(250);
      
    };
    if (digitalRead(Relay_UP) == LOW && currentTime - previousTime >= timeDurationAuto && toggle_auto == 1){
     digitalWrite(Relay_UP, HIGH);
      
      lcd.clear();
      lcd.print("Automata uzem");
       
     delay(250);
      
    };
  // ----- AUTO Redony mozgatas lefele
     
    if (LDR_value <= 450 && digitalRead(Relay_UP) == HIGH && toggle_auto == 1) {
      digitalWrite(Relay_DOWN, LOW);
       lcd.clear();
       lcd.print("Automata uzem");
       lcd.setCursor(0,1);
       lcd.print("Redony LE");
       
     previousTime = currentTime;
     toggle_auto = 0;
     delay(250);
      
    };
   if (digitalRead(Relay_DOWN) == LOW && currentTime - previousTime >= timeDurationAuto && toggle_auto == 0 ){
     digitalWrite(Relay_DOWN, HIGH);
     
      lcd.clear();
      lcd.print("Automata uzem");
      delay(250);
      
    };

   if (digitalRead(Relay_UP) == LOW || digitalRead(Relay_DOWN) == LOW) {
      lcd.backlight();
      
  }
  else if (currentTime - previousTime >= timeDurationBalcklight){
      lcd.noBacklight();
  }; 

   
    };
 //--------------------------------------------AUTOMATA UZEM VEGE------------------------------//
 
 //--------------------------------------------MANUALIS UZEM------------------------------// 
  int manualOperation(){

  unsigned long currentTime = millis();
   
  //Redőny mozgatás felfele-----------------
    if ( digitalRead(Button_UP) == HIGH && toggle_up == 0 && digitalRead(Button_DOWN) == LOW && digitalRead(Relay_DOWN) == HIGH){
        digitalWrite(Relay_UP, LOW);
        
        toggle_up = 1;
    
       lcd.clear();
       lcd.print("Manualis uzem");
       lcd.setCursor(0,1);
       lcd.print("Redony FEL");
       
       previousTime = currentTime; //Nullázzuk a számlálót
       delay(250);
  };
  if(digitalRead(Button_UP) == HIGH || digitalRead(Button_DOWN) == HIGH || currentTime - previousTime >= timeDuration_UP && toggle_up == 1) {
        digitalWrite(Relay_UP, HIGH);
        digitalWrite(Relay_DOWN, HIGH);
        //delay(250);
        toggle_up = 0;
        toggle_down = 0;

       lcd.clear();
       lcd.print("Manualis uzem");
       delay(250);
  };
  //Redőny mozgatás lefele-----------------
  if (digitalRead(Button_DOWN) == HIGH && toggle_down == 0 && digitalRead(Button_UP) == LOW && digitalRead(Relay_UP) == HIGH){
        digitalWrite(Relay_DOWN, LOW);
       
        toggle_down = 1;
        
       lcd.clear();
       lcd.print("Manualis uzem");
       lcd.setCursor(0,1);
       lcd.print("Redony LE");

       previousTime = currentTime; //Nullázzuk a számlálót
        delay(250);
  };
  if(digitalRead(Button_DOWN) == HIGH || digitalRead(Button_UP) == HIGH || currentTime - previousTime >= timeDuration_DOWN && toggle_down == 1) {
       digitalWrite(Relay_DOWN, HIGH);
       digitalWrite(Relay_UP, HIGH);
       //delay(250);
       toggle_down = 0;
       toggle_up = 0;

       lcd.clear();
       lcd.print("Manualis uzem");
       delay(250);
  };

  if (digitalRead(Relay_UP) == LOW || digitalRead(Relay_DOWN) == LOW) {
      lcd.backlight();
      
  }
  else if (currentTime - previousTime >= timeDurationBalcklight){
      lcd.noBacklight();
  }; 
        
  
  
 
  };
 //--------------------------------------------MANUALIS UZEM VEGE------------------------------// 

 
