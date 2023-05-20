//#include <ServoTimer2.h>
//#include <Servo.h>

//https://youtu.be/O0mX_X5-pzw#include <RadioHead.h>

#include <RHCRC.h>
#include <RHGenericDriver.h>
#include <RH_ASK.h>
#include <AFMotor.h>

// Include dependant SPI Library 
#include <SPI.h>     
   


#define RX_REC_LED_PIN A0
#define TURN_LEFT_PIN A1
#define TURN_RIGHT_PIN A2
#define BUZZER_PIN 0
#define ONOFF_LED A2

// Create Amplitude Shift Keying Object
#define RADIOHEAD_BAUD 2000 // ATTINY85 - Transmission Speed
#define RADIOHEAD_TX_PIN -1 // UNO - Pin of the 433MHz transmitter (here not used)
#define RADIOHEAD_RX_PIN A5 // UNO - Pin of the 433MHz receiver 

RH_ASK rf_driver(RADIOHEAD_BAUD, RADIOHEAD_RX_PIN, RADIOHEAD_TX_PIN);

AF_DCMotor motor(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

#define ServoPin  10
//ServoTimer2 servo;

char buffer[100];

void setup()
{
    Serial.begin(9600);
    Serial.println("motor : start");
    pinMode(RX_REC_LED_PIN, OUTPUT); 
    pinMode(TURN_LEFT_PIN, OUTPUT); 
    pinMode(TURN_RIGHT_PIN, OUTPUT); 

    pinMode(ONOFF_LED, OUTPUT);
    digitalWrite (ONOFF_LED,HIGH);
    digitalWrite(TURN_LEFT_PIN, LOW); 
    digitalWrite(TURN_RIGHT_PIN, LOW); 

    rf_driver.init();     // UNO
 
    motor.setSpeed(200);
    motor.run(RELEASE);
    motor2.setSpeed(200);
    motor2.run(RELEASE);

    // attaches the servo on pin 10 to the servo object
    //myservo.attach(10);  
    //servo.attach(ServoPin);     // attach a pin to the servos and they will start pulsing
} 
int incPulse(int val, int inc){
   if( val + inc  > 2000 )
      return 1000 ;
   else
       return val + inc;  
 }  

int i = 0; 
int val;
char subtext[4];
void loop(){
  //i = i+1;
   //sprintf(buffer,  "i = %d", i);
   //Serial.println(buff);
   digitalWrite(RX_REC_LED_PIN, LOW); 

       
   // Set buffer to size of expected message
   uint8_t buf[7];
   uint8_t buflen = sizeof(buf);
  
  //val = incPulse( servo.read(), 1);
  //servo.write(val);

  // delay(10);   
   if (rf_driver.recv(buf, &buflen))
   {      
      // Message received with valid checksum
      digitalWrite(RX_REC_LED_PIN, HIGH);
     // Serial.print("Message Received: ");
     // Serial.println((char*)buf);
         
      if (strncmp((char*) buf, "FWD", 3) == 0)
      {        
         motor.run(BACKWARD);
         motor2.run(BACKWARD);
         strncpy(subtext, (char*) &buf[4], 3);
           
         // Serial.println ("Motor Forward");   
         if (strncmp(subtext, "RHT", 3) == 0) {
             Serial.println("Motor Forward - RHT");
             digitalWrite(TURN_LEFT_PIN, LOW); 
             digitalWrite(TURN_RIGHT_PIN, HIGH); 
         }      
         if (strncmp(subtext, "MID", 3) == 0) {
             Serial.println("Motor Forward - MID");
             digitalWrite(TURN_LEFT_PIN, LOW); 
             digitalWrite(TURN_RIGHT_PIN, LOW); 
         }
         if (strncmp(subtext, "LFT", 3) == 0) {
             Serial.println("Motor Forward - LFT");
             digitalWrite(TURN_LEFT_PIN, HIGH); 
             digitalWrite(TURN_RIGHT_PIN, LOW); 
         }      }
      if (strncmp ((char*) buf, "REL", 3) == 0)
      {
         digitalWrite(TURN_LEFT_PIN, LOW); 
         digitalWrite(TURN_RIGHT_PIN, LOW); 
         delay(100);
         Serial.println("Motor Release");
         motor.run(RELEASE);
         motor2.run(RELEASE);
      }
      if (strncmp ((char*) buf, "BWD", 7) == 0)
      {
         Serial.println("Motor Backward");
         motor.run(FORWARD);
         motor2.run(FORWARD);
         delay(700); 
         motor.run(RELEASE);
         motor2.run(RELEASE);
      }
      digitalWrite(RX_REC_LED_PIN, LOW);    

      if (strncmp ((char*) buf, "right__", 7) == 0)
      {
         Serial.println("Motor Right");
         motor.run(BACKWARD);
         motor2.run(RELEASE);
         delay(700); 
         motor.run(RELEASE);
         motor2.run(RELEASE);
        
      }


     if (strncmp ((char*) buf, "left___", 7) == 0)
     {
      Serial.println("Motor Right");
      motor.run(RELEASE);
      motor2.run(BACKWARD);
      delay(1000); 
      motor.run(RELEASE);
      motor2.run(RELEASE);
        
     }
   }
}
