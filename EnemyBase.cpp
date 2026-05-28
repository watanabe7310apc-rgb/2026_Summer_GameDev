#include <DxLib.h>
#include "EnemyBase.h"

	//コンストラクタ
	EnemyBase::EnemyBase(void)
	{

	}

	//デストラクタ
	EnemyBase::~EnemyBase(void)
	{

	}

	//初期化処理(最初の1回のみ実行)
	void EnemyBase::SystemInit(GameScene*gs)
	{
		//敵キャラ個別のパラメータ設定処理
		SetEnemyParam();

		//敵の画像の読み込み
		LoadImages();

		//アニメーションカウンタの初期化
		stepAnim = 0;

		//生存フラグの初期化
		aliveFlg = true;
	}

	//ゲーム起動・再開時に必ず呼び出す処理
	void EnemyBase::GameInit(void)
	{

	}

	//更新処理
	void EnemyBase::Update(void)
	{

		if (stepAnim > 10 * 10)stepAnim = 0;

		//座標に移動量を加える
		pos.x += speed;

	}

	//描画処理
	void EnemyBase::Draw(void)
	{


		switch (enemyType)
		{
		case E_ENEMY_ID::E_TYPE_DRAGON:
			stepAnim += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim) % 4;
			DrawGraph(pos.x,pos.y,imgDragon_[animIdx],true);
			break;
		}
	}

	//解放処理(最後の1回のみ使用)
	void EnemyBase::Release(void)
	{
		for (int i = 0; i < 4; i++)
			if (imgDragon_[i] != -1) DeleteGraph(imgDragon_[i]);

	}

	//画像の読み込み
	void EnemyBase::LoadImages(void)
	{
		for (int i = 0; i < 4; i++) imgDragon_[i] = -1;

		//ドラゴン
		LoadDivGraph(
			("Image/Enemy/enemy6.png"),
			4, 4, 1, size.x, size.y, imgDragon_,
			false
		);
	}

	/*
	*----------------------------------------------------
	* 敵にダメージを与える
	* Input:
	*   int dp : 与えるダメージ
	* Output:
	*    無し
	*----------------------------------------------------
	*/

	void EnemyBase::SetDamage(int dp)
	{
		hp -= dp;
		if (hp <= 0) {
			hp = 0;
			aliveFlg = false;
		}
	}

	/*
	*----------------------------------------------------
	* 敵キャラの足元座標を取得する
	* Input:
	*   無し
	* Output:
	*    float : 足元のY座標
	*----------------------------------------------------
	*/
	int EnemyBase::GetEnemyFootPosY(void)
	{
		return static_cast<int>(pos.y + size.y / 2);
	}
