#include <DxLib.h>
#include "SceneManager.h"
#include"../SceneBase.h"

SceneManager* SceneManager::instance_ = nullptr;

//コンストラクタ
SceneManager::SceneManager(void)
{
	fader = nullptr;

	scene_ID = waitScene = E_SCENE_NON;

	sceneChangeFlg = false;
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
	fader = new Fader();

	SetTransColor(0xff, 0x00, 0xff);

	fader->SystemInit();
}

//ゲーム起動・再開時に必ず呼び出す処理
void SceneManager::GameInit(void)
{
	scene_->GameInit();
}

//更新処理
void SceneManager::Update(void)
{
	fader->Update();
	if (sceneChangeFlg)
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

	fader->Release();
	delete fader;
	fader = nullptr;

	delete instance_;
}

bool SceneManager::ChangeScene(E_SCENE_ID id)
{

	//現在のシーンを解放
	ReleaseScene(scene_ID);

	//シーンIDを変更
	scene_ID = id;

	switch (scene_ID) {
	case E_SCENE_TITLE:
		break;
	case E_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	}
	return false;
}

void SceneManager::DoChangeScene(E_SCENE_ID sceneId)
{

}