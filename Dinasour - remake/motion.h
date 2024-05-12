#ifndef MOTION_H
#define MOTION_H

#include "graphics.h"
#define INITIAL_SPEED 3;

Graphics graphics;
    graphics.init();

struct Mouse{
    int x,y;
    int dx=0 ,dy=0;
    int speed = INITIAL_SPEED;
    void move(){
    x +=dx;
    y +=dy;
    }

    void turnNorth(){
        dy = -speed;
        dx =0;
    }

    void turnSouth(){
        dy= speed;
        dx=0;
    }

    void turnWest(){
        dy =0;
        dx =-speed;
    }

    void turnEast(){
        dy =0;
        dx = speed;
    }
};

void render (const Mouse &mouse, const Graphics& graphics, SDL_Texture* bird){
    graphics.renderTexture(bird, mouse.x, mouse.y);
}

#endif