#include "PS2X_lib.h"
#include "Adafruit_PWMServoDriver.h"
#include "MyServo.h"
#include "fix.h"

bool routine(const unsigned long int t, const unsigned int i);

void go_straight();

void go_back();

void turn_left();

void turn_right();

void fast_left();

void fast_right();

void stop();

PS2X ps2x;

Adafruit_PWMServoDriver pwmServoDriver;

int ps2_status = -1;

const int L1 = 4;
const int L2 = 3;
const int R1 = 6;
const int R2 = 5;
const int LEN = 7;
const int REN = 13;
const int SPEED = 255;
const int SPEED1 = 160;
const int delaytime = 30;
enum CAR_STATE
{
    CAR_STOP, CAR_FORWARD, CAR_BACKWARD, CAR_LEFT, CAR_RIGHT
};
int car_state = CAR_STOP;
enum SERVO_NAME
{
    SERVO_HAND, SERVO_2, SERVO_3, SERVO_4, SERVO_NET
};

MyServo servo[5] = {MyServo(6), MyServo(2), MyServo(3), MyServo(4), MyServo(5)};
int car_state_count = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(1000);
    // 舵机
    MyServo::setup();
    servo[SERVO_HAND].init(240, 428, 300);
    servo[SERVO_2].init(150, 550, 260);//530...150
    servo[SERVO_3].init(170, 566, 222);//226...182
    servo[SERVO_4].init(136, 600, 580);//550'''294
    servo[SERVO_NET].init(150, 260, 260);

    // 电机
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(LEN, OUTPUT);
    pinMode(REN, OUTPUT);

    while (ps2_status != 0)
    {
        Serial.println(ps2_status);
        ps2_status = ps2x.config_gamepad(12, 11, 10, 8, true, true);
        //the clock(7) pin, command(2) pin, attention(6) pin and the data(1) pin
        //pressure and rumble feature enabled
        delay(300);
    }
    if (ps2_status == 0)
    { //no error
        Serial.println("Controller found & successfully configured");
    }
    else
    {
        Serial.println("oooops, something went wrong");
    }

    yield();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (ps2_status != 0)
    {
        Serial.println("PS2 controller problem");
        return; //error occured, skip the loop
    }
    if (!routine(50, 0))
    { //returns true every 50 milliseconds
        return;
    }
    ps2x.read_gamepad(false, 0);

    if (ps2x.Analog(PSS_LX) < 10)
    {
        servo[SERVO_HAND].change(4);
        Serial.println("Left controller turned left");
    }
    else if (ps2x.Analog(PSS_LX) > 220)
    {
        servo[SERVO_HAND].change(-4);
        Serial.println("Right controller turned right");
    }
    else if (ps2x.Button(PSB_PAD_DOWN))
    {
        Serial.println("Down button held down");
        MyServo::clearTask();
        servo[SERVO_NET].addTaskPulse(150);
        servo[SERVO_2].addTaskPulse(534);
        servo[SERVO_3].addTaskPulse(338);
        servo[SERVO_4].addTaskPulse(132);
        servo[SERVO_HAND].addTaskPulse(240);
    }
    else if (ps2x.Button(PSB_PAD_UP))
    {
        //servo[SERVO_HAND].setPulse(400);
        Serial.println("UP button held down");
        
        MyServo::clearTask();
        servo[SERVO_4].addTaskPulse(366,4);
        servo[SERVO_2].addTaskPulse(342,4);
        servo[SERVO_3].addTaskPulse(558,4);
        servo[SERVO_2].addTaskPulse(158,4);
        servo[SERVO_NET].addTaskPulse(150,4);
    }
    else if (ps2x.Button(PSB_PAD_RIGHT))
    {
        //servo[SERVO_HAND].setPulse(uint16_t pulse);
        Serial.println("Right button held down");

        MyServo::clearTask();
        servo[SERVO_4].addTaskPulse(444,4);
        servo[SERVO_2].addTaskPulse(230,4);
        servo[SERVO_3].addTaskPulse(362,4);
        servo[SERVO_NET].addTaskPulse(260);
    }
    else if (ps2x.Button(PSB_PAD_LEFT))
    {
        //servo[SERVO_HAND].setPulse(uint16_t pulse);
        Serial.println("Left button held down");
        
        MyServo::clearTask();
        servo[SERVO_4].addTaskPulse(444,4);
        servo[SERVO_2].addTaskPulse(406,4);
        servo[SERVO_3].addTaskPulse(214,4);
        servo[SERVO_NET].addTaskPulse(260);
    }
    else if (ps2x.Button(PSB_L2) )
    {
        Serial.println("L2 button held down");
        turn_left();
        delay(delaytime);
        stop();

    }
    else if (ps2x.Button(PSB_R2) )
    {
        Serial.println("R2 button held down");
        turn_right();
        delay(delaytime);
        stop();
    }
    else if (ps2x.Analog(PSS_LY) < 10)
    {
        servo[SERVO_2].change(4);
        Serial.println("Left Controller turned down");
    }
    else if (ps2x.Analog(PSS_LY) > 220)
    {
        servo[SERVO_2].change(-4);
        Serial.println("Left controller turned up");
    }
    else if (ps2x.Analog(PSS_RX) < 10)
    {
        servo[SERVO_4].change(4);
        Serial.println("Right controller turned left");
    }
    else if (ps2x.Analog(PSS_RX) > 220)
    {
        servo[SERVO_4].change(-4);
        Serial.println("Right controller turned right");
    }
    else if (ps2x.Analog(PSS_RY) < 10)
    {
        servo[SERVO_3].change(4);
        Serial.println("Right controller turned down");
    }
    else if (ps2x.Analog(PSS_RY) > 220)
    {
        servo[SERVO_3].change(-4);
        Serial.println("Right controller turned up");
    }


    if (ps2x.Button(PSB_L1))
    {
        servo[SERVO_NET].change(8);
        Serial.println("L1 button held down");
    }

    else if (ps2x.Button(PSB_R1))
    {
        servo[SERVO_NET].change(-8);
        Serial.println("R1 button held down");
    }

    
    if (ps2x.Button(PSB_TRIANGLE))
    {
        Serial.println("Triangle button held down");
        car_state_count = 1;
        if (car_state != CAR_FORWARD) go_straight();
    }
    else if (ps2x.Button(PSB_CROSS))
    {
        Serial.println("Cross button held down");
        car_state_count = 1;
        if (car_state != CAR_BACKWARD) go_back();
    }
    else if (ps2x.Button(PSB_SQUARE))
    {
        Serial.println("Square button held down");
        car_state_count = 1;
        if (car_state != CAR_LEFT) fast_left();
    }
    else if (ps2x.Button(PSB_CIRCLE))
    {
        Serial.println("Circle button held down");
        car_state_count = 1;
        if (car_state != CAR_RIGHT) fast_right();
    }
    else if (car_state != CAR_STOP)
    {
        Serial.println("No button held down");
        if (car_state_count > 0) car_state_count--;
        else stop();
    }
    MyServo::loop();
}

bool routine(const unsigned long int t, const unsigned int i)
{
    static unsigned long int timeOfLast[16] = {0}; //this initializes an array to 0
    if (i >= 16)
    {
        return false;
    }
    unsigned long int timeNow = millis();
    if (timeNow - timeOfLast[i] >= t)
    {
        timeOfLast[i] = timeNow;
        //Serial.println(timeNow);
        return true;
    }
    return false;
}

void go_straight()
{
    car_state = CAR_FORWARD;
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    analogWrite(LEN, SPEED);
    analogWrite(REN, SPEED);
}



void go_back()
{
    car_state = CAR_BACKWARD;
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    analogWrite(LEN, SPEED);
    analogWrite(REN, SPEED);
}

void turn_left()
{
    car_state = CAR_LEFT;
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    analogWrite(LEN, SPEED1);
    analogWrite(REN, SPEED1);
}

void turn_right()
{
    car_state = CAR_RIGHT;
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    analogWrite(LEN, SPEED1);
    analogWrite(REN, SPEED1);
}

void fast_left()
{
    car_state = CAR_LEFT;
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    analogWrite(LEN, SPEED);
    analogWrite(REN, SPEED);
}

void fast_right()
{
    car_state = CAR_RIGHT;
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    analogWrite(LEN, SPEED);
    analogWrite(REN, SPEED);
}



void stop()
{
    car_state = CAR_STOP;
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    analogWrite(LEN, 0);
    analogWrite(REN, 0);
}

