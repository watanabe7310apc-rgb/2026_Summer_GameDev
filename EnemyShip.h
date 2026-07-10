#pragma once
#include "EnemyBase.h"
#include "Src/Vector2.h"

class EnemyShip :
    public EnemyBase
{
public:
    void SetEnemyParam(void)override;
    void Update(void) override;

private:
    int respawnTimer = 0;
    bool waiting = false;
};