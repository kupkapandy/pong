#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"


SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

bool init(){
  bool success = true;
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("couldn't initalize - SDL Error: %s", SDL_GetError());
  }else{
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
      printf("couldn't create window! - SDL Error: %s", SDL_GetError());
    }
  }

  return success;
}

void movePlayer(SDL_Surface* surface, SDL_Rect* rect, int value){
  SDL_FillRect(surface, rect, 0x00000000);
  rect->y += value * -1;
  if(rect->y < 0) rect->y = 0;
  else if(rect->y > SCREEN_HEIGHT - rect->h) rect->y = SCREEN_HEIGHT - rect->h;
  SDL_FillRect(surface, rect, 0xffffffff);
}

void moveBall(SDL_Surface* surface, SDL_Rect* ball, SDL_Rect* player, int *xValue, int *yValue){
  SDL_FillRect(surface, ball, 0x00000000);
  ball->x += *xValue;
  ball->y += *yValue;
  if(ball->x > SCREEN_WIDTH - ball->w) *xValue *= -1;
  if(ball->x == player->x + player->w
      && ball->y >= player->y && ball->y <= player->y + player->h) *xValue *= -1;
  if((ball->x >= player->x && ball->x <= player->x + player->w) && (ball->y == player->y + player->h || ball->y + ball->h == player->y)){
    *yValue *= -1;
    *xValue *= -1;
  }
  if(ball->y < 0) *yValue *= -1;
  if(ball->y > SCREEN_HEIGHT - ball->h) *yValue *= -1;

  SDL_FillRect(surface, ball, 0xffffffff);
}

void moveEnemy(SDL_Surface* surface, SDL_Rect* rect, int value){

}


int main(){
  if(!init()){
    printf("init failed!\n");
    return -1;
  }else{
    SDL_Rect player = (SDL_Rect){
      (float)SCREEN_WIDTH / 24 * 1.5,
      (float)SCREEN_HEIGHT / 2 - (float)SCREEN_WIDTH / 24,
      SCREEN_WIDTH / 24,
      SCREEN_HEIGHT / 3,
    };
    SDL_Rect ball = (SDL_Rect){
      (float)SCREEN_WIDTH / 2 - (float)min(SCREEN_WIDTH, SCREEN_HEIGHT) / 20,
      (float)SCREEN_HEIGHT / 2 - (float)min(SCREEN_WIDTH, SCREEN_HEIGHT) / 20,
      min(SCREEN_WIDTH, SCREEN_HEIGHT) / 20,
      min(SCREEN_WIDTH, SCREEN_HEIGHT) / 20,
    };
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, &player, 0xffffffff);
    SDL_FillRect(surface, &ball, 0xffffffff);
    SDL_UpdateWindowSurface(window);
    int xValue = -2;
    int yValue = 2;
    bool quit = false;
    SDL_Event event;
    float a, b, delta;
    while(!quit){
      int a = SDL_GetTicks();
      delta = a - b;
      if(delta > 1000/240.0){
        printf("fps: %f\n", 1000 / delta);
        b = a;
        while(SDL_PollEvent(&event) != 0){
          if(event.type == SDL_QUIT){
            quit = true;
          }
          if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN){
            movePlayer(surface, &player, -1 * playerSpeed);
          }
          if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP){
            movePlayer(surface, &player, playerSpeed);
          }
        }
        moveBall(surface, &ball, &player, &xValue, &yValue);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(1);
      }
    }
  }
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
