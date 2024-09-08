#pragma once

#include <atomic>
#include <chrono>
#include <thread>
#include "hardware_interface.h"


void SimI2cSendData (uint8_t command, uint8_t* data, int length);
void SimI2cReceiveData (uint8_t command, uint8_t* data, int length);