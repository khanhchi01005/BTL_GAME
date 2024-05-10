#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib> 
#include <ctime> 
#include "graphics1.h"
#include "defs.h"
#include "game.h"

using namespace std;

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    // Check for x-axis overlap
    bool xOverlap = rect1.x + rect1.w >= rect2.x && rect2.x + rect2.w >= rect1.x;
    
    // Check for y-axis overlap
    bool yOverlap = rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y;
    
    // Return true if both x-axis and y-axis overlap
    return xOverlap && yOverlap;
}


int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();

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
                cactusX.push_back(SCREEN_WIDTH-10); // Add a new cactus at the right edge of the screen
                SDL_Rect cactusRect = { cactusX.back(), 390, CACTUS_WIDTH, CACTUS_HEIGHT };
                cactusRects.push_back(cactusRect);
            }

            // Move all cacti forward
            for (int i = 0; i < cactusX.size(); ++i) {
                cactusX[i] -= 18;
                cactusRects[i].x = cactusX[i];
            }
        }

        graphics.prepareScene();
        background.scroll(10);
        graphics.renderback(background);

        // Render cacti and check for collisions
        for (int i = 0; i < cactusX.size(); ++i) {
            graphics.renderTexture(cactus, cactusX[i], 390);

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
    t_rexTexture = nullptr;

    graphics.quit();
    return 0;
}