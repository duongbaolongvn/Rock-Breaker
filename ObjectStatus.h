

#ifndef CHECK_H_
#define CHECK_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class ObjectStatus {
public:
    ObjectStatus(SDL_Renderer* renderer);
    virtual ~ObjectStatus();

    float x, y, Chieurong, Chieucao;

    virtual void Update(float delta);
    virtual void Render(float delta);

    bool Collides(ObjectStatus* z);
protected:
    SDL_Renderer* renderer;

};

#endif
