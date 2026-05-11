#pragma once

class SceneBase
{
public:
	//コンストラクタ
	SceneBase(void);

	//デストラクタ
	virtual ~SceneBase(void) = 0;

	//初期化処理(最初の1回のみ実行)
	virtual void SystemInit(void) = 0;

	//ゲーム起動・再開時に必ず呼び出す処理
	virtual void GameInit(void) = 0;

	//更新処理
	virtual void Update(void) = 0;

	//描画処理
	virtual void Draw(void) = 0;

	//解放処理(最後の1回のみ使用)
	virtual void Release(void) = 0;
};
