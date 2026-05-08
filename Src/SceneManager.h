#pragma once
#include<chrono>
#include<DxLib.h>
#include"..//StDefine.h"

class Fader;
class SceneBase;

class SceneManager
{
public:

	//インスタンスの生成
	static void CreateInstance(void);

	//インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);   //初期化処理(最初の1回のみ実行)
	void Update(void);       //更新処理
	void Draw(void);         //描画処理
	void Release(void);      //解放処理(最後の1回のみ実行)

	void ChangeScene(E_SCENE_ID id);
	void ReleaseScene(E_SCENE_ID id);

private:

	//静的インスタンス
	static SceneManager* instance_;

	SceneManager(void);   //コンストラクタ
	~SceneManager(void);  //デストラクタ

	SceneBase* scene_;     //各種シーン
	Fader* fader;          //フェーダークラスのインスタンスのポインタ
	bool sceneChangeFlg;   //シーンチェンジ実行中のフラグ

	E_SCENE_ID scene_Id;   //現在のシーンID
	E_SCENE_ID waitScene;  //シーンチェンジで次に遷移するシーンのID

	//シーン遷移
	void DoChangeScene(E_SCENE_ID sceneId);

	void Fade(void);

	//シーン遷移中判定
	bool isSceneChanging_;
};