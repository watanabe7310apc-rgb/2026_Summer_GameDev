#include <DxLib.h>
#include "EnemyShip.h"
#include "Src/Application.h"

void EnemyShip::SetEnemyParam(void)
{
	//敵の画像サイズ
	size = { 64,62 };

	enemyType = E_ENEMY_ID_2::E_TYPE_SHIP_2;
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
	hp = hpMax = 20;

	// 爆弾の発射間隔
	bombTimer = 150;
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

	// 爆弾タイマー
	bombTimer--;

	if (bombTimer <= 0)
	{
		bombTimer = 150;

		for (int i = 0; i < BOMB_MAX; i++)
		{
			if (!bomb[i].GetAlive())
			{
				bool left = (enemySpoanPoint == 1);
				bomb[i].Shot(pos.x, pos.y + size.y / 2,left);
				break;
			}
		}
	}

	for (int i = 0; i < BOMB_MAX; i++)
	{
		bomb[i].Update();
	}

	if (pos.x < -size.x ||
		pos.x > Application::SCREEN_SIZE_X + size.x)
	{
		waiting = true;
		respawnTimer = 100;
	}
}

void EnemyShip::Draw()
{
	EnemyBase::Draw();

	for (int i = 0; i < BOMB_MAX; i++)
	{
		bomb[i].Draw();
	}
}