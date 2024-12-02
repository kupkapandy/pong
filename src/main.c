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

void move(SDL_Surface* surface, SDL_Rect* rect, int value){
  SDL_FillRect(surface, rect, 0x00000000);
  rect->y += value * -10;
  if(rect->y < 0) rect->y = 0;
  else if(rect->y > SCREEN_HEIGHT - rect->h) rect->y = SCREEN_HEIGHT - rect->h;
  SDL_FillRect(surface, rect, 0x00ff0000);
}


int main(){
  if(!init()){
    printf("init failed!\n");
    return -1;
  }else{
    SDL_Rect rect;
    rect.w = SCREEN_HEIGHT / 24;
    rect.h = SCREEN_HEIGHT / 4;
    rect.x = rect.w * 1.5;
    rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, &rect, 0x00ff0000);
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
    while(!quit){
      while(SDL_PollEvent(&event) != 0){
        if(event.type == SDL_QUIT){
          quit = true;
        }
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN){
          move(surface, &rect, -1);
          SDL_UpdateWindowSurface(window);
        }
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP){
          move(surface, &rect, 1);
          SDL_UpdateWindowSurface(window);
        }
      }
    }
  }
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
