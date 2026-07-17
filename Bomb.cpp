#include "Bomb.h"
#include "Src/Application.h"

Bomb::Bomb()
{
    isAlive = false;
    speed = 5.0f;

    anim = 0;

    for (int i = 0; i < ANIM_MAX; i++)
    {
        image[i] = -1;
    }

    LoadDivGraph(
        "Image/Bomb.png",
        ANIM_MAX,
        ANIM_MAX,
        1,
        48,
        40,
        image
    );
}

void Bomb::Shot(float x, float y,bool left)
{
    pos.x = x;
    pos.y = y;

    isAlive = true;

    anim = 0;

    isLeftDir = left;
}

bool Bomb::HitCheck(float playerX, float playerY, float playerW, float playerH)
{
    if (!isAlive) return false;

    float bombLeft = pos.x - 24;
    float bombRight = pos.x + 24;
    float bombTop = pos.y - 20;
    float bombBottom = pos.y + 20;

    float playerLeft = playerX - playerW / 2;
    float playerRight = playerX + playerW / 2;
    float playerTop = playerY - playerH / 2;
    float playerBottom = playerY + playerH / 2;

    if (bombRight > playerLeft &&
        bombLeft < playerRight &&
        bombBottom > playerTop &&
        bombTop < playerBottom)
    {
        isAlive = false;
        return true;
    }

    return false;
}

void Bomb::Update()
{
    if (!isAlive) return;

    pos.y += speed;

    anim += 0.2f;

    if (anim >= ANIM_MAX)
    {
        anim = 0;
    }
}

void Bomb::Draw()
{
    if (!isAlive) return;

    DrawRotaGraph(
        (int)pos.x,
        (int)pos.y,
        1.5,
        0.0,
        image[(int)anim],
        TRUE,
        isLeftDir
    );
}