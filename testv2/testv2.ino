#include <Wire.h>
#include <hd44780.h> // main hd44780 header
#include <hd44780_I2Cexp.h> // i2c expander i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config exapander chip
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

int segmentA=A0;
int segmentB=A1;
int segmentC=12;
int segmentD=2;
int segmentE=4;
int segmentF=7;
int segmentG=8;
//int segmentDP=12;
int swith1=13;
int swith2=11;
int swith3=10;
int swith4=9;
void displaySegment(int);

int sec = 20; //traffic
int stage = 3;   //rgb
int red = 3;
int yellow =5;
int green = 6;//rgb

int money=0;
int car =0;
bool stay=false;

void setup() 
{
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status) // non zero status means it was unsuccesful
  {
  // begin() failed so blink error code using the onboard LED if possible
  hd44780::fatalError(status); // does not return
  }
  Serial.begin(9600);
   pinMode(segmentA, OUTPUT);
   pinMode(segmentB, OUTPUT);
   pinMode(segmentC, OUTPUT);
   pinMode(segmentD, OUTPUT);
   pinMode(segmentE, OUTPUT);
   pinMode(segmentF, OUTPUT);
   pinMode(segmentG, OUTPUT);
//   pinMode(segmentDP, OUTPUT);
   pinMode(swith1, OUTPUT);
   pinMode(swith2, OUTPUT);
   pinMode(swith3, OUTPUT);
   pinMode(swith4, OUTPUT);
  
   noInterrupts();
 TCCR1A = 0; 
 TCCR1B = 0;
 TCNT1 = 0; 
 OCR1A = 15624; 
 
TCCR1B |= (1 << WGM12); 
 TCCR1B |= (1 << CS12) | (1 << CS10); 
 TIMSK1 |= (1 << OCIE1A); 
 interrupts(); 
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}
ISR(TIMER1_COMPA_vect)
{
 sec--;
 if(sec == 0&&stage == 3){
  stage = 1;
  sec =10;
 }
 if(sec == 0&&stage == 1){
  stage = 2;
  sec =3;
 }
 if(sec == 0&&stage == 2){
  stage = 3;
  sec =20;
 }
}
unsigned long temp=0;
void loop() 
{
    if(!stay){
    lcd.clear();
    lcd.print("Money: ");
    lcd.print(money);
    lcd.setCursor(0, 1);
    lcd.print("Car: ");
    lcd.print(car);
    delay(20);
    }
    if(stay&&stage==1){
    lcd.clear();
    lcd.print("OK");
    lcd.setCursor(0, 1);
    lcd.print("Can pass");
    delay(20);
    }
    if(stay&&(stage==2||stage==3)){
    lcd.clear();
    lcd.print("Can't pass");
    lcd.setCursor(0, 1);
    lcd.print("You must wait");
    delay(20);
    }
    int readI=analogRead(A2);
     unsigned long times=millis();
     if(temp-times>5000){
        temp =times;
        if(!stay&&readI<970){
        stay =true;
        if(stage==1){
        money+=170;
        car++;
        }
      }
    }
    if(stay&&readI>990)stay=false;
    displayNumber(sec);
    if(stage==3){
      digitalWrite(red,HIGH);
      digitalWrite(yellow,LOW);
      digitalWrite(green,LOW);
    }
    if(stage==2){
      digitalWrite(red,LOW);
      digitalWrite(yellow,HIGH);
      digitalWrite(green,LOW);
    }
    if(stage==1){
      digitalWrite(red,LOW);
      digitalWrite(yellow,LOW);
      digitalWrite(green,HIGH);
    }
}

void displayNumber(int x)
{
          if(x>=1000){
          digitalWrite(swith1,HIGH);
          digitalWrite(swith2,LOW);
          digitalWrite(swith3,LOW);
          digitalWrite(swith4,LOW);
          displaySegment(x/1000);
          delay(5);
          //digitalWrite(swith1,LOW);
          }
          if(x>=100){
          digitalWrite(swith1,LOW);
          digitalWrite(swith2,HIGH);
          digitalWrite(swith3,LOW);
          digitalWrite(swith4,LOW);
          displaySegment((x/100)%10);
          //digitalWrite(swith2,LOW);
          delay(5);
          }
          if(x>=10){
          digitalWrite(swith1,LOW);
          digitalWrite(swith2,LOW);
          digitalWrite(swith3,HIGH);
          digitalWrite(swith4,LOW);
          displaySegment((x/10)%10);
          //digitalWrite(swith3,LOW);
          delay(5);
          }
          digitalWrite(swith1,LOW);
          digitalWrite(swith2,LOW);
          digitalWrite(swith3,LOW);
          digitalWrite(swith4,HIGH);
          displaySegment(x%10);
          //digitalWrite(swith4,LOW);
          delay(5);
          
}

void displaySegment(int numberToDisplay)
{
  switch(numberToDisplay)
  {
    //Number 0
    case 0:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

    //Number 1
    case 1:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

    //Number 2
    case 2:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,HIGH);
    break;

    //Number 3
    case 3:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,HIGH);
    break;

    //Number 4
    case 4:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

    //Number 5
    case 5:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

    //Number 6
    case 6:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

    //Number 7
    case 7:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

    //Number 8
    case 8:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

    //Number 9
    case 9:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;
  }
}
