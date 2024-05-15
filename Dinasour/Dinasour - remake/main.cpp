#include "graphics1.h"
#include "defs.h"
#include "game.h"

using namespace std;
void drawBoundingBox(SDL_Renderer* renderer, const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set the color to red
    SDL_RenderDrawRect(renderer, &rect); // Draw the rectangle
}

int main(int argc, char* argv[]) {
    bool quit= false;
   Graphics graphics;
    graphics.init();
    SDL_Event e;
    TTF_Font* font = graphics.loadFont("fonts/swan.ttf", 35);
    TTF_Font* font2 = graphics.loadFont("purisa.ttf",35);
    SDL_Color color = {0, 0, 0, 255};

    SDL_Texture* Menu = graphics.loadTexture("images/try.jpg");
    graphics.prepareScene(Menu);

    SDL_Texture* WELCOME = graphics.renderText("Welcome to my T-rex Game", font, color);
    graphics.renderTexture(WELCOME, 150, 150);

// New Game
    SDL_Texture* newGame = graphics.renderText("New Game", font2, color);
    graphics.renderTexture(newGame, 270, 250);
    SDL_Rect newGameBox = {250, 250, 250, 50};
    drawBoundingBox(graphics.getRenderer(), newGameBox);

// Exit
    SDL_Texture* Exit = graphics.renderText("Exit", font2, color);
    graphics.renderTexture(Exit, 330, 330);
    SDL_Rect exitBox = {250, 330, 250, 50};
    drawBoundingBox(graphics.getRenderer(), exitBox);

// Instruction
    SDL_Texture* Help = graphics.renderText("Help", font2, color);
    graphics.renderTexture(Help, 330, 410);
    SDL_Rect helpBox = {250, 410, 250, 50};
    drawBoundingBox(graphics.getRenderer(), helpBox);

    SDL_Rect Help_newGameBox = {100, 350, 250, 50};
    SDL_Rect Help_exitBox = {530, 350, 250, 50};
//Music cho Menu
    Mix_Music *gMusic = graphics.loadMusic("music/theme.mp3");
    SDL_Texture* pauseMusic = graphics.loadTexture("images/pause_music.png");
    graphics.renderTexture(pauseMusic, 670,60);
    SDL_Rect musicBox = {665,55,40,40};
    drawBoundingBox(graphics.getRenderer(),musicBox);



     graphics.presentScene();


 //LOAD MENU
    while (!quit) {
       // graphics.play(gMusic);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (inHelpMenu) {
                    if (MouseOverButton(Help_newGameBox, mouseX, mouseY)) {
                        isPlaying = true;
                        quit = true;
                    } else if (MouseOverButton(Help_exitBox, mouseX, mouseY)) {
                        quit = true;
                    }
                } else {
                    if (MouseOverButton(newGameBox, mouseX, mouseY)) {
                        isPlaying = true;
                        quit=true;
                    } else if (MouseOverButton(exitBox, mouseX, mouseY)) {
                        quit = true;
                    } else if(MouseOverButton(musicBox,mouseX,mouseY)){
                        if(isPlayingMusic){
                            isPlayingMusic =false;
                        }
                        else{
                            isPlayingMusic =true;
                        }

                    } else if (MouseOverButton(helpBox, mouseX, mouseY)) {
                        inHelpMenu = true;
                    // Hiển thị màn hình trợ giúp
                        SDL_Texture* Menu = graphics.loadTexture("images/try.jpg");
                        graphics.prepareScene(Menu);
                        graphics.presentScene();

                    // Hiển thị hướng dẫn
                        TTF_Font* font = graphics.loadFont("fonts/swan.ttf", 28);
                        SDL_Texture* Instruction = graphics.renderText("Press SPACE or UP to move the T-rex away from obstacles", font, color);
                        graphics.renderTexture(Instruction, 50, 230);

                    // Hiển thị nút New Game
                        font = graphics.loadFont("fonts/purisa.ttf", 15);
                        graphics.renderTexture(newGame, 120, 350);
                        drawBoundingBox(graphics.getRenderer(), Help_newGameBox);

                    // Hiển thị nút Exit
                        graphics.renderTexture(Exit, 600, 350);
                        drawBoundingBox(graphics.getRenderer(), Help_exitBox);
                        graphics.presentScene();
                        inHelpMenu = true;
                    }
                }
            }
        }
    }
if(isPlayingMusic){
    graphics.play(gMusic);
}
    Mix_HaltMusic();




//VAN CHOI
    if(isPlaying){
        bool quit =false;
        vector<int> cactusX;
        vector<SDL_Rect> cactusRects;
        vector<int> cloudX;
        vector<SDL_Rect> cloudRects;
        int lastCactus = SDL_GetTicks();
        int lastBird =SDL_GetTicks();

        //Music
        Mix_Music *gMusic = graphics.loadMusic("music/subway.ogg");
        graphics.play(gMusic);
        Mix_Chunk *gJump = graphics.loadSound("music/jump.wav");
        Mix_Chunk *gCrash = graphics. loadSound("music/crash.mp3");

        //Background troi
        ScrollingBackground background;
        background.setTexture(graphics.loadTexture("images/try.jpg"));

        //T-rex
        Sprite t_rex;
        SDL_Texture* t_rexTexture = graphics.loadTexture("images/char.png");
        t_rex.init(t_rexTexture, T_REX_FRAMES, T_REX_CLIPS);

        //Cactus
        SDL_Texture* cactusTexture = graphics.loadTexture("images/cactus.png");

        //Cloud
        Sprite cloud;
        SDL_Texture* cloudTexture = graphics.loadTexture("images/chim.png");
        cloud.init(cloudTexture,BIRD_FRAMES,BIRD_CLIPS);

        //Font
        TTF_Font* font = graphics.loadFont("fonts/typoca.ttf", 20);
        SDL_Color color = {0, 0, 0, 255};
        //Score
        SDL_Texture* printScore;
        string ScurrentScore = ("Score: "+ to_string(score/50));
        const char* currentScore = ScurrentScore.c_str();
        printScore = graphics.renderText(currentScore, font, color);
        //High score
        SDL_Texture* printHighScore;
        string ScurrentHighScore = ("Highest Score: "+ to_string(highscore/50));
        const char* currentHighScore = ScurrentHighScore.c_str();
        printHighScore = graphics.renderText(currentHighScore, font, color);

        while (!quit) {
            //Hien thi lua hcon sau khi thua
            if(GameOver){
            // Ve New Game hoac Exit
                graphics.renderTexture(newGame, 270, 250);
                drawBoundingBox(graphics.getRenderer(), newGameBox);
                graphics.renderTexture(Exit, 330, 330);
                drawBoundingBox(graphics.getRenderer(), exitBox);
            //Ve diem sau khi thua
                TTF_Font* font = graphics.loadFont("fonts/typoca.ttf",55 );
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
                    if (MouseOverButton(newGameBox,mouseX,mouseY)) {
                        cactusX.back()=SCREEN_WIDTH+280;
                        cactusX.clear();
                        cloudX.clear();
                        if(cactusX.empty()){
                            cout <<"Empty";
                        }
                        for (int i = 0; i < cactusX.size(); ++i) {
                            x_axis = SCREEN_WIDTH;
                            cactusX.push_back(x_axis) ;
                            cactusRects[i].x = cactusX[i];
                            graphics.renderTexture(cactusTexture, cactusX[i], 390);

                    }
                        for (int i = 0; i < cloudX.size(); ++i) {
                            x_axis = SCREEN_WIDTH;
                            cloudX.push_back(x_axis) ;
                            cloudRects[i].x = cloudX[i];
                            graphics.renderTexture(cloudTexture, cloudX[i], 330);
                    }

                        score=0;
                        a=0;
                        lastBird=SDL_GetTicks();
                        lastCactus=SDL_GetTicks();
                        GameOver = false;
                        Reset = true;
                    }

            //Thoat game ra
                    if (MouseOverButton(exitBox,mouseX,mouseY)) {
                            quit=true;
                    }
                }
            }
        }



//Logic game
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
            moveUp();
            graphics.play(gJump);
        }

        if (!GameOver) {
            moveUp();
            if (cactusX.empty() || cactusX.back() <= SCREEN_WIDTH - Gap) {
                x_axis= SCREEN_WIDTH;
                cactusX.push_back(x_axis);
                SDL_Rect cactusRect = { cactusX.back(), 415, CACTUS_WIDTH, CACTUS_HEIGHT };
                cactusRects.push_back(cactusRect);
            }
            else if (cloudX.empty() || cloudX.back() <= SCREEN_WIDTH - Gap) {
                x_axis= SCREEN_WIDTH;
                cloudX.push_back(x_axis);
                SDL_Rect cloudRect = { cloudX.back() , 340, CLOUD_WIDTH, CLOUD_HEIGHT };
                cloudRects.push_back(cloudRect);
            }
            int now = SDL_GetTicks();
            int time = 1000;

            if(now-lastCactus >= time){
        // Move all cacti forward
                for (int i = 0; i < cactusX.size(); ++i) {
                    cactusX[i] -= /*12+a +20*/ 8+a ;
                    cactusRects[i].x = cactusX[i]+20;

                }
            }

            if(now-lastBird >= 3*time){
                    for (int i = 0; i < cloudX.size(); ++i) {
                        cloudX[i] -= /*18+a;*/ 8+a+1;
                        cloudRects[i].x = cloudX[i] + /*280*i*/ 280*i;
                        //counta % 3 ==0)
                        //cloudRects[i].x = cloudX[i] ;

                }
            }

        graphics.renderTexture(printScore, 600, 50);
        graphics.renderTexture(printHighScore,600,100);
        background.scroll(5);
        graphics.presentScene();
        graphics.renderback(background);
        t_rex.tick();
        graphics.render(trexX, trexY, t_rex);



        // Render cacti and check for collisions
        for (int i = 0; i < cactusX.size(); ++i) {
            graphics.renderTexture(cactusTexture, cactusX[i], 415);
            drawBoundingBox(graphics.getRenderer(), cactusRects[i]);
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, cactusRects[i]) && score >= 5) {
                 graphics.play(gCrash);
                 GameOver = true;
                 break;
            }
        }
       cloud.tick();
         for (int i = 0; i < cloudX.size(); ++i) {
            graphics.render(cloudX[i]  + 280 * i,340,cloud);
           // currentFrame =0;
            //drawBoundingBox(graphics.getRenderer(), cloudRects[i]);
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
                if (CheckCollision(trexRect, cloudRects[i]) && score >= 5) {
                                 graphics.play(gCrash);
                                 GameOver = true;
                                 break;
                            }
        }

        }


        ifstream file("highscore.txt");
        if (file){
            file >> highscore;
            file.close();
        }
        if(score >= highscore){
            highscore = score;
            ofstream outfile ("highscore.txt");
            if(outfile){
                outfile << score;
                outfile.close();
            }
        }

         // Score
        ScurrentScore = ("Score: "+ to_string(score/50));
        currentScore = ScurrentScore.c_str();
        printScore = graphics.renderText(currentScore, font, color);

        //High Score
        ScurrentHighScore = ("Highest score: "+ to_string(highscore/50));
        currentHighScore = ScurrentHighScore.c_str();
        printHighScore = graphics.renderText(currentHighScore, font, color);


        //SDL_Delay(50);


    }
    SDL_DestroyTexture(t_rexTexture);
    SDL_DestroyTexture(cactusTexture);
    SDL_DestroyTexture(cloudTexture);
    SDL_DestroyTexture (printScore);
    SDL_DestroyTexture (printHighScore);
    printScore= NULL;
    TTF_CloseFont(font);

    t_rexTexture = nullptr;
    cactusTexture= nullptr;
    cloudTexture = nullptr;

    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gMusic != nullptr) Mix_FreeChunk( gJump );
    graphics.quit();
}
    return 0;
}

