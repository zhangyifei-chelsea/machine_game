//
// Created by zyf on 2017/3/18.
//

#ifdef CLION_FIX

class _Serial
{
public:
    void begin(double);
    void println(const char*);
    void println(double);
};

_Serial Serial;

void delay(double);

unsigned long millis();

void pinMode(int,int);
void digitalWrite(int,int);
void analogWrite(int,int);
void yield();

typedef unsigned char byte;
typedef bool boolean;

#define A0 0
#define A1 0
#define A2 0
#define A3 0
#define A4 0
#define A5 0
#define A6 0
#define A7 0
#define A8 0
#define A9 0
#define OUTPUT 0
#define INPUT 0
#define LOW 0
#define HIGH 1


#endif //MACHINE_GAME_FIX_H
