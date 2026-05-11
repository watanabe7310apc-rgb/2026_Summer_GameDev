#include <DxLib.h>
#include <time.h>
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void) {

	img = -1;
}

TitleScene::~TitleScene(void) {

}

bool TitleScene::SystemInit(void) {

	img = LoadGraph("image/title.bmp");
	if (img == -1)return false;

	return true;
}

void TitleScene::GameInit(void) {

	//次のシーンの初期設定
	nextSceneID = E_SCENE_TITLE;

	prevSpaceKey = nowSpaceKey = 0;
}

void TitleScene::Update(void) {
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);
	//アップトリガーを判定
	if (prevSpaceKey == 1 && nowSpaceKey == 0) {
		nextSceneID = E_SCENE_GAME;
	}
}

void TitleScene::Draw(void) {

	DrawGraph(TITLE_SIZE_HIG / 2, TITLE_SIZE_HIG / 2, img, true);
}

bool TitleScene::Release(void) {
	if (DeleteGraph(img) == -1)return false;

	return true;
}