#pragma once
#include "SceneBase.h"
#include "PlayerFront.h"
class GameScene :
    public SceneBase
{
public:
	//コンストラクタ
	GameScene(void);

	//デストラクタ
	~GameScene(void);

	//初期化処理(最初の1回のみ実行)
	void SystemInit(void)override;

	//ゲーム起動・再開時に必ず呼び出す処理
	void GameInit(void)override;

	//更新処理
	void Update(void)override;

	//描画処理
	void Draw(void)override;

	//解放処理(最後の1回のみ使用)
	void Release(void)override;

private:
	int img_;   //背景のハンドル番号

	PlayerFront* front_;

	////当たり判定処理
	//void CollisionCheck(void);
	//bool CollisionChackRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2);
};

