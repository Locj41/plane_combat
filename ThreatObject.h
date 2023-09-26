#pragma once
#include"Common_Function.h"
#include "BaseObject.h"
#include"AmoObject.h"
#include <vector>

#define THREAT_WIDTH 80
#define THREAT_HEIGHT 33

class ThreatObject :
    public BaseObject
{
private:
    int x_val_;
    int y_val_;
    std::vector<AmoObject*> p_amo_list;

public:
    ThreatObject();
    ~ThreatObject();
    
    void handleMove(const int& x_border, const int& y_border);
    void hanldInputAction(SDL_Event event);

    void set_x_val_(const int& val) {
        x_val_ = val;
    }
    void set_y_val_(const int& val) {
        y_val_ = val;
    }
    int get_x_val_() const {
        return x_val_;
    }
    int get_y_val_() const {
        return y_val_;
    }
    void setAmoList(std::vector<AmoObject*> amo_list) {
        this->p_amo_list = amo_list;
    }
    std::vector<AmoObject*> getAmoList() {
        return p_amo_list;
    }
    void initAmo(AmoObject* amo);
    void makeAmo(const int& x_limit, const int& y_limit);
    void resetThreat();
};

