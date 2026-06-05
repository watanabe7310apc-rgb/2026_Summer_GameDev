#include <DxLib.h>
#include "EnemyDragon.h"
#include "Src/Application.h"

void EnemyDragon::SetEnemyParam(void)
{
	//敵の画像サイズ
	size = { 128,128 };
	//初期位置
	enemySpoanPoint = GetRand(1);

		switch (enemySpoanPoint) {
		case 0:
			pos = { -64.0f,850.0f };
			break;
		case 1:
			pos = { Application::SCREEN_SIZE_X,850.0f };
			break;
		}
	//敵の移動速度
	speed = 2.0f;
	//ヒットポイント
	hp = hpMax = 10;
}
