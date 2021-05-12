

#include "BI.h"

BI::BI(SDL_Renderer* renderer): ObjectStatus(renderer) {
    SDL_Surface* surface = IMG_Load("/Users/duongbaolong/Desktop/SDL2/Rock Breaker/ball.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 0;
    y = 0;
    Chieurong = 24;
    Chieucao = 24;

    SetDirection(1, 1);
}

BI::~BI() {
    SDL_DestroyTexture(texture);
}

void BI::Update(float delta) {
    x += dirx * delta;
    y += diry * delta;
}

void BI::Render(float delta) {
    SDL_Rect rect;
    rect.x = (int)(x + 0.5f);
    rect.y = (int)(y + 0.5f);
    rect.w = Chieurong;
    rect.h = Chieucao;
    SDL_RenderCopy(renderer, texture, 0, &rect);
}

void BI::SetDirection(float dirx, float diry) {
    float length = sqrt(dirx * dirx + diry * diry);
    this->dirx = BALL_SPEED * (dirx / length);
    this->diry = BALL_SPEED * (diry / length);
}
