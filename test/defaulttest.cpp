#include "simulation.h"


void printPos (void){
    int16_t x;
    int16_t y;
    int16_t theta;
    commandsAsserv.get_coordinates(x,y,theta);
    printf("%d %d %d\n",x,y,theta);
}

FUNCTIONSIM(defaultTest){
    printPos();
    // commandsAsserv.set_consigne_lineaire(-500,0);
    // sleep(5);
    commandsAsserv.consigne_angulaire(90);
    sleep(1);
    printPos();
}
