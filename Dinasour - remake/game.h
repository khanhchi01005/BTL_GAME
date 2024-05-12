#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include "graphics1.h"
#define INITIAL_SPEED 30

int trexX=SCREEN_WIDTH/6;
int trexY = SCREEN_HEIGHT-GROUND_HEIGHT-T_REX_HEIGHT;
int dx=0,dy=0;
int speed =INITIAL_SPEED;
bool isJumping = false;


void move() {
    if (isJumping) {
        trexY += dy;
        if (trexY+   T_REX_HEIGHT >= SCREEN_HEIGHT - GROUND_HEIGHT) { // Check if T-Rex reached the ground
            trexY = SCREEN_HEIGHT - GROUND_HEIGHT - T_REX_HEIGHT;
            isJumping = false; // T-Rex finishes jumping
            dy = 0; // Reset vertical velocity
        } else {
            dy+=2; // Apply gravity
            // if i apply dy+=4 , i falls faster
        }
    }
}

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
   if(rect1.x < rect2.x){
        score++;
   }

   return rect1.x + rect1.w >= rect2.x && rect2.x + rect2.w >= rect1.x &&
           rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y;
}


bool gameOver(int trexX,int trexY){
    return trexX <=0 || trexX >= SCREEN_WIDTH;
           trexY <=0 || trexY >= SCREEN_HEIGHT;
}
#endif
