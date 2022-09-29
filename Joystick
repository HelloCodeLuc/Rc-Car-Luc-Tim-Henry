# include <Servo.h>

Servo myservo;  // create servo object to control a servo


const int LeftInput = 2;
const int RightInput = 4;
const int LeftBulb = 6;
const int RightBulb = 8;



void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  myservo.attach(10);
  pinMode(LeftInput, INPUT);
  pinMode(RightInput, INPUT);
  pinMode(LeftBulb, OUTPUT);
  pinMode(RightBulb, OUTPUT);
}
int incPulse(int val, int inc){
   if( val + inc  > 150 )
      return 0 ;
   else
       return val + inc;  
 } 
 int i;
 char buffer[100];
 int LeftInput_state = 0;
 int RightInput_state = 0;
 int val = 0;
 
void loop() {
  LeftInput_state = digitalRead(LeftInput);
  RightInput_state = digitalRead(RightInput);
  
  sprintf(buffer, "i = %d,%5d val = %d,%5d Left input = %d\n", i, val, LeftInput_state );
  Serial.println(buffer);
  i = i +1;
  // put your main code here, to run repeatedly:

 /*   if (RightButton = HIGH)(;
       (Steervar = Steervar + 10);
    else if (RightButton = LOW);
       (Steervar = Steervar = 10);
       )
    if (LeftButton = HIGH) (;
       (Steervar = Steervar - 10);
    else if (LeftButton = LOW);
       (Steervar = Steervar = 10);
       )*/
  /*8

   delay(10);
    sprintf (buff, "Steervar = %5d, \n",  Steervar);
    Serial.print(buff);
*/


  // val = incPulse( myservo.read(), 1);

   

   if (LeftInput_state == HIGH) {
     digitalWrite (LeftBulb, HIGH);
     digitalWrite (RightBulb, LOW);
     Serial.println ("Left");
     //val = 0
      myservo.write(150);
   }
   else if (RightInput_state == HIGH) {
      digitalWrite (LeftBulb, LOW);
      digitalWrite (RightBulb, HIGH);
      Serial.println ("Right");
      myservo.write(0);
   }
   else {
      digitalWrite (LeftBulb, LOW);
      digitalWrite (RightBulb, LOW);
      Serial.println ("Middle");
      myservo.write(75);
   }
}
