

#ifndef Bang_H_
#define Bang_H_

#include "ObjectStatus.h"
#include <stdlib.h>
#include <time.h>

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 12
#define BOARD_BRWIDTH 64
#define BOARD_BRHEIGHT 24
#include <time.h>
class Brick {
public:
    int type;
    bool state;
};

class Bang: public ObjectStatus {
public:
    Bang(SDL_Renderer* renderer);
    ~Bang();

    void Update(float D);
    void Render(float D);
    void CreateLevel();

    float VTtuongx, VTtuongy;
    Brick Rock[BOARD_WIDTH][BOARD_HEIGHT];

private:
    SDL_Texture* bricktexture;
    SDL_Texture* sidetexture;
};

#endif
