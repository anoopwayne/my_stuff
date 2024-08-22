uint16_t s;
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
uint8_t servonum = 0;

#include <Stepper.h>
#define STEPS 100
int prev=0;
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9, 10, 11);
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 
int angleToPulse(int ang);

void setup() {
  
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  stepper.setSpeed(40);
  pwm.begin();

  pwm.setPWMFreq(60);
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()){
    Serial.readBytes((char*)&s, 2);
    if (s <= 180) {
     
      pwm.setPWM(0, 0, angleToPulse(s) );
      Serial.println(s);
    }
    else if (s >= 181 && s <= 360) {
      
       pwm.setPWM(2, 0, angleToPulse(s-180) );
      Serial.println(s - 180);
    }
    else if (s >= 361 && s <=540) {
      
       pwm.setPWM(12, 0, angleToPulse(s-360) );
      Serial.println(s - 360);
    }
    else if (s >= 541 && s <= 720) {
      s4.write(s-540);
      pwm.setPWM(15, 0, angleToPulse(s-540) );
      Serial.println(s - 540);
    }
    if(s>=720 && s<=1080)
        {
          static int sum=0;
          
          s=s-720;

          sum=sum+s;
          Serial.println(sum);

          if(sum>=360)
          {
           sum=sum-360;
            int rotate=(prev-sum);
            stepper.step(-rotate/1.8);
            Serial.println(s);
            Serial.print("rotate:");
            Serial.println(rotate);


            }
          else{
          stepper.step(s/1.8);
          Serial.println(s);
          }
        prev=sum;
        }
      }
  }  // put your main code here, to run repeatedly:


int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   //Serial.print("Angle: ");Serial.print(ang);
   //Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}