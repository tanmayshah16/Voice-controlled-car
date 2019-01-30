
#define IO_USERNAME    "iotteam8"
#define IO_KEY         "7a6add3546b84796a62a63901ffbd781"


#define WIFI_SSID       "Redmi"
#define WIFI_PASS       "tan10000"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

// These are used to set the direction of the bridge driver.


#define obstaclePin_front  D0;
#define obstaclePin_back  D1;
//#define ENB D3      //ENB
#define MOTORB_1 D4 //IN3
#define MOTORB_2 D5 //IN4
#define MOTORA_1 D7 //IN1
#define MOTORA_2 D6 //IN2
//#define ENA D8      //ENA

#define redLED D2
#define greenLED D3


AdafruitIO_Feed *command = io.feed("voicecommand"); // Set up the 'command' feed

// SETUP
void setup()
{
  // Configure pins
  
  //pinMode(ENA, OUTPUT);
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  //pinMode(ENB, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(obstaclePin_front,INPUT);

  pinMode(obstaclePin_back,INPUT);
   
   
   
  // disable both motors
  //digitalWrite(ENA,LOW);
//  digitalWrite(ENB,LOW);
  digitalWrite(redLED,HIGH);
  digitalWrite(greenLED,LOW);
  
  // Start serial communication
  Serial.begin(9600);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);  

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

// MAIN CODE
void loop()
{
  io.run();
}

// this part of the code runs whenever there's a new message on Adafruit.io feed
void handleMessage(AdafruitIO_Data *data) {
  
  String commandStr = data->toString(); // store the incoming commands in a string
  
  // received message
  Serial.print("received <- ");
  Serial.println(commandStr);

  String cmd;
  int angle;

  // separate text and number ingredients
  for (int i = 0; i < commandStr.length(); i++) {
    if (commandStr.substring(i, i+1) == ":") {
      cmd = commandStr.substring(0, i);
      angle = commandStr.substring(i+1).toInt();
      break;
    }
  }

  // print command
  Serial.println(cmd);
  Serial.println(angle);
  
  // perform movements
  // LEFT
if (cmd.equalsIgnoreCase("Start")){
	Serial.println("Ignition on");
	digitalWrite(redLED,LOW);
	digitalWrite(greenLED,HIGH);
}
  
  if (cmd.equalsIgnoreCase("left")){    
    Serial.println("Turning left");
    //digitalWrite(ENA,HIGH);
    //digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,HIGH);
    digitalWrite(MOTORB_2,LOW);
    delay(angle*15);
    Serial.println("Stop");
    //digitalWrite(ENA,LOW);
    //digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  // RIGHT
  if (cmd.equalsIgnoreCase("right")){    
    Serial.println("Turning right");
    //digitalWrite(ENA,HIGH);
    //digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,HIGH);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,HIGH);
    delay(angle*15);
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  // FORWARD
  if (cmd.equalsIgnoreCase("forward")){    
    Serial.println("Moving forward");
    //digitalWrite(ENA,HIGH);
    //digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,HIGH);
    delay(angle*15);
    Serial.println("Stop");
    //digitalWrite(ENA,LOW);
    //digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  // BACK
  if (cmd.equalsIgnoreCase("reverse")){    
    Serial.println("Moving back");
    //digitalWrite(ENA,HIGH);
    //digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,HIGH);
    digitalWrite(MOTORB_1,HIGH);
    digitalWrite(MOTORB_2,LOW);
    delay(angle*15);
    Serial.println("Stop");
    //digitalWrite(ENA,LOW);
    //digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }  

int hasObstacle_front = digitalRead(obstaclePin_front);
  int hasObstacle_back = digitalRead(obstaclePin_back);
if (hasObstacle_front==0)
  {
    Serial.println("Stop something is ahead!!");
    //digitalWrite(ENA,LOW);
    //digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  if (hasObstacle_front==1)
  {
    //Serial.println("Front Path is clear");
    digitalWrite(LED_front,0);
  }
  if (hasObstacle_back==0)
  {
    Serial.println("Stop something is at back!!");
    //digitalWrite(ENA,LOW);
    //digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  if (hasObstacle_front==1)
  {
    //Serial.println("Back Path is clear");
    digitalWrite(LED_back,0);
  }
}
  
