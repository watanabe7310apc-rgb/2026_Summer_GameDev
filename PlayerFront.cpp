#include <DxLib.h>
#include <string>
#include "PlayerFront.h"
#include "Src/Application.h"
#include "Src/AsoUtility.h"
#include "Src/Manager/InputManager.h"
#include "GameScene.h"

//コンストラクタ
PlayerFront::PlayerFront(void)
{

}

//デストラクタ
PlayerFront::~PlayerFront(void)
{

}

//初期化処理(最初の1回のみ実行)
void PlayerFront::SystemInit(void)
{
	LoadImages();

	//アニメーション状態
	animState_ = ANIM_STATE::IDLE;

	//アニメーションカウンタ
	stepAnim_ = 0;

	//初期座標
	pos_ = { 800.0f,900.0f };

	apos_ = { 0.0f,0.0f };

	//プレイヤーの向き
	dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;

	//移動速度の初期化
	moveSpeed_ = 0.0f;

	//ジャンプ力
	isAttack_ = false;
	isStrikeAttack_ = false;
	AtkHit_ = true;


	//攻撃判定の初期化
	attackAnim_ = 0;

	//生存状態の初期化
	aliveFlg = true;

	//HPの初期化
	hp = FRONT_HP;

	//ノックバック速度
	knockBackSpeed_ = 0.0f;

	//ノックバックのデフォルト値
	knockBackPower_ = 20.0f;


	SE_Slash_ = LoadSoundMem("Image/Sound/Slash.mp3");
	SE_Strike_ = LoadSoundMem("Image/Sound/Strike.mp3");
	SE_Damage_ = LoadSoundMem("Image/Sound/Damage.mp3");

}


//ゲーム起動・再開時に必ず呼び出す処理
void PlayerFront::GameInit(void)
{
}

//更新処理
void PlayerFront::Update(void)
{
	if (fabs(knockBackSpeed_) > 0.01f)
	{
		pos_.x += knockBackSpeed_;
		knockBackSpeed_ *= KNOCKBACK_DEC;

		//止まったら終了
		if (fabs(knockBackSpeed_) < 0.1f)
		{
			knockBackSpeed_ = 0.0f;
		}
		return;
	}

	//何もしていない時だけIDLEモーション実行
	if (!isAttack_ &&!isStrikeAttack_&& moveSpeed_ == 0)
	{
		animState_ = ANIM_STATE::IDLE;
	}

	if (!isAttack_&&!isStrikeAttack_)
	{
		//プレイヤーの移動操作
		ProcessMove();

		//移動(実際の座標移動)
		Move();
	}
	//減速
	Decelerate(MOVE_DEC);

	//プレイヤーの攻撃操作
	ProcessAttack();

	//攻撃
	Attack();

	//突き攻撃
	StrikeAttack();

	//プレイヤーの左端のチェック
	if (pos_.x < 0) {
		pos_.x = 0;
	}

	//プレイヤーの右端のチェック
	if (pos_.x >= Application::SCREEN_SIZE_X - SIZE_X) {
		pos_.x = Application::SCREEN_SIZE_X - SIZE_X;
	}


}

//描画処理
void PlayerFront::Draw(void)
{
	
	DrawBox(pos_.x-(SIZE_X/2), pos_.y-(SIZE_Y/2), pos_.x + (SIZE_X/2), pos_.y + (SIZE_Y/2), GetColor(0, 200, 0), false);

	if (isAttack_) {
		DrawBox(apos_.x - (ATTACK_RANGE_X / 2), apos_.y - (ATTACK_RANGE_Y / 2), apos_.x + (ATTACK_RANGE_X / 2), apos_.y + (ATTACK_RANGE_Y / 2), GetColor(200, 0, 0), false);
	}
	else if (isStrikeAttack_) {
		DrawBox(apos_.x - (ATTACK_RANGE_X ), apos_.y - (ATTACK_RANGE_Y / 2), apos_.x + (ATTACK_RANGE_X ), apos_.y + (ATTACK_RANGE_Y / 2), GetColor(200, 0, 0), false);

	}

	switch (animState_)
	{
		case ANIM_STATE::IDLE:
		{
 			stepAnim_ += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % IDLE_ALL_NUM;
			DrawPlayer(Idleimages_[animIdx]);
		}
		break;

		case ANIM_STATE::RUN:
		{
			stepAnim_ += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % RUN_ALL_NUM;
			DrawPlayer(Runimages_[animIdx]);
			break;
		}

		case ANIM_STATE::DAMAGED:
		{
			stepAnim_ += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % DAMAGE_ALL_NUM;
			DrawPlayer(Damageimages_[animIdx]);
			break;
		}
		case ANIM_STATE::ATTACK:
		{
			stepAnim_ += ATTACK_ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % ATTACK_ALL_NUM;
			DrawPlayer(Attackimages_[animIdx]);
			break;
		}
		case ANIM_STATE::RUN_ATTACK:
		{
			stepAnim_ += ATTACK_ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % ATTACK_ALL_NUM;
			DrawPlayer(RunAttackimages_[animIdx]);
			break;
		}

	}

}

//解放処理(最後の1回のみ使用)
void PlayerFront::Release(void)
{
		for (int i = 0; i < IDLE_ALL_NUM; i++)
			if (Idleimages_[i] != -1) DeleteGraph(Idleimages_[i]);

		for (int i = 0; i < RUN_ALL_NUM; i++)
			if (Runimages_[i] != -1) DeleteGraph(Runimages_[i]);

		for (int i = 0; i < ATTACK_ALL_NUM; i++)
			if (Attackimages_[i] != -1) DeleteGraph(Attackimages_[i]);

		for (int i = 0; i < ATTACK_ALL_NUM; i++)
			if (RunAttackimages_[i] != -1) DeleteGraph(RunAttackimages_[i]);

		for (int i = 0; i < DAMAGE_ALL_NUM; i++)
			if (Damageimages_[i] != -1) DeleteGraph(Damageimages_[i]);

		DeleteSoundMem(SE_Damage_);
		DeleteSoundMem(SE_Slash_);
		DeleteSoundMem(SE_Strike_);
}

void PlayerFront::LoadImages(void)
{
	for (int i = 0; i < IDLE_ALL_NUM; i++)   Idleimages_[i] = -1;
	for (int i = 0; i < RUN_ALL_NUM; i++)    Runimages_[i] = -1;
	for (int i = 0; i < ATTACK_ALL_NUM; i++) Attackimages_[i] = -1;
	for (int i = 0; i < ATTACK_ALL_NUM; i++) RunAttackimages_[i] = -1;
	for (int i = 0; i < DAMAGE_ALL_NUM; i++) Damageimages_[i] = -1;


	//待機
	LoadDivGraph(
		("Image/Knight/spr_knight_idle.png"),
		IDLE_ALL_NUM,
		IDLE_ALL_NUM, 1,
		SIZE_X, SIZE_Y,
		Idleimages_,
		false
	);


	//ダメージ
	LoadDivGraph(
		("Image/Knight/spr_knight_hit.png"),
		DAMAGE_ALL_NUM,
		DAMAGE_ALL_NUM, 1,
		SIZE_X, SIZE_Y,
		Damageimages_,
		false
	);

	//走る
	LoadDivGraph(
		("Image/Knight/spr_knight_run.png"),
		RUN_ALL_NUM,
		RUN_ALL_NUM, 1,
		SIZE_X, SIZE_Y,
		Runimages_,
		false
	);

	//攻撃
	LoadDivGraph(
		("Image/Knight/spr_knight_meleeattack.png"),
		ATTACK_ALL_NUM,
		ATTACK_ALL_NUM, 1,
		SIZE_X, SIZE_Y,
		Attackimages_,
		false
	);

	//ダッシュ攻撃
	LoadDivGraph(
		("Image/Knight/spr_knight_rangedattack.png"),
		ATTACK_ALL_NUM,
		ATTACK_ALL_NUM, 1,
		192, SIZE_Y,
		RunAttackimages_,
		false
	);
}

	//プレイヤーの向きと描画
	void PlayerFront::DrawPlayer(int handleId)
	{
			// 座標変換
			Vector2 pos = pos_.ToVector2();

			if (isStrikeAttack_)
			{
				switch (dir_)
				{
				case AsoUtility::DIRECTION::E_DIR_RIGHT:
					pos.x = pos.x * 1.05;
					break;
				case AsoUtility::DIRECTION::E_DIR_LEFT:
					pos.x = pos.x / 1.07;
					break;
				}
			}

		//プレイヤーの向き
		bool isLeftDir = true;
		if (dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT)
		{
			isLeftDir = false;
		}

		//描画(座標、拡大率、回転、ハンドルID、透過フラグ、横反転、縦反転)
		DrawRotaGraph(
			pos.x, pos.y,
			1.5, 0.0, handleId, true,
			isLeftDir
		);
	}

	// プレイヤーの移動操作
	void PlayerFront::ProcessMove(void)
	{
		InputManager& inputIns = InputManager::GetInstance();

		InputManager::JOYPAD_IN_STATE state =
			inputIns.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

		int analogKeyX = state.AKeyLX;

		//左向き
		if (inputIns.IsNew(KEY_INPUT_LEFT) || analogKeyX < 0)
		{
			dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
			animState_ = ANIM_STATE::RUN;
			//加速
			Accele(-MOVE_ACC);
		}
		//右向き
		if (inputIns.IsNew(KEY_INPUT_RIGHT) || analogKeyX > 0)
		{
			dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
			animState_ = ANIM_STATE::RUN;
			//加速
			Accele(MOVE_ACC);
		}
	}

	// 加速(スピードを加える)
	void PlayerFront::Accele(float speed)
	{
		moveSpeed_ += speed;

		//速度制限(右方向)
		if (moveSpeed_ > MAX_MOVE_SPEED) {
			moveSpeed_ = MAX_MOVE_SPEED;
		}
		//速度制限(左方向)
		if (moveSpeed_ < -MAX_MOVE_SPEED) {
			moveSpeed_ = -MAX_MOVE_SPEED;
		}
	}

	// 減速(ディセラレイト)
	void PlayerFront::Decelerate(float speed)
	{
		//右方向の移動を減速させる
		if (moveSpeed_ > 0.0f)
		{
			moveSpeed_ -= speed;
			moveSpeed_ = 0.0f;
		}
		//左方向の移動を減速させる
		if (moveSpeed_ < 0.0f)
		{
			moveSpeed_ += speed;
			moveSpeed_ = 0.0f;
		}
	}

	// 移動(実際の座標移動)
	void PlayerFront::Move(void)
	{
		pos_.x += moveSpeed_;
	}


	//攻撃操作
	void PlayerFront::ProcessAttack(void)
	{
		InputManager& inputIns = InputManager::GetInstance();

		//攻撃中は新しい攻撃を受け付けない
		if (isAttack_||isStrikeAttack_)return;
		if ((inputIns.IsTrgDown(KEY_INPUT_F) || inputIns.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT)))
		{
				isAttack_ = true;
				attackAnim_ = 0;
				stepAnim_ = 0;
				animState_ = ANIM_STATE::ATTACK;
				//ノックバック距離
				SetKnockBackPower(10.0f);
				PlaySoundMem(SE_Slash_, DX_PLAYTYPE_BACK, true);

		}
		if ((inputIns.IsTrgDown(KEY_INPUT_E) || inputIns.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP)))
		{
				isStrikeAttack_ = true;
				AtkHit_ = false;
				attackAnim_ = 0;
				stepAnim_ = 0;
				animState_ = ANIM_STATE::RUN_ATTACK;
				//ノックバック距離
				SetKnockBackPower(15.0f);
				PlaySoundMem(SE_Strike_, DX_PLAYTYPE_BACK,true);
		}
	}

	//攻撃
	void PlayerFront::Attack(void)
	{
		if (!isAttack_) return;


			attackAnim_ += ATTACK_ANIM_SPEED;

			if (dir_ == AsoUtility::DIRECTION::E_DIR_LEFT)
			{
				apos_.x = pos_.x - (SIZE_X / 2);
				apos_.y = pos_.y;
			}
			else if(dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT)
			{
				apos_.x = pos_.x+(SIZE_X/2) ;
				apos_.y = pos_.y;
			}

			if (attackAnim_ >= ATTACK_ALL_NUM)
			{
				isAttack_ = false;
				attackAnim_ = 0;
			}
	}

	//突き攻撃
	void PlayerFront::StrikeAttack(void)
	{
		if (!isStrikeAttack_) return;


			attackAnim_ += ATTACK_ANIM_SPEED;

			if (dir_ == AsoUtility::DIRECTION::E_DIR_LEFT)
			{
				apos_.x = pos_.x - SIZE_X;
				apos_.y = pos_.y;
			}
			else if(dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT)
			{
				apos_.x = pos_.x+SIZE_X ;
				apos_.y = pos_.y;
			}

			if (attackAnim_ >= ATTACK_ALL_NUM)
			{
				isStrikeAttack_ = false;
				attackAnim_ = 0;
			}
	}



	//プレイヤーにダメージを与える
	void PlayerFront::SetDamage(int dp)
	{
		hp -= dp;
		PlaySoundMem(SE_Damage_, DX_PLAYTYPE_BACK, true);

		if (hp <= 0)
		{
			hp = 0;
			aliveFlg = false;
		}
	}

	//ノックバック中
	void PlayerFront::AddKnockBack(float power,float enemyX)
	{
		//敵の向きに応じて方向を決める
		float dir = (enemyX<pos_.x) ? 1.0f : -1.0f;
		//敵ごとに違う値を渡せる
		knockBackSpeed_ = power * dir;

		//ダメージアニメーション
		animState_= ANIM_STATE::DAMAGED;
	}




