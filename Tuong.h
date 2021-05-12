
#ifndef Tuong_H_
#define Tuong_H_

#include "ObjectStatus.h"

class Tuong: public ObjectStatus {
public:
    Tuong(SDL_Renderer* renderer);
    ~Tuong();

    void Update(float delta);
    void Render(float delta);

private:
    SDL_Texture* texture;
};

#endif
