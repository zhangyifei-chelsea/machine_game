//
// Created by zyf on 2017/3/18.
//

#ifndef MACHINE_GAME_HANDLECONTROLLER_H
#define MACHINE_GAME_HANDLECONTROLLER_H

#include <stdint.h>
#include "LobotServoController.h"

class HandleController {

public:

    HandleController(LobotServoController &lobotServoController);

    void initSignal();

    bool isSignalChanged();

    uint8_t signal();

private:

    LobotServoController *m_lobotServoController;
    uint8_t m_lastSignal;
    bool m_signalChangedFlag;
};


#endif //MACHINE_GAME_HANDLECONTROLLER_H
