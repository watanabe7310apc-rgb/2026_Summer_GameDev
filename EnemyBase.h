/*
#pragma once
#include <string>
#pragma once
#include <string>
#include "Vector2.h"
#include "Vector2F.h"
#include "AsoUtility.h"

class GameScene;

class EnemyBase;
{

public:

	// 方向ごとのアニメーション数
	static constexpr int NUM_ANIM = 4;

	// 敵の種類
	enum class TYPE
	{
		SLIME
		ZOMBIE
		SOLDIER
	};

	// コンストラクタ
	EnemyBase(void);

	// デストラクタ
	virtual ~EnemyBase(void);

	// 初期処理(最初の１回のみ実行)
	virtual void Init(GameScene* scene);

	// パラメータ設定(純粋仮想関数)
	virtual void SetParam(void) = 0;

	// 更新処理(毎フレーム実行)
	virtual void Update(void);

	// 描画処理(毎フレーム実行)
	virtual void Draw(void);

	// 解放処理(最後の１回のみ実行)
	virtual void Release(void);

	// 座標の取得
	Vector2F GetPos(void);

	// 座標の設定
	void SetPos(Vector2F pos);

	// 画像サイズの取得
	Vector2 GetSize(void);

	// 生存判定
	bool IsAlive(void);

	// 生存判定
	void SetAlive(bool alive);

	// ダメージを与える
	void Damage(int damage);

	// 足元座標
	int GetFootPosY(void);

protected:

	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// 画像のファイル名
	std::string imgFileName;

	// 画像
	int imgs_[static_cast<int>(AsoUtility::DIR::MAX)][NUM_ANIM];

	// 画像のサイズ
	Vector2 size_;

	// 表示座標
	Vector2F pos_;

	// 移動速度
	float speed_;

	// 移動方向
	AsoUtility::DIR dir_;

	// アニメーション
	int cntAnim_;

	// アニメーション速度
	float speedAnim_;

	// 体力
	int hp_;

	// 体力最大値
	int hpMax_;

	// 生存判定
	bool isAlive_;

	// 画像の向きを変える
	void SetAnimDir(Vector2F direction);
};

*/