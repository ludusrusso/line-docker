/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
#define USE_USBCON
#include <ros.h>
#include <std_msgs/Int8.h>


int PINS[] = {8,9,10,11,12};
int READ = 7;
bool data[5] = {false};

ros::NodeHandle nh;

std_msgs::Int8 data_msg;
ros::Publisher chatter("chatter", &data_msg);
const int del = 10;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(READ, INPUT);
  for (int i = 0; i < 5; i++) pinMode(PINS[i], OUTPUT);
  for (int i = 0; i < 5; i++) digitalWrite(PINS[i], HIGH);
  nh.initNode();
  nh.advertise(chatter);
}

// the loop routine runs over and over again forever:
void loop() {
  int d = 0;
  for (int i = 0; i < 5; i++) {
      
      digitalWrite(PINS[i], LOW);
      delay(del);
      data[i] = digitalRead(READ);
      d = (d<<1) + data[i];
      delay(del);
      digitalWrite(PINS[i], HIGH);
     
    }
     data_msg.data = d;
     chatter.publish( &data_msg );
     nh.spinOnce();
 }
