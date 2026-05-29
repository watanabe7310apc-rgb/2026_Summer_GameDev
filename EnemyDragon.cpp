#include <DxLib.h>
#include "EnemyDragon.h"

void EnemyDragon::SetEnemyParam(void)
{
	//敵の画像サイズ
	size = { 64,64 };

	//初期位置
	pos = { 0.0f,750.0f };

	//敵の移動速度
	speed = 1.5f;
	//ヒットポイント
	hp = hpMax = 10;
}
