#include <DxLib.h>
#include "SceneManager.h"

//コンストラクタ
SceneManager::SceneManager(void)
{
	fader = nullptr;

	scene_ID = waitScene = E_SCENE_NON;
}

//デストラクタ
SceneManager::~SceneManager(void)
{

}

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
	else {
		E_SCENE_ID nextSceneID = scene_ID;
		switch (scene_ID) {
		case E_SCENE_TITLE:
			break;
		case E_SCENE_GAME:
			break;
		case E_SCENE_GAMEOVER:
			break;
		}
		if (scene_ID != nextSceneID) {
			sceneChangeFlg = true;
			waitScene = nextSceneID;
			fader->SetFade(E_STAT_FADE_OUT);
		}
	}
}

//描画処理
void SceneManager::Draw(void)
{
	switch (scene_ID) {
	case E_SCENE_TITLE:
		break;
	caseE_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	}
	fader->Draw();
}

//解放処理(最後の1回のみ実行)
void SceneManager::Release(void)
{
	ReleaseScene(E_SCENE_TITLE);
	ReleaseScene(E_SCENE_GAME);
	ReleaseScene(E_SCENE_GAMEOVER);

	fader->Release();
	delete fader;
	fader = nullptr;
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

void SceneManager::ReleaseScene(E_SCENE_ID id)
{
	switch (id) {
	case E_SCENE_TITLE:
		break;
	case E_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	}
}
