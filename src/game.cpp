#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include <thread>
#include "timer.cpp"
typedef std::chrono::high_resolution_clock Clock;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      enemy(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)-1),
      random_h(0, static_cast<int>(grid_height)-1) {
  PlaceFood();
  PlaceBonus();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    controller.HandleInput(running, enemy);
    Update();
    renderer.Render(snake, enemy, food, power);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;

      MoveEnemy();
    }
    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    if(HasBonus){
      power.x = 1000000;
      power.y = 1000000;
      // std::cout << "HasBonus " << HasBonus << std::endl;
      // std::cout << timer.elapsedSeconds() << std::endl;
      // std::cout << "active bonus: " << ActiveBonus << std::endl;
      if(timer.elapsedSeconds() >= 5.000){
        HasBonus = false;
        // std::cout << "HasBonus " << HasBonus << std::endl;
        timer.stop();
        if(ActiveBonus == 0){
          snake.speed -= 0.5;
          //std::cout << "now speed is " << snake.speed << std::endl;
          PlaceBonus();
          //std::cout << "powe {" << power.x << ", " << power.y << "}" << std::endl; 
        }
        else if(ActiveBonus == 1){
          std::cout << "IMMORTAL" << std::endl;
        }
      }
    }
      
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceBonus() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      power.x = x;
      power.y = y;
      return;
    }
  }
}

void Game::Update() {  //auto add_bonus_time;
  if (!snake.alive) return;

  snake.Update();
  enemy.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  int e_new_x = static_cast<int>(enemy.head_x);
  int e_new_y = static_cast<int>(enemy.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    enemy.GrowBody();
    snake.speed += 0.02;
    enemy.speed += 0.01;
  }
  
  if(snake.SnakeCell(power.x, power.y)){
    std::cout << "fji" << std::endl;
    SaveSpeed = snake.speed;
    //ActiveBonus = bonus.GetPower();
    // switch(ActiveBonus){
    //   case 0: 
    //     // snake.speed += 0.5;
    //     // HasBonus = true;
    //     // timer.start();
    //     std::cout << "Bonus activated: speed " << ActiveBonus << std::endl;
    //     break;
    //   case 1:
    //     std::cout << "Bonus activated: immortal " << ActiveBonus << std::endl;
    //     break;
    //   case 2: 
    //     std::cout << "Bonus activated: 2points " << ActiveBonus << std::endl;
    //     break;
    //   case 3:
    //     std::cout << "Bonus activated: 2points " << ActiveBonus << std::endl;
    //     break;
    // }
  }

  // for(const auto item: enemy.BodyPosition()){
  //   if(new_x == item.x && new_y == item.y){
  //     snake.alive = false;
  //     std::cout << "=====================" << std::endl;
  //     std::cout <<  "     GAME  OVER    "  << std::endl;
  //     std::cout << "=====================" << std::endl;
  //   }
  // }

  // if((new_x == e_new_x && new_y == e_new_y && snake.size > 1)){
  //   snake.alive = false;
  //   std::cout << "=====================" << std::endl;
  //   std::cout <<  "     GAME  OVER    "  << std::endl;
  //   std::cout << "=====================" << std::endl;
  // }
  
}

void Game::ActivatePower(){
  
}

void Game::MoveEnemy(){
  Snake::Direction direction = Snake::Direction(rand()%4);
  enemy.direction = direction;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }