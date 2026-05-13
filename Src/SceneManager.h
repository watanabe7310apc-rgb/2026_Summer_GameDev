#pragma once
#include <chrono>

#include"..//Src/Fader.h"
#include"..//StDefine.h"

class SceneBase;

class SceneManager
{
public:

	//インスタンスの生成
	static void CreateInstance(void);

	//インスタンスの取得
	static SceneManager& GetInstance(void);

	void SystemInit(void);   //初期化処理(最初の1回のみ実行)
	void GameInit(void);     //ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);       //更新処理
	void Draw(void);         //描画処理
	void Release(void);      //解放処理(最後の1回のみ実行)

	void ChangeScene(E_SCENE_ID id);

	E_SCENE_ID GetScene(void);   //状態遷移

private:

	//静的インスタンス
	static SceneManager* instance_;

	SceneBase* scene_;   //各種シーン
	SceneManager(void);
	~SceneManager(void);  //デストラクタ


	Fader* fader;          //フェーダークラスのインスタンスのポインタ
	bool sceneChangeFlg;   //シーンチェンジ実行中のフラグ

	E_SCENE_ID scene_ID;   //現在のシーンID
	E_SCENE_ID waitScene;  //シーンチェンジで次に遷移するシーンのID

	//シーン遷移
	void DoChangeScene(E_SCENE_ID sceneId);

	//フェード処理
	void Fade(void);
};