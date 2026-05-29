#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "Manager/InputManager.h"

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
}

void GameOverScene::Update(void)
{
    InputManager& inputIns = InputManager::GetInstance();

    // スペースキー or パッドの決定ボタン
    if (inputIns.IsNew(KEY_INPUT_SPACE) ||
        inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1,
            InputManager::JOYPAD_BTN::DOWN))
    {
        SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
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