//
// Created by zyf on 2017/3/18.
//

#include "MyServo.h"

void MyServo::setup()
{
    pwmServoDriver = new Adafruit_PWMServoDriver();
    pwmServoDriver->begin();
    pwmServoDriver->setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

MyServo::MyServo(uint8_t num)
{
    m_num = num;
}

void MyServo::init(uint16_t minPulse, uint16_t maxPulse, uint16_t initialPulse)
{
    m_minPulse = minPulse;
    m_maxPulse = maxPulse;
    m_currentPulse = minPulse;
    setPulse(initialPulse);
}

void MyServo::setPulse(uint16_t pulse)
{
    if (pulse > m_currentPulse)
    {
        for (; m_currentPulse < min(m_maxPulse, pulse); m_currentPulse++)
            pwmServoDriver->setPWM(m_num, 0, m_currentPulse);
    }
    else
        for (; m_currentPulse > max(m_minPulse, pulse); m_currentPulse--)
            pwmServoDriver->setPWM(m_num, 0, m_currentPulse);
}

void MyServo::change(int16_t a)
{
    setPulse(m_currentPulse + a);
}

