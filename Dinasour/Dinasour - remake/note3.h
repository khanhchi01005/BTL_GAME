
#include "graphics.h"
#include "defs.h"
#include "sprite.h"

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

    Trex trex;
    Cactus cactus;

     // Set initial positions
    trex.position.x = SCREEN_WIDTH / 4;
    trex.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - TREX_HEIGHT;
    cactus.position.x = SCREEN_WIDTH;
    cactus.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - CACTUS_HEIGHT;


     // Game variables
     bool quit = false;
     bool isGameOver = false;
     int score =0;
     int gameSpeed = INITIAL_SPEED;
     SDL_Event e;

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images/try.jpg"));

	graphics.presentScene();

     SDL_Texture* bird = graphics.loadTexture("images/bird.png");
     //SDL_Texture *cactus = graphics.loadTexture("images/cactus1.png");

    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE && !trex.isJumping) {
                    trex.isJumping = true;
                    trex.jumpHeight = 100;
                    trex.jumpSpeed = 10;
                }
            }
        }
    if (!isGameOver) {
            if (!isGameOver) {
                // Update trex
                if (trex.isJumping) {
                    trex.position.y -= trex.jumpSpeed;
                    trex.jumpSpeed -= 1;
                    if (trex.position.y >= SCREEN_HEIGHT - GROUND_HEIGHT - TREX_HEIGHT) {
                        trex.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - TREX_HEIGHT;
                        trex.isJumping = false;
                    }
                }

                // Update cactus
                cactus.position.x -= gameSpeed;

                // Check for collision
                if (CheckCollision(trex.position, cactus.position)) {
                    isGameOver = true;
                }

                // Check if cactus passed the trex
                if (cactus.position.x + CACTUS_WIDTH < trex.position.x) {
                    score++;
                    if (score % 10 == 0) {
                        gameSpeed++;
                    }
                    cactus.position.x = SCREEN_WIDTH;
                    cactus.position.y = SCREEN_HEIGHT - GROUND_HEIGHT - CACTUS_HEIGHT;
                }
            }



    }



    SDL_DestroyTexture( background.texture );
    background.texture =NULL;
   SDL_DestroyTexture(bird);
    bird =NULL;
    graphics.quit();
    return 0;
}
