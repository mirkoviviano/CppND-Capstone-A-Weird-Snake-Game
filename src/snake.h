#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody(bool doubleGrowth);
  bool SnakeCell(int x, int y);

  Direction direction = Direction(rand()%4);

  float speed{0.1f};
  int size{1};
  bool alive{true};
  bool immortal{false};
  bool doublePoints{false};
  bool doubleGrowth{false};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

  std::vector<SDL_Point> BodyPosition();
 
 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif