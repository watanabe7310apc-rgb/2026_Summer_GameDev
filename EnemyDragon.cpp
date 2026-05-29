#include <DxLib.h>
#include "EnemyDragon.h"

void EnemyDragon::SetEnemyParam(void)
{
	//敵の画像サイズ
	size = { 64,64 };
	//初期位置
	enemySpoanPoint = GetRand(1);

		switch (enemySpoanPoint) {
		case 0:
			pos = { -64.0f,750.0f };
			break;
		case 1:
			pos = { 1500.0f,750.0f };
			break;
		}
	//敵の移動速度
	speed = 1.5f;
	//ヒットポイント
	hp = hpMax = 10;
}
