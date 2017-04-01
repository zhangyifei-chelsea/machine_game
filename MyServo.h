//
// Created by zyf on 2017/3/18.
//

#ifndef MACHINE_GAME_MYSERVO_H
#define MACHINE_GAME_MYSERVO_H

#include <Servo.h>
#include "Adafruit_PWMServoDriver.h"
#include <math.h>

#define max(a, b) (((a)>(b))?(a):(b))
#define min(a, b) (((a)<(b))?(a):(b))

class MyServo
{
public:

    static Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver();;

    static void setup();

    MyServo(uint8_t num);

    /**
     *
     * @param minPulse
     * @param maxPulse
     * @param initialPulse
     */
    void init(uint16_t minPulse, uint16_t maxPulse, uint16_t initialPulse);

    void setPulse(uint16_t pulse);

    void change(int16_t a);

private:

    // 舵机驱动板上的编号
    uint8_t m_num;
    // 最小/最大范围
    uint16_t m_minPulse, m_maxPulse;
    // 当前值
    uint16_t m_currentPulse;
};


#endif //MACHINE_GAME_MYSERVO_H
