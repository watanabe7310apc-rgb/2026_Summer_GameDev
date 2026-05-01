#pragma once

#include"..//Src/Fader.h"
#include"..//StDefine.h"

class SceneBase;

class SceneManager
{
public:
	SceneManager(void);   //コンストラクタ
	~SceneManager(void);  //デストラクタ

	void SystemInit(void);   //初期化処理(最初の1回のみ実行)
	void GameInit(void);     //ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);       //更新処理
	void Draw(void);         //描画処理
	void Release(void);      //解放処理(最後の1回のみ実行)

	bool ChangeScene(E_SCENE_ID id);
	void ReleaseScene(E_SCENE_ID id);

private:
	Fader* fader;          //フェーダークラスのインスタンスのポインタ
	bool sceneChangeFlg;   //シーンチェンジ実行中のフラグ

	E_SCENE_ID scene_ID;   //現在のシーンID
	E_SCENE_ID waitScene;  //シーンチェンジで次に遷移するシーンのID
};