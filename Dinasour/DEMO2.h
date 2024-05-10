#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "graphics1.h"
#include "defs.h"
#include "game.h"

using namespace std;
const int ENEMY_WIDTH=40;
const int ENEMY_HEIGHT=70;

bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    // Check for x-axis overlap
    bool xOverlap = rect1.x + rect1.w >= rect2.x && rect2.x + rect2.w >= rect1.x;

    // Check for y-axis overlap
    bool yOverlap = rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y;

    // Return true if both x-axis and y-axis overlap
    return xOverlap && yOverlap;
}

void drawBoundingBox(SDL_Renderer* renderer, const SDL_Rect& rect) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set the color to red
    SDL_RenderDrawRect(renderer, &rect); // Draw the rectangle
}

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("images/try.jpg"));

    Sprite t_rex;
    SDL_Texture* t_rexTexture = graphics.loadTexture("images/char.png");
    t_rex.init(t_rexTexture, T_REX_FRAMES, T_REX_CLIPS);

    bool quit = false;
    SDL_Event e;

    // Store the positions of enemies and their collision rectangles
    vector<int> enemyX;
    vector<SDL_Rect> enemyRects;

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

            int enemyGap = 500;
            if (enemyX.empty() || enemyX.back() <= SCREEN_WIDTH - enemyGap) {
                enemyX.push_back(SCREEN_WIDTH - 10); // Add a new enemy at the right edge of the screen
                SDL_Rect enemyRect = { enemyX.back(), 390, ENEMY_WIDTH, ENEMY_HEIGHT };
                enemyRects.push_back(enemyRect);
            }

            // Move all enemies forward
            for (int i = 0; i < enemyX.size(); ++i) {
                enemyX[i] -= 18;
                enemyRects[i].x = enemyX[i];
            }
        }

        graphics.prepareScene();
        background.scroll(10);
        graphics.renderback(background);

        // Render enemies and check for collisions
        for (int i = 0; i < enemyX.size(); ++i) {
            drawBoundingBox(graphics.getRenderer(), enemyRects[i]); // Draw bounding box
            // Adjust the Y position as needed
            SDL_Rect trexRect = { trexX, trexY, T_REX_WIDTH, T_REX_HEIGHT };
            if (CheckCollision(trexRect, enemyRects[i])) {
                quit = true;
                break;
            }
        }

        t_rex.tick();
        graphics.render(trexX, trexY, t_rex);

        // Remove enemies that are off the screen
        while (!enemyX.empty() && enemyX.front() < -ENEMY_WIDTH) {
            enemyX.erase(enemyX.begin());
            enemyRects.erase(enemyRects.begin());
        }

        graphics.presentScene();
        SDL_Delay(100);
    }

    SDL_DestroyTexture(t_rexTexture);
    t_rexTexture = nullptr;

    graphics.quit();
    return 0;
}