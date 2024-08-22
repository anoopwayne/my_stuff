int sum;
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define CH2 12
#define CH4 11
#define CH10 13
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t servonum = 0;

#include <Stepper.h>
#define STEPS 100
int prev=0;
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 6, 7, 8, 9);
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 
int angleToPulse(int ang);

void setup() {
  
  Serial.begin(9600);
  pinMode(CH10,INPUT);
 pinMode(CH2,INPUT);
 pinMode(CH4,INPUT);
 pinMode(10,INPUT);

  Serial.println("16 channel Servo test!");
  stepper.setSpeed(60);
  pwm.begin();

  pwm.setPWMFreq(60);
  // put your setup code here, to run once:

}

void loop() {
  int pwm1=pulseIn(CH10,HIGH);
  int pwm2=pulseIn(CH2,HIGH);
  int pwm3=pulseIn(CH4,HIGH);
  int pwm4=pulseIn(10, HIGH);
  int cw=map(pwm4,988,1975,0,4);
  int val1=map(pwm1,988,1975,200,575);
  int val2=map(pwm2,988,1975,125,400);
int val3=map(pwm3,988,1975,125,575);
  pwm.setPWM(4,0,val1);
 // Serial.println(val3);
  //delay(100);
  pwm.setPWM(1,0,val2);
  //delay(100);
  pwm.setPWM(5,0,val3);
//delay(100);
sum=sum+val3;
//Serial.println(sum);
Serial.println("no");
while(cw==4){
   int pwm4=pulseIn(10, HIGH);
  int cw=map(pwm4,988,1975,0,4);
  if(cw!=4){
    break;
  }
Serial.println("cw");
  stepper.step(5);
}
while(cw==0)
{
   int pwm4=pulseIn(10, HIGH);
  int cw=map(pwm4,988,1975,0,4);
  if(cw!=0)
  {
    break;
  }
  Serial.println("Ncw");
  stepper.step(-5);
}

}

