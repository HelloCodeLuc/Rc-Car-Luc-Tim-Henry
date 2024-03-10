
#include <RadioHead.h>
#include <RHCRC.h>
#include <RHGenericDriver.h>
#include <RH_ASK.h>

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h>   

#define DEBUG_PIN 3
#define SWITCH_PIN 4
// Create Amplitude Shift Keying Object
#define RADIOHEAD_BAUD 2000 
#define RADIOHEAD_TX_PIN 12 // UNO - Pin of the 433MHz transmitter
#define RADIOHEAD_RX_PIN -1 // UNO - Pin of the 433MHz receiver (here not used)

RH_ASK rf_driver(RADIOHEAD_BAUD, RADIOHEAD_RX_PIN, RADIOHEAD_TX_PIN);

int buttonState = 0;
int sensorPin = A0;
int sensorValue = 0;

// JOYSTICK 
int analogPinX = A0; // potentiometer wiper (middle terminal) connected to analog pin 0
int analogPinY = A1; // potentiometer wiper (middle terminal) connected to analog pin 1
int valY = 0;  // variable to store the value read
int valX = 0;  // variable to store the value read

void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
    while (!Serial);
    Serial.println("start");
#endif
    
    pinMode(DEBUG_PIN, OUTPUT); // DEBUG
    pinMode(SWITCH_PIN, INPUT); // SWITCH

    if (!rf_driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
	;
#endif
}

void loop()
{
    const char *msg = "hello";

    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(200);
}

/*
char *xmsg, *ymsg;
void loop()
{    
   valX = analogRead(analogPinX);  // read the input pin
   Serial.print("valX = ");
   Serial.println(valX);
   valY = analogRead(analogPinY);  // read the input pin
   Serial.print("valY = ");
   Serial.println(valY);

   digitalWrite(DEBUG_PIN, LOW);

   // buttonState = digitalRead(SWITCH_PIN);
   //if (buttonState == HIGH) {
   //if (valX

   xmsg = (char*) "notset";
   if (valX > 600)
   {
      // forward 
      xmsg = (char*) "Forward";
   } 
   if (valX < 400)
   {
      // backward 
      xmsg = (char*) "backward";
   } 
   if (valX >= 400 && valX <= 600)
   {
      // do nothing 
      xmsg = (char*) "release";
   }

// buttonState = digitalRead(SWITCH_PIN);
   //if (buttonState == HIGH) {
   //if (valY

   if  (valY > 600)
   {
      // right
      ymsg = (char*) "right__";
   }
   
   if (valY < 400)
   {
      // left
      ymsg = (char*) "left___";
   }

   if (valY >= 400 && valY <= 600)
   {
      // left
      ymsg = (char*) "release";
   }
   Serial.print(": xmsg = ");
   Serial.println(xmsg);
   Serial.print(": ymsg = ");
   Serial.println(ymsg);
   rf_driver.send((uint8_t *)xmsg, strlen(xmsg));
    rf_driver.send((uint8_t *)ymsg, strlen(ymsg));
   //digitalWrite(DEBUG_PIN, HIGH);
   rf_driver.waitPacketSent(); 

   delay(1);
} 
*/