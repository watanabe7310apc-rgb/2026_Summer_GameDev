#include <DxLib.h>
#include "EnemyBase.h"
#include "Enemy.h"

EnemyBase::EnemyBase(void) {

}

EnemyBase::~EnemyBase(void) {

}

bool EnemyBase::SystemInit(GameScene* gs) {

	gInst = gs;
	//敵キャラ個別のパラメータ設定処理
	SetEnemyParam();

	std::string path = "image/";
	path += imgFName;
	int err = LoadDivGraph(path.c_str(), CHARA_MAX,
		ANIM_NUMS, static_cast<int>(AsoUtility::DIRECTION::E_DIR_MAX),
		size.x, size.y, enemy_img[0]);

	if (err == -1)return false;

	return true;
}