#pragma once
#include "BaseObject.h"
#include"Common_Function.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject :
    public BaseObject
{
private:
    int frame_;
    SDL_Rect clips_[4];
public:
    ExplosionObject();
    ~ExplosionObject();
    void setClips();
    void setFame(const int& frame) {
        frame_ = frame;
    }
    void showExplosion();

};

