#include <DxLib.h>
#include <time.h>
#include "Src/Application.h"
#include "Src/SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void) {

	img = -1;
}

TitleScene::~TitleScene(void) {

}

void TitleScene::SystemInit(void) {

	img = LoadGraph("image/title.bmp");

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

void TitleScene::Release(void) 
{
	DeleteGraph(img);
}