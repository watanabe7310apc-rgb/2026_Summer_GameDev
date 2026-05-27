#pragma once

#include "Src/Vector2.h"
#include "Src/Vector2F.h"
#include "Src/AsoUtility.h"

class GameScene;

class EnemyBase
{
public:
	
	//敵の種類
	enum E_ENEMY_ID {
		E_TYPE_DRAGON,

		E_TYPE_MAX
	};

	//アニメーション速度
	static constexpr float ANIM_SPEED = 0.1f;

	//コンストラクタ
	EnemyBase(void);

	//デストラクタ
	~EnemyBase(void);

	//初期化処理(最初の1回のみ実行)
	virtual void SystemInit(GameScene* gs);

	//ゲーム起動・再開時に必ず呼び出す処理
	virtual void GameInit(void);

	//更新処理
	virtual void Update(void);

	//描画処理
	virtual void Draw(void);

	//解放処理(最後の1回のみ使用)
	virtual void Release(void);

	//敵の個別のパラメータ設定
	virtual void SetEnemyParam(void) = 0;

	//敵の位置を取得
	virtual Vector2F GetEnemyPos(void) { return pos; }

	//敵の画像サイズを取得
	virtual Vector2 GetEnemySize(void) { return size; }

	//敵の生存状態を取得
	virtual bool GetAlive(void) { return aliveFlg; }

	//敵の生存状態を設定する
	virtual void SetAlive(bool bflg) { aliveFlg = bflg; }

	//ダメージを与える
	void SetDamage(int dp);

	//敵キャラの足元座標を取得する
	int GetEnemyFootPosY(void);

	//敵の種類
	int enemyType;

protected:

	//画像の読み込み
	void LoadImages(void);

	//敵画像のハンドル番号
	int imgDragon_[4];

	//敵表示座標
	Vector2F pos;

	//アニメーションカウンター
	float stepAnim;

	//ヒットポイント
	int hp;

	//ヒットポイントの最大値
	int hpMax;

	//生存フラグ
	bool aliveFlg;

	//敵の画像サイズ
	Vector2 size;

	//敵の移動速度
	float speed;

};

