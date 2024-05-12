#include "graphics1.h"
#include "defs.h"
#include "game.h"

using namespace std;

bool isPlaying = false;

void drawBoundingBox(SDL_Renderer* renderer, const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set the color to red
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
    SDL_Event e;
    bool quit =false;
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
        while (SDL_PollEvent(&e)!=0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
// Vao choi game
                if (mouseX >= newGameBox.x && mouseX < newGameBox.x + newGameBox.w &&
                    mouseY >= newGameBox.y && mouseY < newGameBox.y + newGameBox.h) {
                    //GameOver = false;
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
    bool quit =false;

    int randomX;
    int lastCactus = SDL_GetTicks();
    int lastBird =0;
    int Gap = 500;



     // Store the positions of cacti and their collision rectangles
    vector<int> cactusX;
    vector<SDL_Rect> cactusRects;
    vector<int> birdX;
    vector<SDL_Rect> birdRects;

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



    while (!quit) {
        // Hien thi lua chon sau khi thua
        if(GameOver){
        // Ve New Game hoac Exit
                graphics.renderTexture(newGame, 270, 250);
                drawBoundingBox(graphics.getRenderer(), newGameBox);
                graphics.renderTexture(Exit, 330, 330);
                drawBoundingBox(graphics.getRenderer(), exitBox);
        //Ve diem sau khi thua
                TTF_Font* font = graphics.loadFont("fonts/purisa.ttf",55 );
                SDL_Color color = {0, 0, 0, 255};
                SDL_Texture* AfterScore = graphics.renderText(currentScore, font, color);
                graphics.renderTexture(AfterScore, 200, 150);

                graphics.presentScene();
            while(SDL_PollEvent(&e)!=0){
                if(e.type==SDL_QUIT){
                    quit = true;
                }
                else if(e.type == SDL_MOUSEBUTTONDOWN){
                        int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
            // Vao choi game
                if (mouseX >= newGameBox.x && mouseX < newGameBox.x + newGameBox.w &&
                    mouseY >= newGameBox.y && mouseY < newGameBox.y + newGameBox.h) {

                    for (int i = 0; i < cactusX.size(); ++i) {
                    cactusX[i] =800 ;
                    cactusRects[i].x = cactusX[i];
                    graphics.renderTexture(cactusTexture, cactusX[i], 390);

                }



                    GameOver = false;

                }
//Thoat game ra
                if (mouseX >= exitBox.x && mouseX < exitBox.x + exitBox.w &&
                    mouseY >= exitBox.y && mouseY < exitBox.y + exitBox.h) {
                    quit=true;
                }
                }
            }
        }


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


        if (!GameOver) {
            move();

            srand(time(0));

            if (cactusX.empty() || cactusX.back() <= SCREEN_WIDTH - Gap) {
                randomX= SCREEN_WIDTH;
                cactusX.push_back(randomX); // Add a new cactus at the right edge of the screen
                SDL_Rect cactusRect = { cactusX.back(), 440, CACTUS_WIDTH, CACTUS_HEIGHT };
                cactusRects.push_back(cactusRect);
            }
            else if (birdX.empty() || birdX.back() <= SCREEN_WIDTH - Gap) {
                int birdx= SCREEN_WIDTH;
                birdX.push_back(birdx); // Add a new bird at the right edge of the screen
                SDL_Rect birdRect = { birdX.back() , 270, BIRD_WIDTH, BIRD_HEIGHT };
                birdRects.push_back(birdRect);
            }

            int now = SDL_GetTicks();
            int time = 1000;
            int a = score/100+1;
            if(now-lastCactus >= time){
        // Move all cacti forward
                for (int i = 0; i < cactusX.size(); ++i) {
                    cactusX[i] -= 8+a ;
                    cactusRects[i].x = cactusX[i];
                }
            }

            int minTime = 1000; // Thời gian tối thiểu (ms) giữa các lần xuất hiện con chim
            int maxTime = 5000; // Thời gian tối đa (ms) giữa các lần xuất hiện con chim
            lastBird =   SDL_GetTicks();
            int birdTime=  minTime + rand() % (maxTime - minTime + 1); ;

            if(now-lastBird >= birdTime){
                    for (int i = 0; i < birdX.size(); ++i) {
                        birdX[i] -= 8+a;
                        birdRects[i].x = birdX[i] ;
            }
            }


        graphics.renderTexture(printScore, 600, 50);
        background.scroll(10);
        graphics.presentScene();
        graphics.renderback(background);
        t_rex.tick();
        graphics.render(trexX, trexY, t_rex);


        ScurrentScore = ("Score: "+ to_string(score));
        currentScore = ScurrentScore.c_str();
        printScore = graphics.renderText(currentScore, font, color);

        // Render cacti and check for collisions
        for (int i = 0; i < cactusX.size(); ++i) {
            cactus.tick();
            graphics.renderTexture(cactusTexture, cactusX[i]-20, 390);
            drawBoundingBox(graphics.getRenderer(), cactusRects[i]);

            // Adjust the Y position as needed
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, cactusRects[i])) {
                 graphics.play(gCrash);
                 /*quit = true;
                 isPlaying=false;
                 */
                 GameOver = true;
                 break;
            }
        }

         for (int i = 0; i < birdX.size(); ++i) {
            bird.bat_tick() ;
            graphics.render(birdX[i]-175,270,bird);
            drawBoundingBox(graphics.getRenderer(), birdRects[i]);

            // Adjust the Y position as needed
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, birdRects[i])) {
                graphics.play(gCrash);
               /* isPlaying=false;
                quit=true;
                */
                GameOver = true;
                break;
            }
        }
        }

        SDL_Delay(50);

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

