
#include <DxLib.h>
#include "EnemyBase.h"
#include "Src/SceneManager.h"
#include "Src/Application.h"

	
	EnemyBase::EnemyBase(void)
	{

	}


	EnemyBase::~EnemyBase(void)
	{

	}

	//
	void EnemyBase::SystemInit(GameScene*gs)
	{
		//敵のパラメータの設定
		SetEnemyParam();

		//敵の画像のロード
		LoadImages();

		//アニメーション
		stepAnim = 0;

		//生存フラグ
		aliveFlg = true;

		//ノックバック速度
		knockBackSpeed_ = 0.0f;

		//ノックバックの減衰率
		knockBackDec_ = 0.85f;


	}

	//繧ｲ繝ｼ繝襍ｷ蜍輔・蜀埼幕譎ゅ↓蠢・★蜻ｼ縺ｳ蜃ｺ縺吝・逅・
	void EnemyBase::GameInit(void)
	{

	}

	//更新
	void EnemyBase::Update(void)
	{

		if (stepAnim > 10 * 10)stepAnim = 0;

		if (fabs(knockBackSpeed_) > 0.01f)
		{
			pos.x -= knockBackSpeed_;
			knockBackSpeed_ *= knockBackDec_;

			//止まったら終了
			if (fabs(knockBackSpeed_) < 0.1f)
			{
				knockBackSpeed_ = 0.0f;
			}
			return;
		}

			switch (enemySpoanPoint)
			{
			case 0:
				//敵が右を向いているとき
				pos.x += speed;
				dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
				break;
			case 1:
				//敵が左を向いているとき
				pos.x -= speed;

				dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
				break;
			}

	}

	//描画
	void EnemyBase::Draw(void)
	{
		DrawBox(pos.x - (size.x / 2), pos.y - (size.y / 2), pos.x + (size.x / 2), pos.y + (size.y / 2), GetColor(200, 0, 0), false);
		DrawBox(pos.x - 50, pos.y - 100, pos.x + (hp * 5), pos.y - 70, GetColor(0, 0, 255), true);

		if (Application::Player_ == 1) {
			switch (enemyType) {
			case E_ENEMY_ID_1::E_TYPE_GOAST_1:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 3;
				DrawEnemy(imgGoast_[animIdx]);
			}
			break;
			case E_ENEMY_ID_1::E_TYPE_BOAR_1:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 6;
				DrawEnemy(imgBoar_[animIdx]);
			}
			break;
			case E_ENEMY_ID_1::E_TYPE_HONE_1:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 3;
				DrawEnemy(imgHone_[animIdx]);
			}
			break;
			}
		}
		else {
			switch (enemyType)
			{
			case E_ENEMY_ID_2::E_TYPE_DRAGON_2:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 4;
				DrawEnemy(imgDragon_[animIdx]);

			}
			break;
			case E_ENEMY_ID_2::E_TYPE_GOAST_2:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 3;
				DrawEnemy(imgGoast_[animIdx]);
			}
			break;
			case E_ENEMY_ID_2::E_TYPE_BOAR_2:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 6;
				DrawEnemy(imgBoar_[animIdx]);
			}
			break;
			case E_ENEMY_ID_2::E_TYPE_BAT_2:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 4;
				DrawEnemy(imgBat_[animIdx]);
			}
			break;
			case E_ENEMY_ID_2::E_TYPE_HONE_2:
			{
				stepAnim += ANIM_SPEED;
				int animIdx = AsoUtility::Round(stepAnim) % 3;
				DrawEnemy(imgHone_[animIdx]);
			}
			break;
			}
		}
	}

	//解放処理
	void EnemyBase::Release(void)
	{
		for (int i = 0; i < 4; i++)
			if (imgDragon_[i] != -1) DeleteGraph(imgDragon_[i]);
		for (int i = 0; i < 3; i++)
			if (imgGoast_[i] != -1) DeleteGraph(imgGoast_[i]);
		for (int i = 0; i < 4; i++)
			if (imgBat_[i] != -1) DeleteGraph(imgBat_[i]);
		for (int i = 0; i < 6; i++)
			if (imgBoar_[i] != -1) DeleteGraph(imgBoar_[i]);
		for (int i = 0; i < 3; i++)
			if (imgHone_[i] != -1) DeleteGraph(imgHone_[i]);

	}

	//敵画像のロード
	void EnemyBase::LoadImages(void)
	{
		for (int i = 0; i < 4; i++) imgDragon_[i] = -1;
		for (int i = 0; i < 3; i++) imgGoast_[i] = -1;
		for (int i = 0; i < 4; i++) imgBat_[i] = -1;
		for (int i = 0; i < 6; i++) imgBoar_[i] = -1;
		for (int i = 0; i < 3; i++) imgHone_[i] = -1;

		//ドラゴン
		LoadDivGraph(
			("Image/Enemy/enemy6.png"),
			4, 4, 1, size.x, size.y, imgDragon_,
			false
		);

		//ゴースト
		LoadDivGraph(
			("Image/Enemy/Enemy 15-3.png"),
			3, 3, 1, size.x, size.y, imgGoast_,
			false
		);

		//イノシシの画像のロード
		LoadDivGraph(
			("Image/Enemy/Boar.png"),
			6, 6, 1, size.x, size.y, imgBoar_,
			false
		);

		//コウモリの画像のロード
		LoadDivGraph(
			("Image/Enemy/Bat.png"),
			4, 4, 1, size.x, size.y, imgBat_,
			false
		);

		//ガイコツの画像のロード
		LoadDivGraph(
			("Image/Enemy/Hone.png"),
			3, 3, 1, size.x, size.y, imgHone_,
			false
		);
	}

	//敵画像の描画
	void EnemyBase::DrawEnemy(int handleId)
	{
		// 座標の変換処理
		Vector2 pos_ = pos.ToVector2();

		//向きに応じて処理を変える
		bool isLeftDir = true;
		if (dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT)
		{
			isLeftDir = false;
		}

		//向きに応じて敵の描画を変える
		DrawRotaGraph(
			pos.x, pos.y,
			1.0, 0.0, handleId, true,
			isLeftDir
		);

	}


	/*
	*----------------------------------------------------
	* ダメージ処理
	* Input:
	*   int dp : ダメージ量
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

	//ノックバック中
	void EnemyBase::AddKnockBack(float power)
	{
		//敵の向きに応じて方向を決める
		float dir = (dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT) ? 1.0f : -1.0f;
		//敵ごとに違う値を渡せる
		knockBackSpeed_ = power * dir;
	}

