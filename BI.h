

#ifndef BI_H_
#define BI_H_

#include "ObjectStatus.h"

#include <math.h>

const float BALL_SPEED = 600;

class BI: public ObjectStatus {
public:
    BI(SDL_Renderer* renderer);
    ~BI();

    void Update(float delta);
    void Render(float delta);

    void SetDirection(float dirx, float diry);

    float dirx, diry;

private:
    SDL_Texture* texture;

};

#endif
