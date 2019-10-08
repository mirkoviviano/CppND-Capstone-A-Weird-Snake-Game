#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "bonus.h"
#include "timer.h"

class Game {
  public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const &controller, Renderer &renderer,
            std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;

  private:
    Snake snake;
    Snake enemy;
    Bonus bonus;
    SDL_Point food;
    SDL_Point power;
    Timer timer;
    int ActiveBonus;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
  

    int score{0};
    bool HasBonus = false;
    float SaveSpeed;

    void PlaceFood();
    void PlaceBonus();
    void ActivatePower();
    void Update();
    void MoveEnemy();
};

#endif