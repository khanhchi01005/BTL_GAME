
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


    Mix_Music *gMusic = graphics.loadMusic("assets\\RunningAway.mp3");
    graphics.play(gMusic);


    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images/try.jpg"));

    Sprite t_rex;
    SDL_Texture* t_rexTexture = graphics.loadTexture("images/char.png");
    t_rex.init(t_rexTexture, T_REX_FRAMES, T_REX_CLIPS);

    SDL_Texture* cactus = graphics.loadTexture("images/xuong.png");

    bool quit = false;
    SDL_Event e;

    // Store the positions of cacti and their collision rectangles
    vector<int> cactusX;
    vector<SDL_Rect> cactusRects;

    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    while (!quit && !gameOver(trexX, trexY)) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE && !isJumping) {
                    isJumping = true;
                    dy = -JUMP_FORCE;
                }
            }
        }

        if (isJumping) {
            move();
        }

        if (!gameOver(trexX, trexY)) {
           move();

            int cactusGap = 500;
            if (cactusX.empty() || cactusX.back() <= SCREEN_WIDTH - cactusGap) {
                cactusX.push_back(SCREEN_WIDTH); // Add a new cactus at the right edge of the screen
                SDL_Rect cactusRect = { cactusX.back(), 390, CACTUS_WIDTH, CACTUS_HEIGHT };
                cactusRects.push_back(cactusRect);
            }

            // Move all cacti forward
            for (int i = 0; i < cactusX.size(); ++i) {
                cactusX[i] -= 20;
                cactusRects[i].x = cactusX[i];
            }
        }

        graphics.prepareScene();
        background.scroll(10);
        graphics.renderback(background);

        // Render cacti and check for collisions
        for (int i = 0; i < cactusX.size(); ++i) {
            graphics.renderTexture(cactus, cactusX[i]-20, 390);
           //  drawBoundingBox(graphics.getRenderer(), cactusRects[i]);

            // Adjust the Y position as needed
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, cactusRects[i])) {
                quit = true;
                break;
            }
        }

        t_rex.tick();
        graphics.render(trexX, trexY, t_rex);

        // Remove cacti that are off the screen
        while (!cactusX.empty() && cactusX.front() < -CACTUS_WIDTH) {
            cactusX.erase(cactusX.begin());
            cactusRects.erase(cactusRects.begin());
        }

        graphics.presentScene();
        SDL_Delay(100);
    }

    SDL_DestroyTexture(t_rexTexture);
    SDL_DestroyTexture(cactus);

    t_rexTexture = nullptr;
     if (gMusic != nullptr) Mix_FreeMusic( gMusic );
      if (gMusic != nullptr) Mix_FreeMusic( gMusic );



    graphics.quit();
    return 0;
}
