#pragma once
#include <vector>
#include <list>
#include "SceneBase.h"
#include "PlayerFront.h"
#include "EnemyBase.h"
class GameScene :
    public SceneBase
{
public:

	//エンカウント(値が大きいと出現する間隔が長くなる)
	static constexpr int ENCOUNT = 180;

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
	EnemyBase* enemy_;

	//Enemyクラスのインスタンスのポインタの可変長テーブル
	//複数の敵を動的に管理する
	std::vector<EnemyBase*> enemys;

	//敵の足元のY座標の小さい順にソートするための可変長テーブル
	std::list<EnemyBase*>enemySortTbl;

	//敵の発生頻度用のカウンター
	int enCounter;

	void EraseEnemys(void);   //敵のデータテーブルを空にする

	//当たり判定処理
	void CollisionCheck(void);
	bool CollisionChackRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2);
};

