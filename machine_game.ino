#include "PS2X_lib.h"
#include "MyServo.h"
#include "fix.h"

bool routine(const unsigned long int t, const unsigned int i);

PS2X ps2x;
int ps2_status = -1;

MyServo servo[5];

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    delay(1000);
    servo[0].init(A0);
    servo[4].init(A4);
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
    } else
    {
        Serial.println("oooops, something went wrong");
    }
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

    if (ps2x.Button(PSB_PAD_LEFT))
    {
        servo[0].change(2);
        Serial.println("Left button held down");
    } else if (ps2x.Button(PSB_PAD_RIGHT))
    {
        servo[0].change(-2);
        Serial.println("Right button held down");
    }
    if (ps2x.Button(PSB_PAD_UP))
    {
        servo[4].change(2);
        Serial.println("Up button held down");
    } else if (ps2x.Button(PSB_PAD_DOWN))
    {
        servo[4].change(-2);
        Serial.println("Down button held down");
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


