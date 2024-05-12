#ifndef _DEFS__H
#define _DEFS__H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GROUND_HEIGHT = 99;
const int T_REX_HEIGHT = 68;
const int T_REX_WIDTH = 50;
const int CACTUS_HEIGHT = /*50*/ 70;
const int CACTUS_WIDTH = /*20*/ 70;
const int BIRD_WIDTH = 30;
const int BIRD_HEIGHT = 30;
const int JUMP_FORCE = /*50*/ 30;
const int FRAME_RATE = 10;
const int FRAME_DELAY = 1000 / FRAME_RATE;
int score =0;

const char* WINDOW_TITLE = "Game Project";

const char* CACTUS_FILE ="img/xuong.png";
const int CACTUS_CLIPS[][4]={
    {0,0,70,70},
    {71,0,70,70},
    {143,0,70,70},
    {216,0,70,70},
};
const int CACTUS_FRAMES = sizeof(CACTUS_CLIPS)/sizeof(int)/4;

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

const char* BIRD_FILE = "img/bat.png";
const int BIRD_CLIPS[][4]={
    {  0, 0, 30, 40},
    { 33, 0, 30, 40},
    { 65, 0, 30, 40},
    { 95, 0, 30, 40},
    {126, 0, 30, 40},
};
const int BIRD_FRAMES = sizeof(BIRD_CLIPS)/sizeof(int)/4;

#endif
