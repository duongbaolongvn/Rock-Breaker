
#include "Bang.h"

Bang::Bang(SDL_Renderer* renderer): ObjectStatus(renderer) {
    SDL_Surface* surface = IMG_Load("/Users/duongbaolong/Desktop/SDL2/Rock Breaker/bricks.png");
    bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("/Users/duongbaolong/Desktop/SDL2/Rock Breaker/side.png");
    sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 16;
    y = 0;
    Chieurong = 768;
    Chieucao = 600;

    VTtuongx = 0;
    VTtuongy = 16;
}

Bang::~Bang() {
    SDL_DestroyTexture(bricktexture);
    SDL_DestroyTexture(sidetexture);
}

void Bang::Update(float delta) {

}

void Bang::Render(float delta) {
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = Rock[i][j];
            if (!brick.state)
                continue;

            SDL_Rect srcrect;

            srcrect.x = (brick.type % 2) * BOARD_BRWIDTH;
            srcrect.y = (brick.type / 2) * BOARD_BRHEIGHT;
            srcrect.w = BOARD_BRWIDTH;
            srcrect.h = BOARD_BRHEIGHT;

            SDL_Rect dstrect;
            dstrect.x = VTtuongx + x + i * BOARD_BRWIDTH;
            dstrect.y = VTtuongy + y + j * BOARD_BRHEIGHT;
            dstrect.w = BOARD_BRWIDTH;
            dstrect.h = BOARD_BRHEIGHT;

            SDL_RenderCopy(renderer, bricktexture, &srcrect, &dstrect);
        }
    }
    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 16;
    dstrect.h = 600;
    SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);

    dstrect.x = 800 - 16;
    dstrect.y = 0;
    dstrect.w = 16;
    dstrect.h = 600;
    SDL_RenderCopy(renderer, sidetexture, 0, &dstrect);
}

void Bang::CreateLevel() {
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick;

            brick.type = rand() % 4;   
            brick.state = true;
            Rock[i][j] = brick;
        }
    }
}
