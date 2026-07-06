#include <DxLib.h>
#include "Boar.h"
#include "Src/Application.h"

void Boar::SetEnemyParam(void)
{
	//敵の画像サイズ
	size = { 96,64 };
	//初期位置
	enemySpoanPoint = GetRand(1);

	switch (enemySpoanPoint) {
	case 0:
		pos = { -64.0f,900.0f };
		break;
	case 1:
		pos = { Application::SCREEN_SIZE_X,900.0f };
		break;
	}
	//敵の移動速度
	speed = 5.0f;

	//ヒットポイント
	hp = hpMax = 3;
}
