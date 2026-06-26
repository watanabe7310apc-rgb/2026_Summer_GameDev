#pragma once
#include "Src/Vector2.h"
#include "Src/Vector2F.h"

class Arrow
{
public:

    Vector2 pos;
    Vector2F dir;

    bool isAlive;

    int image;

    Arrow();

    void Shot(Vector2 start, Vector2 target);

    void Update();

    void Draw();

};