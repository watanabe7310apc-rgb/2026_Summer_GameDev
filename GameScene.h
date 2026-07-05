#pragma once
#include <vector>
#include <list>
#include "SceneBase.h"
#include "PlayerFront.h"
#include "Player2.h"
#include "EnemyBase.h"

class MenuScene;

class GameScene :
    public SceneBase
{
public:

	//エンカウント(値が大きいと出現する間隔が長くなる)
	static constexpr int ENCOUNT = 130;

	//防衛地点の耐久値
	static constexpr int BASE_HP_MAX = 3;

	//スロー表示する時間(フレーム数)
	static constexpr int SLOW_DISP_TIME = 30;

	//敵のスポーンする数
	static constexpr int ENEMY_SPOAN_MAX = 20;


	//コンストラクタ
	GameScene(void);

	//デストラクタ
	~GameScene(void);

	//初期化処理(最初の1回のみ実行)
	void SystemInit()override;

	//ゲーム起動・再開時に必ず呼び出す処理
	void GameInit(void)override;

	//更新処理
	void Update(void)override;

	//描画処理
	void Draw(void)override;

	//解放処理(最後の1回のみ使用)
	void Release(void)override;

	PlayerFront* GetLpPlayer(void) { return front_; }

	bool GetDamageFlg(void) { return Damage_; }

	bool GetClearFlg(void){ return Clear_; }


private:
	int img_;   //背景のハンドル番号
	int imgtower;//拠点のハンドル番号

	PlayerFront* front_;

	Player2* player2_;

	EnemyBase* enemy_;

	MenuScene* menu_;

	//Enemyクラスのインスタンスのポインタの可変長テーブル
	//複数の敵を動的に管理する
	std::vector<EnemyBase*> enemys;

	//敵の足元のY座標の小さい順にソートするための可変長テーブル
	std::list<EnemyBase*>enemySortTbl;

	//敵の発生頻度用のカウンター
	int enCounter;

	//敵の侵入数
	int BaseCounter;

	//敵の出現数
	int spoanCounter_;

	//敵撃破または通過数
	int clearCounter;

	void EraseEnemys(void);   //敵のデータテーブルを空にする

	//当たり判定処理
	void CollisionCheck(void);
	bool CollisionChackRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2);

	//ダメージフラグ
	bool Damage_;

	//スロー表示用のカウンター
	int slowCounter;

	//画面振動用の一時的な描画領域
	int tempScreen;

	//ステージクリア判定
	bool Clear_;

	//SE
	int SE_BaseDamage_;

	//マウス標準
	int scopeImage;


	//敵の出現量
	int SpoanMax_;

	//ウェーブ数
	int WaveMax_;

	//今のウェーブ数
	int nowWave_;
};

