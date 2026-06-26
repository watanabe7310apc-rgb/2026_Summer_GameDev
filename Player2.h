#pragma once
#include "Src/Vector2.h"
#include "Arrow.h"

class Player2
{
public:

    Vector2 pos;

    int image;

    bool isRight;

    static const int ARROW_MAX = 20;

    Arrow arrow[ARROW_MAX];

    Player2();

    void Update();

    void Draw();

private:

    bool oldMouse;

    int shotCoolTime;
    static const int SHOT_INTERVAL = 30;
};