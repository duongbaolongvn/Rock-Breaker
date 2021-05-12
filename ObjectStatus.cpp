

#include "ObjectStatus.h"

ObjectStatus::ObjectStatus(SDL_Renderer* renderer) {
    this->renderer = renderer;

    x = 0;
    y = 0;
    Chieurong = 1;
    Chieucao = 1;
}

ObjectStatus::~ObjectStatus() {
}

void ObjectStatus::Update(float D) {
}

void ObjectStatus::Render(float D) {
}

bool ObjectStatus::Collides(ObjectStatus* z) {
    if (x + Chieurong > z->x && x < z->x + z->Chieurong &&
        y + Chieucao > z->y && y < z->y + z->Chieucao) {
        return true;
    }
    return false;
}
