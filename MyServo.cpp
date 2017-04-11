//
// Created by zyf on 2017/3/18.
//

#include "MyServo.h"
#include "fix.h"

Adafruit_PWMServoDriver MyServo::pwmServoDriver = Adafruit_PWMServoDriver();

void MyServo::setup()
{
    pwmServoDriver.begin();
    pwmServoDriver.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

MyServo::MyServo(uint8_t num)
{
    m_num = num;
}

void MyServo::init(uint16_t minPulse, uint16_t maxPulse, uint16_t initialPulse)
{
    m_minPulse = minPulse;
    m_maxPulse = maxPulse;
    m_currentPulse = initialPulse;
    pwmServoDriver.setPWM(m_num, 0, m_currentPulse);
}

void MyServo::setPulse(uint16_t pulse, int delay_time=2)
{
    if (pulse > m_currentPulse)
    {
        for (; m_currentPulse < min(m_maxPulse, pulse); m_currentPulse++){
            pwmServoDriver.setPWM(m_num, 0, m_currentPulse);
            delay(delay_time);
        }
    }
    else
        for (; m_currentPulse > max(m_minPulse, pulse); m_currentPulse--){
            pwmServoDriver.setPWM(m_num, 0, m_currentPulse);
            delay(delay_time);
        }
    Serial.println(m_num);
    Serial.println(m_currentPulse);
}

void MyServo::change(int16_t a)
{
    setPulse(m_currentPulse + a);
}

