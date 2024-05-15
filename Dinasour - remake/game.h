#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include "graphics1.h"
#define INITIAL_SPEED 30

int speed =INITIAL_SPEED;



void moveUp() {
    int now = SDL_GetTicks();
    if (isJumping) {
        trexY += dy;
        if (trexY+   T_REX_HEIGHT >= SCREEN_HEIGHT - GROUND_HEIGHT) {
            trexY = SCREEN_HEIGHT - GROUND_HEIGHT - T_REX_HEIGHT;
            isJumping = false;
            dy = 0;
        } else {
            if(now-t_rex_tick >2){
            dy+=2;
            t_rex_tick = now;
            }
        }
        }
}

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
   if(rect1.x/3 < rect2.x/3){
        score++;
   }
   return (rect1.x + rect1.w) >= rect2.x  && (rect2.x + rect2.w) >= rect1.x &&
           (rect1.y + rect1.h) >= rect2.y && (rect2.y + rect2.h) >= (rect1.y);
}

bool MouseOverButton(const SDL_Rect& button, int mouseX, int mouseY) {
    return (mouseX >= button.x && mouseX <= button.x + button.w &&
            mouseY >= button.y && mouseY <= button.y + button.h);
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}


#endif
