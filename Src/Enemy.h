//#pragma once
//#include "Vector2.h"
//#include "AsoUtility.h"
//
//class GameScene;
//
//class Enemy
//{
//
//public:
//
//	static const int SIZE_X = 64;	// 横サイズ
//	static const int SIZE_Y = 64;	// 縦サイズ
//
//	// 方向ごとのアニメーション数
//	static constexpr int NUM_ANIM = 2;
//
//	// 移動速度
//	static constexpr float SPEED_DEFAULT = 2.0f;
//
//	// アニメーション速度
//	static constexpr float ANIM_SPEED_DEFAULT = 0.1f;
//
//	// コンストラクタ
//	Enemy(void);
//
//	// デストラクタ
//	~Enemy(void);
//
//	// 初期処理(最初の１回のみ実行)
//	void Init(GameScene* scene);
//
//	// 更新処理(毎フレーム実行)
//	void Update(void);
//
//	// 描画処理(毎フレーム実行)
//	void Draw(void);
//
//	// 解放処理(最後の１回のみ実行)
//	void Release(void);
//
//	// 座標の取得
//	Vector2 GetPos(void);
//
//	// 座標の設定
//	void SetPos(Vector2F pos);
//
//	// 生存判定
//	bool IsAlive(void);
//
//	// 生存判定
//	void SetAlive(bool alive);
//
//private:
//
//	// ゲームシーンのポインタ変数
//	GameScene* gameScene_;
//
//	// 画像
//	int imgs_[static_cast<int>(AsoUtility::DIRECTION::E_DIR_MAX)][NUM_ANIM];
//
//	// 表示座標
//	Vector2 pos_;
//
//	// 移動速度
//	float speed_;
//
//	// 移動方向
//	AsoUtility::DIRECTION dir_;
//
//	// アニメーション
//	int cntAnim_;
//
//	// アニメーション速度
//	float speedAnim_;
//
//	// 生存判定
//	bool isAlive_;
//};