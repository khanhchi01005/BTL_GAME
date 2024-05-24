#ifndef _DEFS__H
#define _DEFS__H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int GROUND_HEIGHT = 99;
    const int T_REX_HEIGHT = 68;
    const int T_REX_WIDTH = 50;
    const int CACTUS_HEIGHT =  70;
    const int CACTUS_WIDTH = 10;
    const int CLOUD_WIDTH = 30;
    const int CLOUD_HEIGHT =30;
    const int JUMP_FORCE =/*36*/ 32;
    const char* WINDOW_TITLE = "Game Project";
    const char* CLOUD_FILE ="img/chim.png";
    const char* T_REX_SPRITE_FILE = "img\\char.png";
    const int T_REX_CLIPS[][4] = {
    {  0, 0, 57, 68},
    { 60, 0, 57, 68},
    {115, 0, 57, 68},
    {174, 0, 57, 68},
    {233, 0, 57, 68},
    {295, 0, 57, 68},
    };
    const int T_REX_FRAMES = sizeof(T_REX_CLIPS)/sizeof(int)/4;

    const char* BIRD_FILE ="img/chim.png";
    const int BIRD_CLIPS[][4] = {
    {  0, 0, 45, 58},
    { 46, 0, 45, 58},
    {94, 0, 45, 58},
    {136, 0, 45, 58},
    {185, 0, 45, 58},
    {234, 0, 45, 58},
    {273,0, 45, 58},
    };
    const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;

    static int highscore =0;
    int score =0;
    int Gap = 700;
    int x_axis=0;
    int a = score/100+1;
    int trexX=SCREEN_WIDTH/6;
    int trexY = SCREEN_HEIGHT-GROUND_HEIGHT-T_REX_HEIGHT;
    int dx=0,dy=0;

    bool GameOver = false;
    bool playgame=0;
    bool isPlaying = false;
    bool isPlayingMusic =true;
    bool isJumping = false;
    bool Reset = false;
    int currentFrame = 0;
    int t_rex_tick = SDL_GetTicks();
    int bird_tick = SDL_GetTicks();
    bool inHelpMenu = false;


#endif
