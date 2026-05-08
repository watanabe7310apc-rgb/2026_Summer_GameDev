#include <DxLib.h>
#include"../Src/Application.h"
#include "SceneManager.h"
#include "Fader.h"
#include"../SceneBase.h"

SceneManager* SceneManager::instance_ = nullptr;

//コンストラクタ
SceneManager::SceneManager(void)
{
	scene_Id = E_SCENE_ID::E_SCENE_NON;
	waitScene = E_SCENE_ID::E_SCENE_NON;
	isSceneChanging_ = false;
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
	instance_->Init();
}

//インスタンスの取得
SceneManager& SceneManager::GetInstance(void)
{
	return*instance_;
}


//初期化処理(最初の1回のみ実行)
void SceneManager::Init(void)
{
	scene_Id = E_SCENE_ID::E_SCENE_GAME;
	fader = new Fader();

	SetTransColor(0xff, 0x00, 0xff);

	fader->SystemInit();

	isSceneChanging_ = false;

	//初期シーンの設定
	DoChangeScene(E_SCENE_ID::E_SCENE_GAME);
}

//更新処理
void SceneManager::Update(void)
{
	fader->Update();
	if (sceneChangeFlg)
	{
		Fade();
	}
	else
	{
		//更新
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

	//描画
	scene_->Draw();

	//最後
	fader->Draw();
}

//解放処理(最後の1回のみ実行)
void SceneManager::Release(void)
{
	scene_->Release();
	delete scene_;

	delete fader;

	delete instance_;
}

void SceneManager::ChangeScene(E_SCENE_ID id)
{
	//フェード処理が終わってからシーンを変える場合もあるため
	//遷移先シーンをメンバ変数に保持
	waitScene = id;

	//フェードアウト(暗転)を開始する
	fader->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;
}

void SceneManager::DoChangeScene(E_SCENE_ID sceneId)
{
	//現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	//シーンを変更する
	scene_Id = sceneId;
	switch (scene_Id)
	{
	case E_SCENE_ID::E_SCENE_TITLE:
		break;
	case E_SCENE_ID::E_SCENE_GAME:
		break;
	case E_SCENE_ID::E_SCENE_GAMEOVER:
		break;
	}

	//シーンの初期化
	scene_->Init();

	waitScene = E_SCENE_ID::E_SCENE_NON;
}


void SceneManager::Fade(void)
{
	//シーンチェンジ実行中
	if (fader->IsEnd() && waitScene != E_SCENE_NON) {
		//フェードアウトが終了
		ChangeScene(waitScene);
		waitScene = E_SCENE_NON;
		fader->SetFade(Fader::STATE::FADE_IN);
	}

	else if (fader->IsEnd() && waitScene == E_SCENE_NON) {
		//フェードインが終了
		sceneChangeFlg = false;
	}

}

