#include "bonus.h"
#include <cmath>
#include <iostream>

int Bonus::GetPower(){
    Bonus::Power power = Bonus::Power(rand() % 4 + 1);

    return power;
}

int Bonus::Duration(){
    duration = rand() % 10000 + 1000;
    return duration;
}