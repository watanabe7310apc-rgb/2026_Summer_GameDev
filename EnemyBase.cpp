#include <DxLib.h>
#include "GameScene.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase(void) {

}

EnemyBase::~EnemyBase(void) {

}

void EnemyBase::Init(GameScene* scene)
{
	// ゲームシーンの機能を使えるように
	gameScene_ = scene;

	// 敵キャラ個別のパラメータ設定
	SetParam();

	// 画像の分割読み込み
	std::string path = "Image/Enemy/";
	path += imgFileName;
	LoadDivGraph(
		path.c_str(),
		16, 4, 4,
		size_.x, size_.y,
		&imgs_[0][0]
	);

	// 初期位置
	pos_.x = 250;
	pos_.y = 250;

	// 向き
	dir_ = AsoUtility::DIR::DOWN;

	// アニメーションカウンタ
	cntAnim_ = 0;

	// 生存判定
	isAlive_ = true;
}

void EnemyBase::Update(void)
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
	if (size < speed_)
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
		pos_.x += direction.x * speed_;
		pos_.y += direction.y * speed_;

		// 向きを変える(移動量が大きい向きを優先)
		SetAnimDir(direction);
	}
	// アニメーションカウンタの進行
	cntAnim_++;
}

void EnemyBase::Draw(void)
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
		pos.x - size_.x / 2 - cameraPos.x,
		pos.y - size_.y / 2 - cameraPos.y,
		imgs_[static_cast<int>(dir_)][animNum], true);
}

void EnemyBase::Release(void)
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

Vector2F EnemyBase::GetPos(void)
{
	return pos_;
}

void EnemyBase::SetPos(Vector2F pos)
{
	pos_ = pos;
}

Vector2 EnemyBase::GetSize(void)
{
	return size_;
}

bool EnemyBase::IsAlive(void)
{
	return isAlive_;
}

void EnemyBase::SetAlive(bool alive)
{
	isAlive_ = alive;
}

void EnemyBase::Damage(int damage)
{
	hp_ -= damage;
	if (hp_ <= 0)
	{
		hp_ = 0;
		isAlive_ = false;
	}
}

int EnemyBase::GetFootPosY(void)
{
	return static_cast<int>(pos_.y + size_.y / 2);
}

void EnemyBase::SetAnimDir(Vector2F direction)
{

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