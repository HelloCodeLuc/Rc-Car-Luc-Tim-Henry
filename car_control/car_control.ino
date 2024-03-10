#include <Wire.h>
#include <AFMotor.h>

#define SOFTSERVO

#ifdef SOFTSERVO
#include <PWMServo.h>
#else
#include <Servo.h>
#endif 

#define RH
#ifdef RH
//  #define RH_ASK_ARDUINO_USE_TIMER2  // need to set this in RH_ASK.h in Radiohead library so no conflict with PWM Servo
#include <RHCRC.h>
#include <RHGenericDriver.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>     
#endif

#define RX_REC_LED_PIN A0
#define TURN_LEFT_PIN A1
#define TURN_RIGHT_PIN A2
#define ONOFF_LED A2

// Create Amplitude Shift Keying Object
#define RADIOHEAD_BAUD 2000 // ATTINY85 - Transmission Speed
#define RADIOHEAD_TX_PIN -1 // UNO - Pin of the 433MHz transmitter (here not used)
#define RADIOHEAD_RX_PIN A5 // UNO - Pin of the 433MHz receiver 

RH_ASK rf_driver(RADIOHEAD_BAUD, RADIOHEAD_RX_PIN, RADIOHEAD_TX_PIN);
#endif

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// Create a Servo object
#ifdef SOFTSERVO
// SoftwareServo myServo;
//Adafruit_SoftServo myServo;
PWMServo myServo;
#define SERVO_SIG 9
#else
Servo myServo;
#endif 

void setup()
{
  #ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
  #endif
  Serial.println("start");

  if (!rf_driver.init())
  #ifdef RH_HAVE_HARDWARE_SPI
    Serial.println("init failed");
  #else
    ;
  #endif

  myServo.attach(SERVO_SIG);
  // Control servo{
  Serial.println("Move to 0");
  myServo.write(0);   // Turn to 0 degrees
  // myServo.refresh();
  delay(1000);          // Wait for 1 second
  Serial.println("Move to 90");
  myServo.write(90);   // Rotate servo to 180 degrees
  // myServo.refresh();
  delay(1000);          // Wait for 1 second
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    //Serial.println("looping");
    if (rf_driver.recv(buf, &buflen)) // Non-blocking
    {     
      // Message with a good checksum received, dump it.
      rf_driver.printBuffer("Got:", buf, buflen);
    }
}

/*

// KENDALL #define BUZZER_PIN 0


char buffer[100];

void setup()
{
    Serial.begin(9600);
    Serial.println("motor : start");

    #ifdef RH
       pinMode(RX_REC_LED_PIN, OUTPUT); 
       pinMode(TURN_LEFT_PIN, OUTPUT); 
       pinMode(TURN_RIGHT_PIN, OUTPUT); 

       pinMode(ONOFF_LED, OUTPUT);
       digitalWrite (ONOFF_LED,HIGH);
       digitalWrite(TURN_LEFT_PIN, LOW); 
       digitalWrite(TURN_RIGHT_PIN, LOW); 

       if (!rf_driver.init())
        Serial.println("rf_driver init failed");
   #endif

 
   // KENDALL motor.setSpeed(200);
   // KENDALL  motor.run(RELEASE);
   // KENDALL  motor2.setSpeed(200);
   // KENDALL  motor2.run(RELEASE);

  //  myServo.attach(SERVO_SIG);

  //  // Control servo
  //  Serial.println("Move to 0");
  //  myServo.write(0);   // Turn to 0 degrees
  //  // myServo.refresh();
  //  delay(1000);          // Wait for 1 second
  //  Serial.println("Move to 90");
  //  myServo.write(90);   // Rotate servo to 180 degrees
  //  // myServo.refresh();
  //  delay(1000);          // Wait for 1 second
} 

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (rf_driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;

      // Message with a good checksum received, dump it.
      rf_driver.printBuffer("Got:", buf, buflen);
    }
}


*/

// // KENDALL int val;
// char subtext[4];

// void loop() {

//    // KENDALL #define NEW_CODE
//    #ifdef NEW_CODE
//       motor1.setSpeed(255); // Set motor speed (0-255)
//       motor1.run(FORWARD);  // Run motor 1 forward
//       delay(2000);          // Wait for 2 seconds

//       motor1.run(BACKWARD); // Run motor 1 backward
//       delay(2000);          // Wait for 2 seconds

//       motor1.run(RELEASE);  // Release motor 1
//       delay(1000);          // Wait for 1 second

//       myServo.write(180);   // Rotate servo to 180 degrees
//       delay(1000);          // Wait for 1 second

//       myServo.write(0);     // Rotate servo to 0 degrees
//       delay(1000);          // Wait for 1 second
//    #else
//       digitalWrite(RX_REC_LED_PIN, HIGH); 
//       // KENDALL digitalWrite(RX_REC_LED_PIN, LOW); 
         
//       // Set buffer to size of expected message
//       uint8_t buf[7];
//       uint8_t buflen = sizeof(buf);
   
//       if (rf_driver.recv(buf, &buflen))
//       {      
//          // Message received with valid checksum
//          digitalWrite(RX_REC_LED_PIN, LOW);
//          Serial.print("Message Received: ");
//          Serial.println((char*)buf);
            
//          if (strncmp((char*) buf, "FWD", 3) == 0)
//          {        
//             motor1.run(BACKWARD);
//             motor2.run(BACKWARD);
//             strncpy(subtext, (char*) &buf[4], 3);
            
//             // Serial.println ("Motor Forward");   
//             if (strncmp(subtext, "RHT", 3) == 0) {
//                Serial.println("Motor Forward - RHT");
//                digitalWrite(TURN_LEFT_PIN, LOW); 
//                digitalWrite(TURN_RIGHT_PIN, HIGH); 
//             }      
//             if (strncmp(subtext, "MID", 3) == 0) {
//                Serial.println("Motor Forward - MID");
//                digitalWrite(TURN_LEFT_PIN, LOW); 
//                digitalWrite(TURN_RIGHT_PIN, LOW); 
//             }
//             if (strncmp(subtext, "LFT", 3) == 0) {
//                Serial.println("Motor Forward - LFT");
//                digitalWrite(TURN_LEFT_PIN, HIGH); 
//                digitalWrite(TURN_RIGHT_PIN, LOW); 
//             }
//          }
//          if (strncmp ((char*) buf, "REL", 3) == 0)
//          {
//             digitalWrite(TURN_LEFT_PIN, LOW); 
//             digitalWrite(TURN_RIGHT_PIN, LOW); 
//             delay(100);
//             Serial.println("Motor Release");
//             motor1.run(RELEASE);
//             motor2.run(RELEASE);
//          }
//          if (strncmp ((char*) buf, "BWD", 7) == 0)
//          {
//             Serial.println("Motor Backward");
//             motor1.run(FORWARD);
//             motor2.run(FORWARD);
//             delay(700); 
//             motor1.run(RELEASE);
//             motor2.run(RELEASE);
//          }
//          digitalWrite(RX_REC_LED_PIN, LOW);    

//          if (strncmp ((char*) buf, "right__", 7) == 0)
//          {
//             Serial.println("Motor Right");
//             motor1.run(BACKWARD);
//             motor2.run(RELEASE);
//             delay(700); 
//             motor1.run(RELEASE);
//             motor2.run(RELEASE);         
//          }

//          if (strncmp ((char*) buf, "left___", 7) == 0)
//          {
//             Serial.println("Motor Right");
//             motor1.run(RELEASE);
//             motor2.run(BACKWARD);
//             delay(1000); 
//             motor1.run(RELEASE);
//             motor2.run(RELEASE);
//          }
//       }
//    #endif 
// }

