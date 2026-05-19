#include <DxLib.h>
#include <string>
#include "PlayerFront.h"
#include "Src/Application.h"
#include "Src/AsoUtility.h"
#include "Src/Manager/InputManager.h"

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
	animState_ = ANIM_STATE::RUN;

	//アニメーションカウンタ
	stepAnim_ = 0;

	//初期座標
	pos_ = { 300.0f,380.0f };

	//プレイヤーの向き
	dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;

	//移動速度の初期化
	moveSpeed_ = 0.0f;

	//ジャンプ力
	jumpPow_ = 0.0f;
	isJump_ = true;

	//ジャンプキーのフレームの初期化
	cntJumpInput_ = INPUT_JUMP_FRAME;
}

//ゲーム起動・再開時に必ず呼び出す処理
void PlayerFront::GameInit(void)
{

}

//更新処理
void PlayerFront::Update(void)
{
	//モーションの初期化を行う
	animState_ = ANIM_STATE::IDLE;

	//プレイヤーの移動操作
	ProcessMove();

	//移動(実際の座標移動)
	Move();

	//減速
	Decelerate(MOVE_DEC);


	//プレイヤーのジャンプ操作
	ProcessJump();

	//常に重力をかける
	//(ジャンプ中でなくても落下する)
	AddGravity();

	//ジャンプ
	Jump();
}

//描画処理
void PlayerFront::Draw(void)
{
	if (isJump_)
	{
		animState_ = ANIM_STATE::JUMP;
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
		//case ANIM_STATE::JUMP:
		//	DrawPlayer(images_[animState]);
		//break;
		case ANIM_STATE::RUN:
		{
			stepAnim_ += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % RUN_ALL_NUM;
			DrawPlayer(Runimages_[animIdx]);
		}
		break;
		case ANIM_STATE::DAMAGED:
		{
			stepAnim_ += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % DAMAGE_ALL_NUM;
			DrawPlayer(Damageimages_[animIdx]);
			break;
		}
		case ANIM_STATE::ATTACK:
		{
			stepAnim_ += ANIM_SPEED;
			int animIdx = AsoUtility::Round(stepAnim_) % ATTACK_ALL_NUM;
			DrawPlayer(Attackimages_[animIdx]);
			break;
		}
		case ANIM_STATE::RUN_ATTACK:
		{
			stepAnim_ += ANIM_SPEED;
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
}

void PlayerFront::LoadImages(void)
{
	for (int i = 0; i < IDLE_ALL_NUM; i++)   Idleimages_[i] = -1;
	for (int i = 0; i < RUN_ALL_NUM; i++)    Runimages_[i] = -1;
	for (int i = 0; i < ATTACK_ALL_NUM; i++) Attackimages_[i] = -1;
	for (int i = 0; i < ATTACK_ALL_NUM; i++) RunAttackimages_[i] = -1;
	for (int i = 0; i < DAMAGE_ALL_NUM; i++) Damageimages_[i] = -1;

	int anim = 0;

	//待機
	LoadDivGraph(
		("Image/Knight/spr_knight_idle.png"),
		IDLE_ALL_NUM,
		IDLE_ALL_NUM, 1,
		SIZE_X, SIZE_Y,
		Idleimages_,
		false
	);

	// ジャンプ
	//anim = static_cast<int>(ANIM_STATE::JUMP);
	//images_[anim][atkNone][0] = LoadGraph((basePath + "Jump.png").c_str());
	//images_[anim][atkShot][0] = LoadGraph((basePath + "JumpShot.png").c_str());

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
		SIZE_X, SIZE_Y,
		RunAttackimages_,
		false
	);
}

	//プレイヤーの向きと描画
	void PlayerFront::DrawPlayer(int handleId)
	{
		// 座標変換
		Vector2 pos = pos_.ToVector2();

		//プレイヤーの向き
		bool isLeftDir = true;
		if (dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT)
		{
			isLeftDir = false;
		}

		//描画(座標、拡大率、回転、ハンドルID、透過フラグ、横反転、縦反転)
		DrawRotaGraph(
			pos.x, pos.y,
			1.0, 0.0, handleId, true,
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

	//重力をかける
	void PlayerFront::AddGravity(void)
	{
		//現在のジャンプ力に重力を加える
		float pow = jumpPow_ + GRAVITY;
		SetJumpPow(pow);
	}

	//プレイヤーのジャンプ操作
	void PlayerFront::ProcessJump(void)
	{
		InputManager& inputIns = InputManager::GetInstance();

		if ((inputIns.IsNew(KEY_INPUT_M) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
 			&&cntJumpInput_<INPUT_JUMP_FRAME)
		{
			cntJumpInput_ += 1;

			float pow =
				jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));
			SetJumpPow(pow);

			isJump_ = true;
		}

		if (inputIns.IsTrgUp(KEY_INPUT_SPACE) || inputIns.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
		{
			//ジャンプの入力判定を強制的に終了させる
			cntJumpInput_ = INPUT_JUMP_FRAME;
		}
	}

	//ジャンプ
	void PlayerFront::Jump(void)
	{
		pos_.y += jumpPow_;

		//仮の接地(衝突)判定
		if (pos_.y > 380)
		{
			pos_.y = 900;

			//地面についたのでジャンプをリセットする
			isJump_ = false;
			SetJumpPow(0.0f);
		}
	}

	//ジャンプ力の設定
	void PlayerFront::SetJumpPow(float pow)
	{
		//ジャンプ力を設定
		jumpPow_ = pow;

		//重力がかかりすぎるのを防ぐ
		if (jumpPow_ > MAX_JUMP_POW) {
			jumpPow_ = MAX_JUMP_POW;
		}
	}

	//攻撃操作
	void PlayerFront::ProcessAttack(void)
	{
		InputManager& inputIns = InputManager::GetInstance();

		if ((inputIns.IsNew(KEY_INPUT_F) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT)))
		{

		}
	}



