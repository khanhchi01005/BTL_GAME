#include "graphics1.h"
#include "defs.h"
#include "game.h"

using namespace std;

bool isPlaying = false;
void drawBoundingBox(SDL_Renderer* renderer, const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the color to red
    SDL_RenderDrawRect(renderer, &rect); // Draw the rectangle
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

int main(int argc, char* argv[]) {
   Graphics graphics;
    graphics.init();
    bool isPlaying = false;
    bool quit = false;
    SDL_Event e;
    TTF_Font* font = graphics.loadFont("fonts/purisa.ttf", 35);
    SDL_Color color = {0, 0, 0, 255};

    SDL_Texture* Menu = graphics.loadTexture("images/try.jpg");
    graphics.prepareScene(Menu);



// Welcome to my game
    SDL_Texture* WELCOME = graphics.renderText("WELCOME TO MY T-REX GAME", font, color);
    graphics.renderTexture(WELCOME, 80, 150);

// New Game
    SDL_Texture* newGame = graphics.renderText("New Game", font, color);
    graphics.renderTexture(newGame, 270, 250);
    SDL_Rect newGameBox = {250, 250, 250, 50};
    drawBoundingBox(graphics.getRenderer(), newGameBox);

// Exit
    SDL_Texture* Exit = graphics.renderText("Exit", font, color);
    graphics.renderTexture(Exit, 330, 330);
    SDL_Rect exitBox = {250, 330, 250, 50};
    drawBoundingBox(graphics.getRenderer(), exitBox);

// Instruction
    SDL_Texture* Help = graphics.renderText("Help", font, color);
    graphics.renderTexture(Help, 330, 410);
    SDL_Rect helpBox = {250, 410, 250, 50};
    drawBoundingBox(graphics.getRenderer(), helpBox);

    graphics.presentScene();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
// Vao choi game
                if (mouseX >= newGameBox.x && mouseX < newGameBox.x + newGameBox.w &&
                    mouseY >= newGameBox.y && mouseY < newGameBox.y + newGameBox.h) {
                    isPlaying = true;
                    quit=true;
                }
//Thoat game ra
                if (mouseX >= exitBox.x && mouseX < exitBox.x + exitBox.w &&
                    mouseY >= exitBox.y && mouseY < exitBox.y + exitBox.h) {
                    quit=true;
                }

                if (mouseX >= helpBox.x && mouseX < helpBox.x + helpBox.w &&
                    mouseY >= helpBox.y && mouseY < exitBox.y + exitBox.h) {
                    quit=true;
                }


            }
        }
}


if(isPlaying){
    Mix_Music *gMusic = graphics.loadMusic("music/subway.ogg");
    graphics.play(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("music/jump.wav");
    Mix_Chunk *gCrash = graphics. loadSound("music/crash.mp3");

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images/try.jpg"));

    Sprite t_rex;
    SDL_Texture* t_rexTexture = graphics.loadTexture("images/char.png");
    t_rex.init(t_rexTexture, T_REX_FRAMES, T_REX_CLIPS);

    Sprite cactus;
    SDL_Texture* cactusTexture = graphics.loadTexture("images/xuong.png");
    cactus.init(cactusTexture,CACTUS_FRAMES,CACTUS_CLIPS);

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture("images/bat.png");
    bird.init(birdTexture,BIRD_FRAMES,BIRD_CLIPS);

    TTF_Font* font = graphics.loadFont("fonts/purisa.ttf", 20);
    SDL_Color color = {0, 0, 0, 255};
    SDL_Texture* printScore;
    string ScurrentScore = ("Score: "+ to_string(score));
    const char* currentScore = ScurrentScore.c_str();
    printScore = graphics.renderText(currentScore, font, color);

    bool quit = false;
    bool isDead = false;
    SDL_Event e;
    int threshold =200;
    int increase=1;
    int cactusSpeed = 15;
    int birdSpeed = 15;
    int X1_axis,X2_axis=0;
    int randomX;

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
            } else if (e.type == SDL_KEYDOWN ) {
                if (((e.key.keysym.sym == SDLK_SPACE)|| (e.key.keysym.sym== SDLK_UP))&& !isJumping) {
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

        srand(time(0));

           int Gap = 500;
          // int birdGap = 500;

    if (cactusX.empty() || cactusX.back() <= SCREEN_WIDTH - Gap) {
        randomX = rand() % (SCREEN_WIDTH - Gap) + SCREEN_WIDTH;
        cactusX.push_back(randomX); // Add a new cactus at the right edge of the screen
        SDL_Rect cactusRect = { cactusX.back(), 440, CACTUS_WIDTH, CACTUS_HEIGHT };
        cactusRects.push_back(cactusRect);
    }
    else if (birdX.empty() || birdX.back() <= SCREEN_WIDTH - Gap) {

        birdX.push_back(randomX); // Add a new bird at the right edge of the screen
        SDL_Rect birdRect = { birdX.back() , 310, BIRD_WIDTH, BIRD_HEIGHT };
        birdRects.push_back(birdRect);
    }


    if(score>=threshold){
            cactusSpeed+=increase;
            threshold +=10;

    }

            // Move all cacti forward
    for (int i = 0; i < cactusX.size(); ++i) {
            cactusX[i] -= cactusSpeed;
            cactusRects[i].x = cactusX[i];
    }

    for (int i = 0; i < birdX.size(); ++i) {
                birdX[i] -= birdSpeed + increase + 2;
                birdRects[i].x = birdX[i] - 175;
            }
    }

        graphics.renderTexture(printScore, 600, 50);
        background.scroll(10);
        graphics.presentScene();
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
            bird.bat_tick() ;
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

        //graphics.presentScene();

        SDL_Delay(58);

        ScurrentScore = ("Score: "+ to_string(score));
        currentScore = ScurrentScore.c_str();
        printScore = graphics.renderText(currentScore, font, color);
    }



    SDL_DestroyTexture(t_rexTexture);
    SDL_DestroyTexture(cactusTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture (printScore);
    printScore= NULL;
    TTF_CloseFont(font);


    t_rexTexture = nullptr;
    cactusTexture= nullptr;
    birdTexture = nullptr;

     if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gMusic != nullptr) Mix_FreeChunk( gJump );
    graphics.quit();
}

    return 0;
}
