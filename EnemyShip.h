#pragma once
#include "EnemyBase.h"
#include "Src/Vector2.h"
#include "Bomb.h"

class EnemyShip :
    public EnemyBase
{
public:
    void SetEnemyParam(void)override;
    void Update(void) override;
    void Draw(void) override;

private:
    int respawnTimer = 0;
    bool waiting = false;

    static const int BOMB_MAX = 500;

    Bomb bomb[BOMB_MAX];

    int bombTimer;
};