//
// Created by zyf on 2017/3/18.
//

#ifndef MACHINE_GAME_MYSERVO_H
#define MACHINE_GAME_MYSERVO_H

#include <Servo.h>
#include <math.h>

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

class MyServo
{
public:

    MyServo();

    void init(int pin);

    void change(int a);

    int step;

    Servo servo;
};


#endif //MACHINE_GAME_MYSERVO_H
