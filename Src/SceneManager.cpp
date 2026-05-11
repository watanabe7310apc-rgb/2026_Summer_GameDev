#include <DxLib.h>
#include <chrono>
#include "SceneManager.h"
<<<<<<< HEAD
#include"../SceneBase.h"

SceneManager* SceneManager::instance_ = nullptr;
=======
#include "../Src/Application.h"
#include "../Src/Fader.h"
#include "../SceneBase.h"

//インスタンスの生成
void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->SystemInit();
}

//インスタンスの取得
SceneManager& SceneManager::GetInstance(void)
{
	return*instance_;
}

>>>>>>> origin/main

//コンストラクタ
SceneManager::SceneManager(void)
{
	scene_ID = waitScene = E_SCENE_ID::E_SCENE_NON;

<<<<<<< HEAD
	scene_ID = waitScene = E_SCENE_NON;

	sceneChangeFlg = false;
=======

	fader = nullptr;
>>>>>>> origin/main
}

//デストラクタ
SceneManager::~SceneManager(void)
{

}

void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->SystemInit();
}

static SceneManager& GetInstance(void);


//初期化処理(最初の1回のみ実行)
void SceneManager::SystemInit(void)
{
	scene_ID = E_SCENE_ID::E_SCENE_TITLE;
	waitScene = E_SCENE_ID::E_SCENE_NON;

	fader = new Fader();

	SetTransColor(0xff, 0x00, 0xff);

	fader->SystemInit();

	//初期シーンの設定
	DoChangeScene(E_SCENE_ID::E_SCENE_TITLE);
}

//ゲーム起動・再開時に必ず呼び出す処理
void SceneManager::GameInit(void)
{
	scene_->GameInit();
}

//更新処理
void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	fader->Update();
	if (sceneChangeFlg)
	{
		Fade();
	}
	else
	{
<<<<<<< HEAD
		//更新
=======
>>>>>>> origin/main
		scene_->Update();
	}
	
}

//描画処理
void SceneManager::Draw(void)
{
	//描画先グラフィック領域の指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画面を初期化
	ClearDrawScreen();

<<<<<<< HEAD
	//描画
	scene_->Draw();

	//最後
=======
	//描画処理
	scene_->Draw();

	//暗転・明転
>>>>>>> origin/main
	fader->Draw();
}

//解放処理(最後の1回のみ実行)
void SceneManager::Release(void)
{
<<<<<<< HEAD

=======
	//シーンの開放
>>>>>>> origin/main
	scene_->Release();
	delete scene_;

	//インスタンスの開放
	delete instance_;

	//フェード機能の開放
	fader->Release();
	delete fader;
	fader = nullptr;

	delete instance_;
}

void SceneManager::ChangeScene(E_SCENE_ID id)
{
	//フェード処理が終わってからシーンを変える場合もあるため
	//遷移先シーンをメンバ変数に保持
	waitScene = id;

	//フェードアウトを開始する
	fader->SetFade(E_FADE_STAT_ID::E_STAT_FADE_OUT);
	sceneChangeFlg = true;
}

//状態遷移
E_SCENE_ID SceneManager::GetScene(E_SCENE_ID nextId)
{
	return scene_ID;
}

//シーン遷移
void SceneManager::DoChangeScene(E_SCENE_ID sceneId)
{

	//シーンを変更する
	scene_ID = sceneId;

	//現在のシーンを開放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (scene_ID) {
	case E_SCENE_TITLE:
		break;
	case E_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	}

	//各シーンの初期化
	scene_->SystemInit();

	waitScene = E_SCENE_ID::E_SCENE_NON;
}

<<<<<<< HEAD
void SceneManager::DoChangeScene(E_SCENE_ID sceneId)
{

}
=======
//フェード処理
void SceneManager::Fade(void)
{
	//シーンチェンジ実行中
	if (fader->IsEnd() && waitScene != E_SCENE_NON) {
		//フェードアウトが終了
		ChangeScene(waitScene);
		waitScene = E_SCENE_NON;
		fader->SetFade(E_STAT_FADE_IN);
	}

	else if (fader->IsEnd() && waitScene == E_SCENE_NON) {
		//フェードインが終了
		sceneChangeFlg = false;
	}
}

>>>>>>> origin/main
