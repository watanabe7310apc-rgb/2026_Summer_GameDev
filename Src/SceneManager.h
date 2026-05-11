#pragma once
#include <chrono>

#include"..//Src/Fader.h"
#include"..//StDefine.h"

class SceneBase;

class SceneManager
{
public:

<<<<<<< HEAD
	//インスタンスの生成
	static void CreateInstance(void);

	//インスタンスの取得
	static SceneManager& GetInstance(void);
=======
	void CreateInstance(void);   //インスタンスの生成
	SceneManager& GetInstance(void);   //インスタンスの取得
>>>>>>> origin/main

	void SystemInit(void);   //初期化処理(最初の1回のみ実行)
	void GameInit(void);     //ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);       //更新処理
	void Draw(void);         //描画処理
	void Release(void);      //解放処理(最後の1回のみ実行)

	void ChangeScene(E_SCENE_ID id);

	E_SCENE_ID GetScene(E_SCENE_ID nextId);   //状態遷移

private:

	//静的インスタンス
	static SceneManager* instance_;

	SceneManager(void);   //コンストラクタ
<<<<<<< HEAD
	~SceneManager(void);  //デストラクタ

	SceneBase* scene_;
=======
	SceneManager(const SceneManager& instance) = default;
	~SceneManager(void);  //デストラクタ


>>>>>>> origin/main
	Fader* fader;          //フェーダークラスのインスタンスのポインタ
	bool sceneChangeFlg;   //シーンチェンジ実行中のフラグ

	E_SCENE_ID scene_ID;   //現在のシーンID
	E_SCENE_ID waitScene;  //シーンチェンジで次に遷移するシーンのID
<<<<<<< HEAD

	//シーン遷移
	void DoChangeScene(E_SCENE_ID sceneId);

	//フェード処理
	void Fade(void);
=======
	SceneBase* scene_;     //各種シーン

	void DoChangeScene(E_SCENE_ID sceneId);   //シーン遷移

	void Fade(void);   //フェード処理
>>>>>>> origin/main
};