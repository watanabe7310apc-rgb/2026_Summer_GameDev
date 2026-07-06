
#pragma once

#include "Src/Vector2.h"
#include "Src/Vector2F.h"
#include "Src/AsoUtility.h"

class GameScene;

class EnemyBase
{
public:
	
	//謨ｵ縺ｮ遞ｮ鬘・
	enum E_ENEMY_ID {
		E_TYPE_DRAGON,
		E_TYPE_GOAST,
		E_TYPE_BOAR,
		E_TYPE_MAX
	};

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 4;


	//敵のアニメーションスピード
	static constexpr float ANIM_SPEED = 0.1f;


	//コンストラクタ
	EnemyBase(void);

	//デストラクタ
	~EnemyBase(void);

	//初期化処理(ゲーム開始時1度だけ実行)
	virtual void SystemInit(GameScene* gs);

	
	virtual void GameInit(void);

	//更新
	virtual void Update(void);

	//描画
	virtual void Draw(void);

	//解放処理
	virtual void Release(void);

	//敵のパラメータ設定
	virtual void SetEnemyParam(void) = 0;

	//敵の出現場所の設定
	virtual Vector2F GetEnemyPos(void) { return pos; }

	//敵のサイズの取得
	virtual Vector2 GetEnemySize(void) { return size; }

	//敵の生存状態の取得
	virtual bool GetAlive(void) { return aliveFlg; }

	//敵の生存状態の設定
	virtual void SetAlive(bool bflg) { aliveFlg = bflg; }

	//ダメージ処理
	void SetDamage(int dp);

	//ノックバックを開始する
	void AddKnockBack(float power);

	//ノックバック中
	bool IsKnockBack()const { return knockBackSpeed_ != 0.0f; }

	//敵の種類
	int enemyType;

	//敵の出現位置
	int enemySpoanPoint;

	//攻撃がヒットしたかを判定する
	bool hitThisAttack_;

protected:

	//ゲームシーンのインスタンスのポインタ
	GameScene* gInst;

	//敵画像のロード
	void LoadImages(void);

	//ドラゴンの画像ハンドル
	int imgDragon_[4];

	//ゴーストの画像ハンドル
	int imgGoast_[3];

	//イノシシの画像のハンドル番号
	int imgBoar_[6];

	//位置
	Vector2F pos;

	//アニメーション速度
	float stepAnim;

	//現在のHP
	int hp;

	//HPの最大値
	int hpMax;

	//生存フラグ
	bool aliveFlg;

	//サイズ
	Vector2 size;

	//移動速度
	float speed;

	//敵の向き
	AsoUtility::DIRECTION dir_;

	//敵の描画
	void DrawEnemy(int handleId);

	//ノックバック速度
	float knockBackSpeed_;

	//ノックバックの減衰率
	float knockBackDec_;

};
