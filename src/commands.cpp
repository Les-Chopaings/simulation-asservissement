#include "commands.h"


commands commandsAsserv;


commands::commands(/* args */)
{
}

commands::~commands()
{
}

void commands::I2cSendData (uint8_t command, uint8_t* data, int length){
    SimI2cSendData(command,data,length);
}


void commands::I2cReceiveData (uint8_t command, uint8_t* data, int length){
    SimI2cReceiveData(command,data,length);
}