//
// Created by zyf on 2017/3/18.
//

#include "HandleController.h"

HandleController::HandleController(LobotServoController &lobotServoController) {
    m_lobotServoController = &lobotServoController;
    m_lastSignal = 255;
    m_signalChangedFlag = true;
}

void HandleController::initSignal() {
    m_lobotServoController->receiveHandle();
    auto newSignal = m_lobotServoController->numOfActinGroupRunning;
    Serial.println(newSignal);
    if (newSignal == m_lastSignal)m_signalChangedFlag = false;
    else {
        m_signalChangedFlag = true;
        m_lastSignal = newSignal;
    }
}

bool HandleController::isSignalChanged() {
    return m_signalChangedFlag;
}

uint8_t HandleController::signal() {
    return m_lastSignal;
}
