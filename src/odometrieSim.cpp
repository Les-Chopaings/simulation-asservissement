#include "odometrieSim.h"
#include "hardware_interface.h"
#include "motor.h"

#define MAXSPEED    500
#define SEUIL       1*COEFMULT


odometrieSim::odometrieSim(/* args */){
    g_timeout_add(1, IntervalOdometrieLeft, this);
    g_timeout_add(1, IntervalOdometrieRight, this);
}

void odometrieSim::setLeftSpeed(int speed){
    valueLeft = speed;
}
void odometrieSim::setRightSpeed(int speed){
    valueRight = speed;
}
void odometrieSim::setLeftDirection(bool directionForward){
    moveForwardLeft = directionForward;
}
void odometrieSim::setRightDirection(bool directionForward){
    moveForwardRight = directionForward;
}

double odometrieSim::map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void odometrieSim::stopThread(void){
    stop_thread = true;
}

odometrieSim::~odometrieSim(){

}


gboolean odometrieSim::IntervalOdometrieLeft(gpointer data) {
    odometrieSim* odometrie = (odometrieSim*)data;
    odometrie->frequencyLeft += map(odometrie->valueLeft,0,100*COEFMULT,0,MAXSPEED)/1000;
    while (odometrie->frequencyLeft>1) {
        odometrie->frequencyLeft = odometrie->frequencyLeft - 0.5;                          //0.5 because the next line is a toggle
        set_gpio_get(port_odometrie2L,pin_odometrie2L,odometrie->moveForwardLeft);
        exti4_isr();
    }
    return true;
}

gboolean odometrieSim::IntervalOdometrieRight(gpointer data) {
    odometrieSim* odometrie = (odometrieSim*)data;
    odometrie->frequencyRight += map(odometrie->valueRight,0,100*COEFMULT,0,MAXSPEED)/1000;
    while (odometrie->frequencyRight>1) {
        odometrie->frequencyRight = odometrie->frequencyRight - 0.5;                        //0.5 because the next line is a toggle
        set_gpio_get(port_odometrie2R,pin_odometrie2R,!odometrie->moveForwardRight);
        exti2_isr();
    }
    return true;
}


        