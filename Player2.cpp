#include <DxLib.h>
#include "Player2.h"
Player2::Player2() 
{ 
	// 座標 
	pos.x = 945; 
	
	pos.y = 470; 

	LoadDivGraph(
		"Image/Archer/Archer_attack.png",
		11,        // 全11枚
		11, 1,     // 横11枚、縦1枚
		64, 47,    // ←1コマのサイズに合わせる
		image
	);

	isRight = true;

	oldMouse = false; 

	shotCoolTime = 0; 

	shotSE = LoadSoundMem("Image/Sound/Arrow.mp3"); 

	animFrame = 0;

	animCounter = 0;

	isAttack = false;
} 

void Player2::Update() 
{ 
	// 移動しない 
	// マウスの方向を向く 
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY); 
	
	if (mouseX < pos.x) 
	{ 
		isRight = false;
	} 
	else 
	{
		isRight = true; 
	} 

	bool nowMouse = (GetMouseInput() & MOUSE_INPUT_LEFT); 
	
	//発射間隔 
	if (shotCoolTime > 0) 
	{ 
		shotCoolTime--; 
	} 
	// クリックした瞬間だけ発射 
	if (nowMouse && !oldMouse && shotCoolTime == 0) 
	{
		Vector2 target(mouseX, mouseY); 
		
		for (int i = 0; i < ARROW_MAX; i++) 
		
		{
			if (!arrow[i].isAlive) 
			{ 
				arrow[i].Shot(pos, target);

				PlaySoundMem(shotSE, DX_PLAYTYPE_BACK);
			
				isAttack = true;
				animFrame = 7;

				shotCoolTime = SHOT_INTERVAL; break; 
			
			} 
		} 
	} 
	// マウス状態を保存 
	oldMouse = nowMouse;
	
	animCounter++;

	if (animCounter >= 4)
	{
		animCounter = 0;

		if (isAttack)
		{
			// 攻撃アニメーション
			animFrame++;

			if (animFrame > 10)
			{
				isAttack = false;
				animFrame = 0;    // 待機アニメーションへ戻る
			}
		}
		else
		{
			// 待機アニメーション
			if (animFrame < 7)
			{
				animFrame++;
			}
			// 7フレームで停止
		}
	}

	// 全ての矢を更新 
	for (int i = 0; i < ARROW_MAX; i++)
	{
		arrow[i].Update();
	} 
} 

void Player2::Draw() 
{
	double scale = 2.0; // 好きな倍率 

	if (isRight) 
	{
		DrawRotaGraph
		( 
			pos.x,
			pos.y, 
			scale, 0.0,
			image[animFrame],
			TRUE, 
			FALSE 
		); 
	}
	else 
	{
		DrawRotaGraph
		(
			pos.x,
			pos.y,
			scale,
			0.0, 
			image[animFrame],
			TRUE, 
			TRUE 
		); 
	} 
	for (int i = 0; i < ARROW_MAX; i++)
	{
		arrow[i].Draw(); 
	}
} 

void Player2::Release() 
{ 
	for (int i = 0; i < 11; i++)
	{
		DeleteGraph(image[i]);
	}
	
	DeleteSoundMem(shotSE); 
}