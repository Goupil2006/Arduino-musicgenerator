int noten2[] = {
440, 
466,
494,
523,
554,
587,
622,
659,
698,
740,
784,
831,
880,
932,
988,
1047,
1109,
1175,
1245,
1319,
1397,
1480,
1568,
1661,
1760,
1865,
1976,
2093,
2217,
2349,
2489,
2637,
2794,
2960,
3136,
3322,
3520,
3729,
3951,
4186,
4435,
4699,
4978,
  };

String noten[] = {
"NOTE_A4",
"NOTE_AS4",
"NOTE_B4",
"NOTE_C5",
"NOTE_CS5",
"NOTE_D5",
"NOTE_DS5",
"NOTE_E5",
"NOTE_F5",
"NOTE_FS5",
"NOTE_G5",
"NOTE_GS5",
"NOTE_A5",
"NOTE_AS5",
"NOTE_B5",
"NOTE_C6",
"NOTE_CS6",
"NOTE_D6",
"NOTE_DS6",
"NOTE_E6",
"NOTE_F6",
"NOTE_FS6",
"NOTE_G6",
"NOTE_GS6",
"NOTE_A6",
"NOTE_AS6",
"NOTE_B6",
"NOTE_C7",
"NOTE_CS7",
"NOTE_D7",
"NOTE_DS7",
"NOTE_E7",
"NOTE_F7",
"NOTE_FS7",
"NOTE_G7",
"NOTE_GS7",
"NOTE_A7",
"NOTE_AS7",
"NOTE_B7",
"NOTE_C8",
"NOTE_CS8",
"NOTE_D8",
"NOTE_DS8",
  };


int melody[] = {
  noten2[1], noten2[1],noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1], noten2[1]
};
int Abstande[] = {
  100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};

const int sound = 4; // sound in 4
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int Temp = 0;
int TempAbstand = 0;
bool istwahr = true;
bool TempAuswahl = false;
int Tempnote = 0;
const int button1 = 2; // button in 2
const int button2 = 6; // button in 2
const int button3 = 8; // button in 2

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
  // put your setup code here, to run once:
  pinMode(sound,OUTPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);
  
  if(buttonState == HIGH){
    TempAuswahl = true;
    delay(1000);
    Serial.println("Start:");
    lcd.clear();
    lcd.print("Start: ");
    for(int x = 0; x < 1000; x++){
      buttonState = digitalRead(button1);
      if(buttonState == HIGH){
        Serial.println("Abstände");
        lcd.clear();
        lcd.print("Abstaende: ");
        for(int y = 0; y < 16; y++){
          delay(1000);
          istwahr = true;
          lcd.setCursor(0, 1);
          Serial.println(String(y + 1) + ":");
          lcd.print(String(y + 1) + ":");
          TempAbstand = 0;
          while(istwahr){
            Serial.println(String(TempAbstand));
            lcd.setCursor(3, 1);
            lcd.print(String(TempAbstand));
            buttonState2 = digitalRead(button2);
            if(buttonState2 == HIGH){
              istwahr = false;
              Abstande[y] = TempAbstand;
            }
            TempAbstand++;
          }
        }
        TempAuswahl = false;
      }
      delay(1);
    }
    if(TempAuswahl){
      Serial.println("Meldie");
      lcd.clear();
      lcd.print("Meldie: ");
      for(int i = 0; i < 16; i++){
            Serial.println(String(i + 1) + ":");
            lcd.setCursor(0, 1);
            lcd.print(String(i + 1) + ":");
            Tempnote = 0;
            Temp = 0;
            while(Temp == 0){
              Serial.println(noten[Tempnote]);
              lcd.setCursor(3, 1);
              lcd.print(noten[Tempnote]);
              int j = 0;
              while(j < 1000){
                buttonState2 = digitalRead(button2);
                if(buttonState2 == HIGH){
                  Temp++;
                  j = 1001;
                  melody[i] = noten2[Tempnote];
                  Serial.println(melody[i]);
                  lcd.setCursor(12, 1);
                  lcd.print(melody[i]);
                  delay(1000);
                }
                delay(1);
                j++;
              }
              Tempnote++;
            }
            
        }
    }
  }
  


  
  if(buttonState3 == HIGH){
   for(int x = 0; x < 16; x++){
     tone(sound, melody[x], 500);
     delay(500 + Abstande[x]);
   }
  }
}
