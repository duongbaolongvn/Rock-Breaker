
#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <stdio.h>

#include "Bang.h"
#include "Tuong.h"
#include "BI.h"

#define FPS_DELAY 600


class Commonfunction {
public:
    Commonfunction();
    ~Commonfunction();

    bool Init();
    void Run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* texture;

    unsigned int lasttick, fpstick, fps, framecount;

    float testx, testy;

    Bang* bang;
    Tuong* tuong;
    BI* BI;
    bool hientuong;

    void Clean();
    void Update(float delta);
    void Render(float delta);

    void ngame();
    void ntuong();
    void nBI();

    void VTtuongx(float x);
    void kiemtravacham();
    float nhavacham(float hitx);
    void vachamvoiria();
    void vachamvoiRock();
    void vachamvoiRock2();
    void doihuongvacham(int dirindex);
    int sogachdaan();
};

#endif

