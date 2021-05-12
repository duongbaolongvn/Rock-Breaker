#include "Commonfunction.h"

Commonfunction::Commonfunction() {
    window = 0;
    renderer = 0;
}

Commonfunction::~Commonfunction() {

}

bool Commonfunction::Init() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Master of Stone Breaker",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    lasttick = SDL_GetTicks();
    fpstick = lasttick;
    fps = 0;
    framecount = 0;
    return true;
}

void Commonfunction::Clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Commonfunction::Run() {


    ngame();
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        unsigned int curtick = SDL_GetTicks();
        float delta = (curtick - lasttick) / 1000.0f;
        if (curtick - fpstick >= FPS_DELAY) {
            fps = framecount * (1000.0f / (curtick - fpstick));
            fpstick = curtick;
            framecount = 0;
            char buf[100];
            snprintf(buf, 100, "Master of Stone Breaker (fps: %u)", fps);
            SDL_SetWindowTitle(window, buf);
        } else {
            framecount++;
        }
        lasttick = curtick;

        Update(delta);
        Render(delta);
    }

    delete bang;
    delete tuong;
    delete BI;

    Clean();

    SDL_Quit();
}

void Commonfunction::ngame() {
    bang->CreateLevel();
    ntuong();
}

void Commonfunction::ntuong() {
    hientuong = true;
    nBI();
}

void Commonfunction::nBI() {
    BI->x = tuong->x + tuong->Chieurong/2 - BI->Chieurong/2;
    BI->y = tuong->y - BI->Chieucao;
}

void Commonfunction::Update(float delta) {

    int mx, my;
    Uint8 mstate = SDL_GetMouseState(&mx, &my);
    VTtuongx(mx - tuong->Chieurong/2.0f);

    if (mstate&SDL_BUTTON(1)) {
        if (hientuong) {
            hientuong = false;
            BI->SetDirection(1, -1);
        }
    }

    if (hientuong) {
        nBI();
    }

    kiemtravacham();
    vachamvoiria();
    vachamvoiRock2();

    if (sogachdaan() == 0) {
        ngame();
    }

    tuong->Update(delta);
    bang->Update(delta);

    if (!hientuong) {
        BI->Update(delta);
    }
}

void Commonfunction::VTtuongx(float x) {
    float newx;
    if (x < bang->x) {

        newx = bang->x;
    } else if (x + tuong->Chieurong > bang->x + bang->Chieurong) {
        newx = bang->x + bang->Chieurong - tuong->Chieurong;
    } else {
        newx = x;
    }
    tuong->x = newx;
}

void Commonfunction::kiemtravacham() {

    if (BI->y < bang->y) {

        BI->y = bang->y;
        BI->diry *= -1;
    } else if (BI->y + BI->Chieucao > bang->y + bang->Chieucao) {
        ntuong();
    }

    if (BI->x <= bang->x) {
        BI->x = bang->x;
        BI->dirx *= -1;
    } else if (BI->x + BI->Chieurong >= tuong->x + tuong->Chieurong) {
        BI->x = bang->x + bang->Chieurong - BI->Chieurong;
        BI->dirx *= -1;
    }
}

float Commonfunction::nhavacham(float hitx) {
    if (hitx < 0) {
        hitx = 0;
    } else if (hitx > tuong->Chieurong) {
        hitx = tuong->Chieurong;
    }
    hitx -= tuong->Chieurong / 2.0f;
    return 2.0f * (hitx / (tuong->Chieurong / 2.0f));
}


void Commonfunction::vachamvoiria() {
    float ballcenterx = BI->x + BI->Chieurong / 2.0f;
    if (BI->Collides(tuong)) {
        BI->y = tuong->y - BI->Chieucao;
        BI->SetDirection(nhavacham(ballcenterx - tuong->x), -1);
    }
}

void Commonfunction::vachamvoiRock() {
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = bang->Rock[i][j];
            if (brick.state) {

                float brickx = bang->VTtuongx + bang->x + i*BOARD_BRWIDTH;
                float bricky = bang->VTtuongy + bang->y + j*BOARD_BRHEIGHT;
                float w = 0.5f * (BI->Chieurong + BOARD_BRWIDTH);
                float h = 0.5f * (BI->Chieucao + BOARD_BRHEIGHT);
                float dx = (BI->x + 0.5f*BI->Chieurong) - (brickx + 0.5f*BOARD_BRWIDTH);
                float dy = (BI->y + 0.5f*BI->Chieucao) - (bricky + 0.5f*BOARD_BRHEIGHT);

                if (fabs(dx) <= w && fabs(dy) <= h) {
                    bang->Rock[i][j].state = false;

                    float wy = w * dy;
                    float hx = h * dx;

                    if (wy > hx) {
                        if (wy > -hx) {
                            doihuongvacham(3);
                        } else {
                            doihuongvacham(0);
                        }
                    } else {
                        if (wy > -hx) {
                            doihuongvacham(2);
                        } else {
                            doihuongvacham(1);
                        }
                    }
                    return;
                }
            }
        }
    }
}

void Commonfunction::vachamvoiRock2() {
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = bang->Rock[i][j];
            if (brick.state) {
                float Rockx = bang->VTtuongx + bang->x + i*BOARD_BRWIDTH;
                float Rocky = bang->VTtuongy + bang->y + j*BOARD_BRHEIGHT;
                float VTBIx = BI->x + 0.5f*BI->Chieurong;
                float VTBIy = BI->y + 0.5f*BI->Chieucao;
                float VTgachx = Rockx + 0.5f*BOARD_BRWIDTH;
                float VTgachy = Rocky + 0.5f*BOARD_BRHEIGHT;

                if (BI->x <= Rockx + BOARD_BRWIDTH && BI->x+BI->Chieurong >= Rockx && BI->y <= Rocky + BOARD_BRHEIGHT && BI->y + BI->Chieucao >= Rocky) {
                    bang->Rock[i][j].state = false;

                    float ymin = 0;
                    if (Rocky > BI->y) {
                        ymin = Rocky;
                    } else {
                        ymin = BI->y;
                    }

                    float ymax = 0;
                    if (Rocky+BOARD_BRHEIGHT < BI->y+BI->Chieucao) {
                        ymax = Rocky+BOARD_BRHEIGHT;
                    } else {
                        ymax = BI->y+BI->Chieucao;
                    }

                    float ysize = ymax - ymin;
                    float xmin = 0;
                    if (Rockx > BI->x) {
                        xmin = Rockx;
                    } else {
                        xmin = BI->x;
                    }

                    float xmax = 0;
                    if (Rockx+BOARD_BRWIDTH < BI->x+BI->Chieurong) {
                        xmax = Rockx+BOARD_BRWIDTH;
                    } else {
                        xmax = BI->x+BI->Chieurong;
                    }

                    float xsize = xmax - xmin;
                    if (xsize > ysize) {
                        if (VTBIy > VTgachy) {
                            BI->y += ysize + 0.01f;
                            doihuongvacham(3);
                        } else {
                            BI->y -= ysize + 0.01f;
                            doihuongvacham(1);
                        }
                    } else {
                        if (VTBIx < VTgachx) {
                            // Left
                            BI->x -= xsize + 0.01f;
                            doihuongvacham(0);
                        } else {
                            // Right
                            BI->x += xsize + 0.01f;
                            doihuongvacham(2);
                        }
                    }

                    return;
                }
            }
        }
    }
}

void Commonfunction::doihuongvacham(int VTchinh) {
    int mulx = 1;
    int muly = 1;

    if (BI->dirx > 0) {

        if (BI->diry > 0) {
            if (VTchinh == 0 || VTchinh == 3) {
                mulx = -1;
            } else {
                muly = -1;
            }
        } else if (BI->diry < 0) {

            if (VTchinh == 0 || VTchinh == 1) {
                mulx = -1;
            } else {
                muly = -1;
            }
        }
    } else if (BI->dirx < 0) {

        if (BI->diry > 0) {
            if (VTchinh == 2 || VTchinh == 3) {
                mulx = -1;
            } else {
                muly = -1;
            }
        } else if (BI->diry < 0) {
            if (VTchinh == 1 || VTchinh == 2) {
                mulx = -1;
            } else {
                muly = -1;
            }
        }
    }
    BI->SetDirection(mulx*BI->dirx, muly*BI->diry);
}

int Commonfunction::sogachdaan() {
    int Count = 0;
    for (int i=0; i<BOARD_WIDTH; i++) {
        for (int j=0; j<BOARD_HEIGHT; j++) {
            Brick brick = bang->Rock[i][j];
            if (brick.state) {
                Count++;
            }
        }
    }

    return Count;
}

void Commonfunction::Render(float delta) {
    SDL_RenderClear(renderer);

    bang->Render(delta);
    tuong->Render(delta);
    BI->Render(delta);

    SDL_RenderPresent(renderer);
}

