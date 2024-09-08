#pragma once

#include "asservissement_interface.h"
#include "i2cSim.h"

class commands : public asservissement_interface
{
private:
    /* data */
public:
    commands(/* args */);

    void I2cSendData (uint8_t command, uint8_t* data, int length) override;
    void I2cReceiveData (uint8_t command, uint8_t* data, int length) override;

    ~commands();
};

extern commands commandsAsserv;

