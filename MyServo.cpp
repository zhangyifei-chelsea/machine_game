//
// Created by zyf on 2017/3/18.
//

#include "MyServo.h"

MyServo::MyServo()
{
    step = 100;
}

void MyServo::init(int pin)
{
    servo.attach(pin);
    servo.write(step);
}

void MyServo::change(int a)
{
    step += a;
    step = max(0, min(200, step));
    servo.write(step);
}

