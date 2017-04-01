#include "PS2X_lib.h"
#include "Adafruit_PWMServoDriver.h"
#include "MyServo.h"
#include "fix.h"

bool routine(const unsigned long int t, const unsigned int i);

void go_straight();

void go_back();

void turn_left();

void turn_right();

void stop();

PS2X ps2x;

Adafruit_PWMServoDriver pwmServoDriver;

int ps2_status = -1;

const int L1 = 4;
const int L2 = 3;
const int R1 = 6;
const int R2 = 5;
const int LEN = A8;
const int REN = A9;
const int SPEED = 0xFF;

enum CAR_STATE
{
    CAR_STOP, CAR_FORWARD, CAR_BACKWARD, CAR_LEFT, CAR_RIGHT
};
int car_state = CAR_STOP;
enum SERVO_NAME
{
    SERVO_HAND, SERVO_2, SERVO_3, SERVO_4, SERVO_NET
};

MyServo servo[5] = {MyServo(0), MyServo(2), MyServo(3), MyServo(4), MyServo(5)};

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(1000);
    // 舵机
    MyServo::setup();
    servo[SERVO_HAND].init(200, 400, 250);
    servo[SERVO_2].init(150, 550, 150);
    servo[SERVO_3].init(170, 618, 182);
    servo[SERVO_4].init(150, 570, 550);
    servo[SERVO_NET].init(150, 260, 150);

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
        Serial.println("Left button held down");
    }
    else if (ps2x.Analog(PSS_LX) > 220)
    {
        servo[SERVO_HAND].change(-4);
        Serial.println("Right button held down");
    }
/*    else if (ps2x.Button(PSB_PAD_UP))
    {
        //servo[4].change(2);
        Serial.println("Up button held down");
    }
    else if (ps2x.Button(PSB_PAD_DOWN))
    {
        //servo[4].change(-2);
        Serial.println("Down button held down");
    }*/
    else if (ps2x.Analog(PSS_LY) < 10)
    {
        servo[SERVO_2].change(4);
        Serial.println("Up button held down");
    }
    else if (ps2x.Analog(PSS_LY) > 220)
    {
        servo[SERVO_2].change(-4);
        Serial.println("Down button held down");
    }
    else if (ps2x.Analog(PSS_RX) < 10)
    {
        servo[SERVO_4].change(4);
        Serial.println("Up button held down");
    }
    else if (ps2x.Analog(PSS_RX) > 220)
    {
        servo[SERVO_4].change(-4);
        Serial.println("Down button held down");
    }
    else if (ps2x.Analog(PSS_RY) < 10)
    {
        servo[SERVO_3].change(4);
        Serial.println("Up button held down");
    }
    else if (ps2x.Analog(PSS_RY) > 220)
    {
        servo[SERVO_3].change(-4);
        Serial.println("Down button held down");
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


    if (ps2x.Button(PSB_TRIANGLE) && car_state != CAR_FORWARD)
    {
        go_straight();
    }
    else if (ps2x.Button(PSB_CROSS) && car_state != CAR_BACKWARD)
    {
        go_back();
    }
    else if (ps2x.Button(PSB_SQUARE) && car_state != CAR_LEFT)
    {
        turn_left();
    }
    else if (ps2x.Button(PSB_CIRCLE) && car_state != CAR_RIGHT)
    {
        turn_right();
    }
    else if (car_state != CAR_STOP)
    {
        stop();
    }
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
    analogWrite(LEN, SPEED);
    analogWrite(REN, SPEED);
}

void turn_right()
{
    car_state = CAR_RIGHT;
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    digitalWrite(LEN, SPEED);
    digitalWrite(REN, SPEED);
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

