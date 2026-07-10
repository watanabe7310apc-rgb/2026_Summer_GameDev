#include <DxLib.h>
#include "EnemyShip.h"
#include "Src/Application.h"

void EnemyShip::SetEnemyParam(void)
{
	//敵の画像サイズ
	size = { 64,62 };
	//初期位置
	enemySpoanPoint = GetRand(1);

	switch (enemySpoanPoint) {
	case 0:
		pos = { -64.0f,100.0f };
		break;
	case 1:
		pos = { Application::SCREEN_SIZE_X,100.0f };
		break;
	}
	//敵の移動速度
	speed = 0.5f;
	//ヒットポイント
	hp = hpMax = 10;
}

void EnemyShip::Update()
{
	if (waiting)
	{
		respawnTimer--;

		if (respawnTimer <= 0)
		{
			SetEnemyParam();
			waiting = false;
		}

		return;
	}

	EnemyBase::Update();

	if (pos.x < -size.x ||
		pos.x > Application::SCREEN_SIZE_X + size.x)
	{
		waiting = true;
		respawnTimer = 100;
	}
}