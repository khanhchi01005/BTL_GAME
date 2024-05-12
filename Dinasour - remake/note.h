#ifndef NOTE_H
#define NOTE_H

#include "graphics.h"
#include "defs.h"

using namespace std;

void waitUntilKeyPressed(){
    SDL_Event e;
    while(true){
        if(SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
        return;
        SDL_Delay(100);
    }
}
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images/try.jpg"));

	graphics.presentScene();

     SDL_Texture* bird = graphics.loadTexture("images/bird.png");
    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }

        background.scroll(50);

        graphics.render(background);
        graphics.renderTexture(bird, 20, 520);

        graphics.presentScene();
        SDL_Delay(100);
    }

    //SDL_Texture* bird = graphics.loadTexture("images/bird(1).png");
   // graphics.renderTexture(bird, 200, 200);

	//graphics.presentScene();

	//waitUntilKeyPressed();

    SDL_DestroyTexture( background.texture );
    background.texture =NULL;
   SDL_DestroyTexture(bird);
    bird =NULL;
    graphics.quit();
    return 0;
}

#endif // NOTE_H
