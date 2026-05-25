#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{
	imgGameOver_ = LoadGraph("Image/UI/Gameover.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");

    prevKey_ = nowKey_ = 0;
    prevPad_ = nowPad_ = 0;
}

void GameOverScene::Update(void)
{
    // キーボード (スペースキー)
    prevKey_ = nowKey_;
    nowKey_ = CheckHitKey(KEY_INPUT_SPACE);

    // パッド（ボタン1）
    prevPad_ = nowPad_;
    nowPad_ = GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1;

    bool keyUp = (prevKey_ == 1 && nowKey_ == 0);
    bool padUp = (prevPad_ != 0 && nowPad_ == 0);

    if (keyUp || padUp)
    {
        SceneManager::GetInstance().ChangeScene(E_SCENE_GAME);
    }
}

void GameOverScene::Draw(void)
{
	int gw, gh;
	int sw, sh;

    // ゲームオーバー画像のサイズ取得
    GetGraphSize(imgGameOver_, &gw, &gh);

    DrawGraph(
        (Application::SCREEN_SIZE_X / 2) - (gw / 2),
        (Application::SCREEN_SIZE_Y / 2) - (gh / 2) - 100,
        imgGameOver_,
        true
    );

    // スタートキー画像のサイズ取得
    GetGraphSize(imgStart_, &sw, &sh);

    DrawGraph(
        (Application::SCREEN_SIZE_X / 2) - (sw / 2),
        (Application::SCREEN_SIZE_Y / 2) - (sh / 2) + 100,
        imgStart_,
        true
    );
}

void GameOverScene::Release(void)
{
    DeleteGraph(imgGameOver_);
    DeleteGraph(imgStart_);
}