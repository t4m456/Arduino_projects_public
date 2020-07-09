int LED_2_PIROS = 2;
int LED_3_ZOLD = 3;
int LED_5_NARANCS = 5;

int RELAY_6 = 6;
int RELAY_4 = 4;

int BUTTON_BAL_8 = 8;
int BUTTON_JOBB_9 = 9;

const unsigned long timeDurationOn = 5400000; // 5.400.000 azaz 90 perc
const unsigned long timeDurationOff = 10800000; //10.800.000 azaz 3 óra

unsigned long previousTime = 0;

void setup() {
 

pinMode(LED_2_PIROS, OUTPUT);
pinMode(LED_3_ZOLD, OUTPUT);
pinMode(LED_5_NARANCS, OUTPUT);

pinMode(RELAY_6, OUTPUT);
pinMode(RELAY_4, OUTPUT);

pinMode(BUTTON_BAL_8, INPUT);
pinMode(BUTTON_JOBB_9, INPUT);


}

void loop() {
  unsigned long currentTime = millis();
  
  digitalWrite(RELAY_4, HIGH);
  
  // Áram alá helyezés után bekapcsol a relay és addig marad bekepcsolt állapotban amig -timeDurationOn- vagy a jobb gombot be nem nyomod.
  if (digitalRead(LED_2_PIROS) == LOW && currentTime - previousTime >= timeDurationOn || digitalRead(BUTTON_JOBB_9) == HIGH){
    digitalWrite(LED_2_PIROS, HIGH);
    digitalWrite(LED_3_ZOLD, LOW);
    digitalWrite(RELAY_6, HIGH);
    
    //digitalWrite(LED_5_NARANCS,HIGH);
     previousTime = currentTime;
  }
 
    
  // A készülék jelenleg kikapcsolt állapotban van
  //Addig marad kikapcsolt állapotban amig a timerDurationOff be van állítva vagy ha benyomom a bal gombot akkor bekapcsol.
   if (digitalRead(LED_2_PIROS) == HIGH && currentTime - previousTime >= timeDurationOff || digitalRead(BUTTON_BAL_8) == HIGH){
    digitalWrite(LED_2_PIROS, LOW);
    digitalWrite(LED_3_ZOLD, HIGH);
    digitalWrite(RELAY_6, LOW);
    delay(5000);
    digitalWrite(RELAY_4, LOW);
    delay(250);
    digitalWrite(RELAY_4, HIGH);
     previousTime = currentTime;
     
   }

   if (currentTime > 2147364800 ) { // Ez kb. 25 nap azaz 2147364800
    digitalWrite(LED_5_NARANCS,HIGH);
    digitalWrite(RELAY_6, HIGH);
    digitalWrite(LED_2_PIROS, HIGH);
    digitalWrite(LED_3_ZOLD, LOW);
    exit(0);
   }
    
   }
   
  
  
    
   // digitalWrite(LED_5_NARANCS,HIGH);
   
   
   
