#include<Servo.h> // including the servo library

Servo servoleft;
Servo servoright;
Servo gripper;   // declaration for the gripper.
int MAXLEFT_SEN = 2;  // pins for the infra-red package of sensors
int LEFT_SEN = 3;
int MIDDLE_SEN = 4;
int RIGHT_SEN = 5;
int MAXRIGHT_SEN = 6;

const int trigPin=7;
const int echoPin=8;
const int trigPin2=9;
const int echoPin2=10;
long duration,duration2;     // diclaring a variable called duration and duration two
int distance,distance2;      // initializing a variable called ditance and the second distance 
void setup() {
 servoleft.attach(13);              
 servoright.attach(12);             
 gripper.attach(11);   // attaching the gripper to the servo pin 11.
 pinMode(trigPin,OUTPUT);  // this is to tell your bot that the 7 pin or the trig pin is the output sound pulse by your sensor
 pinMode(echoPin,INPUT);  // this is to tell your bot that the 8 pin is going to give it the feedback signal
 pinMode(trigPin2,OUTPUT);
 pinMode(echoPin2,INPUT);
 Serial.begin (9600);
 pinMode(MAXLEFT_SEN, INPUT);  // setting the infra-red sensors.
 pinMode(LEFT_SEN, INPUT);
 pinMode(MIDDLE_SEN, INPUT);
 pinMode(RIGHT_SEN, INPUT);
 pinMode(MAXRIGHT_SEN, INPUT);
}

void loop() 
{
  int maxleft = digitalRead(MAXLEFT_SEN);  // recieving the readings of the infra-reds into an integer for comparison.
  int left = digitalRead(LEFT_SEN);
  int middle = digitalRead(MIDDLE_SEN);
  int right = digitalRead(RIGHT_SEN);
  int maxright = digitalRead(MAXRIGHT_SEN);
  digitalWrite(trigPin,LOW);  // just to restart the ultra-sonic
  delayMicroseconds(2);      // aslo to restart
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  Serial.print(" the first distance distance:");   // this is for the program to print to the user the word distance:
  Serial.println(distance);   // this is to tell the prorgam what to print after the distance
  digitalWrite(trigPin2,LOW);  // same thing to the first ultra-sonic just that this time this ultra is attached to differnt pins and also to the right of the bot
  delayMicroseconds(2);
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(10);
  duration2=pulseIn(echoPin2,HIGH);
  distance2=duration2*0.034/2;
  Serial.print("the second distance:");   // there was a simple mistake to be fixed that is the bot is always turning left never to the right at the same time it cant use the second ultra sonic to detect a wall to the left there for might cause a wrong turn
  Serial.println(distance2);
  //black line is 1 , white line is 0.

  servoleft.writeMicroseconds(1700);
  servoright.writeMicroseconds(1300);
  if(maxleft== 0 && left== 0 && middle== 1 && right== 1 && maxright== 0) //straight
  {
  servoleft.writeMicroseconds(1700);
  servoright.writeMicroseconds(1300);
  gripper.write(0);
  }
  else if(maxleft== 0 && left== 1 && middle== 1 && right== 0 && maxright== 0)  //straight
  {
  servoleft.writeMicroseconds(1700);
  servoright.writeMicroseconds(1300);
  gripper.write(0);
  }
    else if(maxleft== 0 && left== 0 && middle== 0 && right== 0 && maxright== 0)  // making a u-turn
  {
    make_u();
  }
      else if(maxleft== 1 && left== 1 && middle== 1 && right== 1 && maxright== 1 && distance<4) // T-junction where a left hand rule is applied.
  {
   servoleft.writeMicroseconds(1500);
   servoright.writeMicroseconds(1500);
   delay(250);
   servoleft.writeMicroseconds(1700);
   servoright.writeMicroseconds(1300);
   delay(100);
   gripper.write(90);
   delay(100);
   maxleft_F();
  }
  else if(maxleft== 1 && left== 1 && middle== 1 && right== 1 && maxright== 1)
  {
   servoleft.writeMicroseconds(1500);
   servoright.writeMicroseconds(1500);
   delay(250);
   maxleft_F();
  }
  else if(maxleft== 0 && left== 0 && middle== 0 && right== 0 && maxright== 1) /* when the robot is tilted to the left. it tilts back to the right*/
  {
    tiltright();
  }
  else if(maxleft== 1 && left== 0 && middle== 0 && right== 0 && maxright== 0)// when the robot is tilted to the right. it tilts back to the left.
  {
   tiltleft();
  }
  else if(maxleft== 1 && left== 1 && middle== 1 && right== 1 && maxright== 0)
  {
    maxright_F();
  }
}



   void maxleft_F()
  {
  servoleft.writeMicroseconds(1300);          
  servoright.writeMicroseconds(1300);
  delay(450);
  }
  void maxright_F()
  {
  servoright.writeMicroseconds(1700);
  servoleft.writeMicroseconds(1700);
  delay(450);
  }
   void tiltright()
  {
  servoright.writeMicroseconds(1500);
  servoleft.writeMicroseconds(1700);
  delay(150);  
  }
  void tiltleft()
  {
  servoleft.writeMicroseconds(1500);
  servoright.writeMicroseconds(1300);
  delay(150);  
  }
  void make_u()
{
  servoleft.write(180);
  servoright.write(180);
}
