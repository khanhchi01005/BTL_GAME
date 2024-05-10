#include "graphics1.h"
#include "defs.h"
#include "game.h"


using namespace std;

void drawBoundingBox(SDL_Renderer* renderer, const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the color to red
    SDL_RenderDrawRect(renderer, &rect); // Draw the rectangle
}

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();


    Mix_Music *gMusic = graphics.loadMusic("music/subway.ogg");
    graphics.play(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("music/jump.wav");
    Mix_Chunk *gCrash = graphics. loadSound("music/crash.mp3");

   /* TTF_Font* font = graphics.loadFont("fonts/purisa.ttf", 100);
    if (TTF_Init() == -1) {
            graphics.logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
        }

    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* helloText = graphics.renderText("Hello", font, color);

    graphics.renderTexture(helloText, 200, 200);
    */

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images/try.jpg"));

    Sprite t_rex;
    SDL_Texture* t_rexTexture = graphics.loadTexture("images/char.png");
    t_rex.init(t_rexTexture, T_REX_FRAMES, T_REX_CLIPS);

    Sprite cactus;
    SDL_Texture* cactusTexture = graphics.loadTexture("images/xuong.png");
    cactus.init(cactusTexture,CACTUS_FRAMES,CACTUS_CLIPS);

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture("images/bird.png");
    bird.init(birdTexture,BIRD_FRAMES,BIRD_CLIPS);


    bool quit = false;
    SDL_Event e;
    int score =0;
    int threshold =2000;
    int increase=1;
    int cactusSpeed = 15;
    int birdSpeed = 15;
    int X1_axis,X2_axis=0;

    // Store the positions of cacti and their collision rectangles
    vector<int> cactusX;
    vector<SDL_Rect> cactusRects;

    vector<int> birdX;
    vector<SDL_Rect> birdRects;

    while (!quit && !gameOver(trexX, trexY)) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_SPACE && !isJumping) {
                    isJumping = true;
                    dy = -JUMP_FORCE;
                }
            }
        }

        if (isJumping) {
            move();
            graphics.play(gJump);
        }



        if (!gameOver(trexX, trexY)) {
          move();
          score++;
           srand(time(0));

           int cactusGap = 500;

if (cactusX.empty() || cactusX.back() <= SCREEN_WIDTH - cactusGap) {
    int randomX = rand() % (SCREEN_WIDTH - cactusGap) + SCREEN_WIDTH;
    cactusX.push_back(randomX); // Add a new cactus at the right edge of the screen
    SDL_Rect cactusRect = { cactusX.back(), 440, CACTUS_WIDTH, CACTUS_HEIGHT };
    cactusRects.push_back(cactusRect);
}

int birdGap = 500;

if (birdX.empty() || birdX.back() <= SCREEN_WIDTH - birdGap) {
    int randomX = rand() % (SCREEN_HEIGHT- SCREEN_WIDTH ) ; // Ensure bird appears from the right side
    int gap = randomX +600;
    birdX.push_back(gap); // Add a new bird at the right edge of the screen
    SDL_Rect birdRect = { birdX.back(), 270, BIRD_WIDTH, BIRD_HEIGHT };
    birdRects.push_back(birdRect);
}







            if(score>=threshold){
                cactusSpeed+=increase;
                threshold +=10;
                birdSpeed+=increase;

            }


            // Move all cacti forward
            for (int i = 0; i < cactusX.size(); ++i) {
                cactusX[i] -= cactusSpeed;
                cactusRects[i].x = cactusX[i];
            }

            for (int i = 0; i < birdX.size(); ++i) {
                birdX[i] -= birdSpeed;
                birdRects[i].x = birdX[i]-230;
            }
        }

        graphics.prepareScene();
        background.scroll(10);
        graphics.renderback(background);

        // Render cacti and check for collisions
        for (int i = 0; i < cactusX.size(); ++i) {
            cactus.tick();
            graphics.renderTexture(cactusTexture, cactusX[i]-20, 390);
           drawBoundingBox(graphics.getRenderer(), cactusRects[i]);

            // Adjust the Y position as needed
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, cactusRects[i])) {
                 graphics.play(gCrash);

                quit = true;
                break;
            }
        }

         for (int i = 0; i < birdX.size(); ++i) {
            bird.tick();
            graphics.render(birdX[i]-220,270,bird);
           drawBoundingBox(graphics.getRenderer(), birdRects[i]);

            // Adjust the Y position as needed
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, birdRects[i])) {
               graphics.play(gCrash);
                quit = true;
                break;
            }
        }

        t_rex.tick();
        graphics.render(trexX, trexY, t_rex);





        // Remove cacti that are off the screen
        /*while (!cactusX.empty() && cactusX.front() < -CACTUS_WIDTH) {
            cactusX.erase(cactusX.begin());
            cactusRects.erase(cactusRects.begin());
        }

         while (!birdX.empty() && birdX.front() < -BIRD_WIDTH) {
            birdX.erase(birdX.begin());
            birdRects.erase(birdRects.begin());
        }
        */


        graphics.presentScene();

        SDL_Delay(58);
    }

    SDL_DestroyTexture(t_rexTexture);
    SDL_DestroyTexture(cactusTexture);
    SDL_DestroyTexture(birdTexture);
   /* SDL_DestroyTexture (helloText);
    helloText= NULL;
    TTF_CloseFont(font);
    */

    t_rexTexture = nullptr;
    cactusTexture= nullptr;
    birdTexture = nullptr;

     if (gMusic != nullptr) Mix_FreeMusic( gMusic );
      if (gMusic != nullptr) Mix_FreeChunk( gJump );




    graphics.quit();
    return 0;
}
