#pragma once
#include <DxLib.h>

class Bomb
{
public:
    Bomb();

    void Shot(float x, float y,bool left);
    void Update();
    void Draw();

    bool GetAlive() { return isAlive; }

    bool HitCheck(float playerX, float playerY, float playerW, float playerH);
private:
    VECTOR pos;
    float speed;
    bool isAlive;
    bool isExplosion;
    bool isLeftDir;

    // アニメーション
    static const int ANIM_MAX = 9;
    static const int EXP_ANIM_MAX = 12;
    int image[ANIM_MAX];
    int explosionImage[EXP_ANIM_MAX];
    float anim;
};