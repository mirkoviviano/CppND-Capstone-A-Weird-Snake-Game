#ifndef BONUS_H
#define BONUS_H

#include <vector>
#include "SDL.h"
#include <random>
#include "snake.h"

class Bonus {
    public:
        enum Power { Speed, Immortality, DoublePoints, DoubleGrowth};

        SDL_Point position;
        
        int GetPower();
        int Duration();
    private: 
        int duration;
};

#endif
