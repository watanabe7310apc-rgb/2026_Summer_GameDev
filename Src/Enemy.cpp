#include <DxLib.h>
#include "Vetor2F.h"
#include "GameScene.h"
#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::Init(GameScene* scene)
{
	// ゲームシーンの機能を使えるように
	gameScene_ = scene;

	// 画像の分割読み込み
	LoadDivGraph(
		"Image/Enemy/Enemy4.png",
		16, 4, 4,
		SIZE_X, SIZE_Y,
		&imgs_[0][0]
	);

	// 初期位置
	pos_.x = 250;
	pos_.y = 250;

	// 初期の移動速度
	speed_ = SPEED_DEFAULT;

	// 向き
	dir_ = AsoUtility::DIR::DOWN;

	// アニメーション速度
	speedAnim_ = ANIM_SPEED_DEFAULT;

	// アニメーションカウンタ
	cntAnim_ = 0;

	// 生存判定
	isAlive_ = true;
}

void Enemy::Update(void)
{
	// プレイヤーの位置
	Vector2 pPos = gameScene_->GetPlayerPos();

	// ベクトル(相手 - 自分)
	Vector2F vec = Vector2F(
		static_cast<float>(pPos.x - pos_.x),
		static_cast<float>(pPos.y - pos_.y)
	);

	// ベクトルの大きさ(長さ)
	float size = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (size < SPEED_DEFAULT)
	{
		// ブルブルしないように、
		// 移動量よりも、位置差が短い場合は移動しない
	}
	else
	{

		// 方向(単位ベクトル)
		Vector2F direction;

		direction.x = vec.x / size;
		direction.y = vec.y / size;

		// 座標に移動量を加える
		pos_.x += direction.x * SPEED_DEFAULT;
		pos_.y += direction.y * SPEED_DEFAULT;

		// 向きを変える(移動量が大きい向きを優先)
		if (abs(direction.x) < abs(direction.y))
		{
			// 上下
			if (direction.y > 0.0f)
			{
				dir_ = AsoUtility::DIR::DOWN;
			}
			else
			{
				dir_ = AsoUtility::DIR::UP;
			}
		}
		else
		{
			// 左右
			if (direction.x > 0.0f)
			{
				dir_ = AsoUtility::DIR::RIGHT;
			}
			else
			{
				dir_ = AsoUtility::DIR::LEFT;
			}
		}
	}
	// アニメーションカウンタの進行
	cntAnim_++;
}

void Enemy::Draw(void)
{
	if (!isAlive_)
	{
		// 生存していなかったら描画しない
		return;
	}

	// アニメーションのチップ番号を作る(0～3)
	int animNum = static_cast<int>(
		(static_cast<float>(cntAnim_) * speedAnim_)) % NUM_ANIM;

	Vector2 cameraPos = gameScene_->GetCameraPos();

	// 敵の表示
	Vector2 pos = AsoUtility::Round(pos_);
	DrawGraph(
		pos.x - SIZE_X / 2 - cameraPos.x,
		pos.y - SIZE_Y / 2 - cameraPos.y,
		imgs_[static_cast<int>(dir_)][animNum], true);
}

void Enemy::Release(void)
{
	// 読み込んだ画像の解放
	int max = static_cast<int>(AsoUtility::DIR::MAX);
	for (int y = 0; y < max; y++)
	{
		for (int x = 0; x < NUM_ANIM; x++)
		{
			DeleteGraph(imgs_[y][x]);
		}
	}
}

Vector2F Enemy::GetPos(void)
{
	return pos_;
}

void Enemy::SetPos(Vector2F pos)
{
	pos_ = pos;
}

bool Enemy::IsAlive(void)
{
	return isAlive_;
}

void Enemy::SetAlive(bool alive)
{
	isAlive_ = alive;
}