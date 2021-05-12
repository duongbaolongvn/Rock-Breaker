
#include "Tuong.h"

Tuong::Tuong(SDL_Renderer* renderer): ObjectStatus(renderer) {
    SDL_Surface* surface = IMG_Load("/Users/duongbaolong/Desktop/SDL2/Rock Breaker/paddle.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    Chieurong = 128;
    Chieucao = 32;

    y = 560;
}
void Tuong::Render(float delta) {
    SDL_Rect rect;
    rect.x = (int)(x + 0.5f);
    rect.y = (int)(y + 0.5f);
    rect.w = Chieurong;
    rect.h = Chieucao;
    SDL_RenderCopy(renderer, texture, 0, &rect);
}
