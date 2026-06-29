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

    // 矢の座標を取得
    Vector2 GetPos()
    {
        return pos;
    }

    // 矢を消す
    void Destroy()
    {
        isAlive = false;
    }

    // 矢の当たり判定サイズ
    static const int SIZE_X = 20;
    static const int SIZE_Y = 8;
};