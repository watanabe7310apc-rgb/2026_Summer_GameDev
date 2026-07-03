#include <DxLib.h>
#include "GameScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"
#include "EnemyBase.h"
#include "EnemyDragon.h"
#include "EnemyGoast.h"
#include "Boar.h"
#include "Src/SceneManager.h"
#include "MenuScene.h"

//コンストラクタ
GameScene::GameScene(void)
{

}

//デストラクタ
GameScene::~GameScene(void)
{

}

//初期化処理(最初の1回のみ実行)
void GameScene::SystemInit()
{

	front_ = new PlayerFront();
	front_->SystemInit();
	player2_ = new Player2();

	img_ = LoadGraph("Image/ゲーム背景(城壁).jpg");
	imgtower = LoadGraph("Image/Tower.png");
	SE_BaseDamage_ = LoadSoundMem("Image/Sound/BaseDamage.mp3");
	scopeImage = LoadGraph("Image/Archer/Scope.png");

	BaseCounter = BASE_HP_MAX;

	spoanCounter_ = 0;

	clearCounter = 0;

	Damage_ = false;

	Clear_ = false;

	SpoanMax_ = Application::Level_ * 10;

	Wave_ = Application::Level_;

	SetMouseDispFlag(FALSE);

}

//ゲーム起動・再開時に必ず呼び出す処理
void GameScene::GameInit(void)
{

}

//更新処理
void GameScene::Update(void)
{

	front_->Update();
	player2_->Update();

	//ヒットスロー
	if (slowCounter > 0)
	{
		slowCounter--;
	}

		if (spoanCounter_ < SpoanMax_) {
			//エンカウンター
			enCounter++;
			if (enCounter > ENCOUNT) {

				spoanCounter_++;

				//敵の生成
				EnemyBase* e = nullptr;

				//ランダムに種別を決める
				int rr = GetRand(static_cast<int>(EnemyBase::E_ENEMY_ID::E_TYPE_MAX) - 1);
				EnemyBase::E_ENEMY_ID type = static_cast<EnemyBase::E_ENEMY_ID>(rr);

				//種別に対応した派生クラスのインスタンスを生成
				switch (type) {
				case EnemyBase::E_ENEMY_ID::E_TYPE_DRAGON:
					e = new EnemyDragon();
					break;
				case EnemyBase::E_ENEMY_ID::E_TYPE_GOAST:
					e = new EnemyGoast();
					break;
				case EnemyBase::E_ENEMY_ID::E_TYPE_BOAR:
					e = new Boar();
					break;
				}

				if (e != nullptr) {
					e->enemyType = type;
					e->SystemInit(this);
					e->GameInit();
					//可変長配列に要素を追加する
					enemys.push_back(e);
					enCounter = 0;           //エンカウンターをリセット
				}
			}
		}
		size_t size = enemys.size();               //敵のテーブルの要素数を取得
		for (auto e : enemys) {
			e->Update();
		}
		if (!front_->GetAttackFlg()) {
			for (auto e : enemys) {
				e->hitThisAttack_ = false;
			}
		}


		//衝突判定
		CollisionCheck();
		if (front_->GetAlive() && BaseCounter > 0&&clearCounter< SpoanMax_) {
			//死亡した敵データを消去する
			size_t size = enemys.size();   //敵のテーブルの要素数を取得
			std::vector<EnemyBase*>::iterator eitr;
			for (int ii = (int)size; ii > 0; ii--) {
				eitr = enemys.begin() + (ii - 1);
				if (!(*eitr)->GetAlive()) {
					(*eitr)->Release();
					delete(*eitr);
					enemys.erase(eitr);
					clearCounter++;
				}
			}
		}
		else
		{
			EraseEnemys();

			if (!front_->GetAlive() || BaseCounter <= 0)
			{
				SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAMEOVER);
			}
			else
			{
				SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_CLEAR);
			}
		
		}


}


//描画処理
void GameScene::Draw(void)
{
	DrawGraph(0,0, img_, false);
	//振動
	if (slowCounter > 0)
	{
		//描画先スクリーンを再設定
		SetDrawScreen(DX_SCREEN_BACK);
		//0or1
		int shake = (slowCounter / 5) % 2;
		//0or2
		shake *= 2;
		//-1or1
		shake -= 1;
		//-5or5
		shake *= 5;


		DrawGraph(shake, shake, tempScreen, true);

		//slowCounterが減るほど薄くなる
		int alpha = 200 * slowCounter / SLOW_DISP_TIME;
		if (alpha > 200)alpha = 255;
		if (alpha < 0)alpha = 0;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y,
			GetColor(200, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	player2_->Draw();

	DrawGraph(Application::SCREEN_SIZE_X / 2- 160 , Application::SCREEN_SIZE_Y - 600, imgtower, true);
	DrawBox(Application::SCREEN_SIZE_X / 2 - 160, Application::SCREEN_SIZE_Y - 600, (Application::SCREEN_SIZE_X / 2 + 160), (Application::SCREEN_SIZE_Y + 225), GetColor(255, 255, 255), false);

	front_->Draw();

	for (auto e:enemys) {
		e->Draw();
	}
	int php = front_->GetHp();

	SetFontSize(25);

	DrawBox(250, 10, 250+(php*3), 10+30, GetColor(0, 255, 0), true);

	DrawFormatString(32, 7, GetColor(0, 0, 0), "プレイヤーHP : ");

	SetFontSize(64);

	DrawFormatString(Application::SCREEN_SIZE_X/2-250, 10, GetColor(0, 0, 0), "防衛地点 %d/%d", BaseCounter,BASE_HP_MAX);
	DrawFormatString(Application::SCREEN_SIZE_X/2-80, 350, GetColor(200, 0, 0), "守れ!!\n ↓");

	SetFontSize(32);

	DrawFormatString(32, 47, GetColor(0, 0, 0), "Enemy :  %d/%d", clearCounter,SpoanMax_);

	SetFontSize(25);

	//マウス標準フレーム
	int mx, my;
	GetMousePoint(&mx, &my);

	DrawRotaGraph(
		mx,
		my,
		0.3,
		0.0,
		scopeImage,
		TRUE
	);
}

//解放処理(最後の1回のみ使用)
void GameScene::Release(void)
{
	DeleteGraph (img_);

	front_->Release();
	delete front_;

	player2_->Release();
	delete player2_;
	player2_ = nullptr;

	EraseEnemys();

	DeleteSoundMem(SE_BaseDamage_);

	DeleteGraph(scopeImage);

}

//当たり判定処理
void GameScene::CollisionCheck(void)
{
	Vector2F Pos;

	//プレイヤーの情報
	//プレイヤーの座標を取得
	Vector2 pPos = front_->GetFrontPos(); // 左上

	//前衛のサイズ
	Vector2 pSize = { PlayerFront::SIZE_X,PlayerFront::SIZE_Y };

	//プレイヤーの攻撃範囲
	Vector2F pos = front_->GetFrontPos();
	Vector2 aPos = AsoUtility::Round(front_->GetFrontAttackPos());
	Vector2 aSize = { PlayerFront::ATTACK_RANGE_X,PlayerFront::ATTACK_RANGE_Y };

	//プレイヤーの突きの攻撃範囲
	Vector2 sPos = AsoUtility::Round(front_->GetFrontAttackPos());
	Vector2 sSize = { PlayerFront::ATTACK_RANGE_X*2,PlayerFront::ATTACK_RANGE_Y };

	//防衛地点の情報
	Vector2 bPos = AsoUtility::Round({ Application::SCREEN_SIZE_X/2, Application::SCREEN_SIZE_Y - 380 });
	Vector2 bSize = { 320, 480 };


	//敵の数だけチェックを行う
	size_t size = enemys.size();
	for (int ii = 0; ii < size; ii++) {
		Pos = enemys[ii]->GetEnemyPos();
		if (!enemys[ii]->GetAlive())continue;

		Vector2 ePos = AsoUtility::Round(Pos);
		Vector2 eSize = enemys[ii]->GetEnemySize();

		//敵とプレイヤーの衝突判定
		if (CollisionChackRectCenter(pPos, pSize, ePos, eSize)) {
			//プレイヤーにダメージを与える
			front_->SetDamage(10); 

			front_->AddKnockBack(15.0f,ePos.x);
		}
		if (!front_->GetAlive()) {
			break;
		}

		//敵とプレイヤーの攻撃の衝突判定
		if (front_->GetAttackFlg()) {
			//攻撃している
			if (CollisionChackRectCenter(aPos, aSize, ePos, eSize) && !enemys[ii]->hitThisAttack_) {
				enemys[ii]->SetDamage(7);   //敵にダメージを与える

				//攻撃の種類ごとにノックバック距離を変える
				enemys[ii]->AddKnockBack(front_->GetKnockBackPower());

				enemys[ii]->hitThisAttack_ = true;
				}
		}

		//敵とプレイヤーの突き攻撃の衝突判定
		if (front_->GetStrikeFlg()&&!front_->GetAttackHit()) {
			//攻撃している
			if (CollisionChackRectCenter(sPos, sSize, ePos, eSize)) {
				enemys[ii]->SetDamage(3);   //敵にダメージを与える

				//敵ごとにノックバック距離を変える
				enemys[ii]->AddKnockBack(front_->GetKnockBackPower());

				front_->SetAttackHit(true);
				}
		}

		//敵と防衛地点の当たり判定
		if (CollisionChackRectCenter(bPos, bSize, ePos, eSize)) {
			BaseCounter--;
			enemys[ii]->SetDamage(10);   //敵にダメージを与える
			slowCounter = SLOW_DISP_TIME;
			PlaySoundMem(SE_BaseDamage_, DX_PLAYTYPE_BACK,true);

		}

		if (!enemys[ii]->GetAlive())continue;
	}

	Arrow* arrows = player2_->GetArrow();

	for (int i = 0; i < Player2::ARROW_MAX; i++)
	{
		if (!arrows[i].isAlive)
			continue;

		Vector2 aPos = arrows[i].GetPos();

		for (auto e : enemys)
		{
			if (!e->GetAlive())
				continue;

			Vector2 ePos = AsoUtility::Round(e->GetEnemyPos());
			Vector2 eSize = e->GetEnemySize();

			// 当たり判定
			if (CollisionChackRectCenter(
				aPos,
				{ 32,32 },      // 矢の当たり判定サイズ
				ePos,
				eSize))
			{
				e->SetDamage(3);      // ダメージ
				arrows[i].Destroy();  // 矢を消す
				break;
			}
		}
	}
}

//中心座標から衝突安定を行う
bool GameScene::CollisionChackRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2)
{
	//1つ目の矩形の座標を求める
	Vector2 stPos1 = cPos1;
	Vector2 edPos1 = cPos1;

	//中心座標から左下と右下の座標を求める
	stPos1.x -= (size1.x / 2);
	stPos1.y -= (size1.y / 2);
	edPos1.x += (size1.x / 2);
	edPos1.y += (size1.y / 2);

	//2つ目の矩形の座標を求める
	Vector2 stPos2 = cPos2;
	Vector2 edPos2 = cPos2;

	//中心座標から左下と右下の座標を求める
	stPos2.x -= (size2.x / 2);
	stPos2.y -= (size2.y / 2);
	edPos2.x += (size2.x / 2);
	edPos2.y += (size2.y / 2);

	//矩形同士の衝突判定
	if (stPos1.x > edPos2.x ||
		edPos1.x<stPos2.x ||
		stPos1.y>edPos2.y ||
		edPos1.y < stPos2.y)
	{
		Damage_ = true;
		return false;
	}
	Damage_ = false;
	return true;
}

/*
*-------------------------------------------------------
* 敵のデータテーブルを空にする
* Input:
*    無し
* OutPut:
*     無し
*-------------------------------------------------------
*/
void GameScene::EraseEnemys(void)
{
	size_t size = enemys.size();
	for (int ii = (int)size; ii > 0; ii--) {
		enemys[ii - 1]->Release();
		//インスタンスの開放
		delete enemys[ii - 1];
	}
	enemys.clear();   //可変長配列を空にする(サイズを0にする)
}
