#pragma once
#include<vector>
#include <map>
#include "Src/Vector2F.h"
#include "Src/AsoUtility.h"

class PlayerFront
{
public:

	static constexpr int SIZE_X = 128;   //横サイズ

	static constexpr int SIZE_Y = 128;    //縦サイズ

	//IDLEモーションの最大アニメーション数
	static constexpr int IDLE_ALL_NUM = 10;

	//RUNモーションの最大アニメーション数
	static constexpr int RUN_ALL_NUM = 8;

	//ATTACKモーションの最大アニメーション数
	static constexpr int ATTACK_ALL_NUM = 8;

	//DAMAGEモーションの最大アニメーション数
	static constexpr int DAMAGE_ALL_NUM = 4;

	//JUMPモーションの最大フレーム数
	static constexpr int JUMP_ALL_NUM = 4;

	//アニメーション速度
	static constexpr float ANIM_SPEED = 0.1f;

	//攻撃アニメーション速度
	static constexpr float ATTACK_ANIM_SPEED = 0.3f;

	// 移動速度の最大値
	static constexpr float MAX_MOVE_SPEED = 100.0f;

	// 加速(accelerator=アクセレレーター)
	static constexpr float MOVE_ACC = 10.0f;

	// 減速(decelerate=ディセラレイト)
	static constexpr float MOVE_DEC = 0.05f;

	//最大ジャンプ力
	static constexpr float MAX_JUMP_POW = 15.0f;

	//重力
	static constexpr float GRAVITY = 0.6f;

	//ジャンプキー入力を受け付けるフレーム数
	static constexpr int INPUT_JUMP_FRAME = 5;

	//プレイヤーの最大HP
	static constexpr int FRONT_HP = 100;

	//プレイヤーの攻撃範囲
	static constexpr int ATTACK_RANGE_X = 75;
	static constexpr int ATTACK_RANGE_Y = 126;

	//アニメーション状態
	enum class ANIM_STATE
	{
		IDLE,
		RUN,
		JUMP_UP,
		JUMP_DOWN,
		DAMAGED,
		ATTACK,
		RUN_ATTACK,
		MAX
	};

	//コンストラクタ
	PlayerFront(void);

	//デストラクタ
	~PlayerFront(void);

	//初期化処理(最初の1回のみ実行)
	void SystemInit(void);

	//ゲーム起動・再開時に必ず呼び出す処理
	void GameInit(void);

	//更新処理
	void Update(void);

	//描画処理
	void Draw(void);

	//解放処理(最後の1回のみ使用)
	void Release(void);

	//プレイヤーのHPの取得
	int GetHp(void) { return hp; }

	//プレイヤーの生存状態の取得
	bool GetAlive(void) { return aliveFlg; }

	//プレイヤーにダメージを与える
	void SetDamage(int dp);

	//プレイヤーの座標を取得
	Vector2F GetFrontPos(void) { return pos_; }

	Vector2F GetFrontAttackPos(void) { return apos_; }

	void SetPlayerPos(Vector2 mPos) { pos_ = mPos; }


	//攻撃中判定
	bool GetAttackFlg(void) { return isAttack_; }


private:

	int Runimages_[RUN_ALL_NUM];
	int Idleimages_[IDLE_ALL_NUM];
	int Damageimages_[DAMAGE_ALL_NUM];
	int Attackimages_[ATTACK_ALL_NUM];
	int RunAttackimages_[ATTACK_ALL_NUM];
	int JumpUpimages_[JUMP_ALL_NUM];
	int JumpDownimages_[JUMP_ALL_NUM];

	//座標
	Vector2F pos_;

	//攻撃座標
	Vector2F apos_;

	//アニメーション状態
	ANIM_STATE animState_;

	// プレイヤーの向き
	AsoUtility::DIRECTION dir_;


	//アニメーションカウンタ
	float stepAnim_;

	//攻撃アニメーションのカウンタ
	float attackAnim_;

	// 移動速度
	float moveSpeed_;

	//ジャンプ力
	float jumpPow_;

	//ジャンプ中判定
	bool isJump_;

	//ジャンプ中の入力判定
	bool isPutJumpKey_;

	//攻撃中判定
	bool isAttack_;

	//ダッシュ攻撃判定
	bool isDashAttack_;

	//現在の高度
	float nowJumplength_;

	//現在の最高高度
	float maxJumplength_;

	//ジャンプキーの入力カウント
	int cntJumpInput_;

	//プレイヤーのHP
	int hp;

	//生存フラグ
	bool aliveFlg;

	//ジャンプカウンタ
	int JumpCnt_;



	//画像の読み込み
	void LoadImages(void);

	//プレイヤーの向きと描画
	void DrawPlayer(int handleId);

	// プレイヤーの移動操作
	void ProcessMove(void);

	// 加速(スピードを加える)
	void Accele(float speed);

	// 減速(ディセラレイト)
	void Decelerate(float speed);

	// 移動(実際の座標移動)
	void Move(void);

	//重力をかける
	void AddGravity(void);

	//プレイヤーのジャンプ操作
	void ProcessJump(void);

	//ジャンプ
	void Jump(void);

	//ジャンプ力の設定
	void SetJumpPow(float pow);

	//攻撃操作
	void ProcessAttack(void);

	//攻撃
	void Attack(void);

};

