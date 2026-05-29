#include <DxLib.h>
#include "GameScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"
#include "EnemyBase.h"
#include "EnemyDragon.h"
#include "EnemyGoast.h"
#include "Src/SceneManager.h"

//コンストラクタ
GameScene::GameScene(void)
{

}

//デストラクタ
GameScene::~GameScene(void)
{

}

//初期化処理(最初の1回のみ実行)
void GameScene::SystemInit(void)
{
	front_ = new PlayerFront();
	front_->SystemInit();

	img_ = LoadGraph("Image/ゲーム背景(城壁).jpg");
	imgtower = LoadGraph("Image/Tower.png");

	BaseCounter = BASE_HP_MAX;

	spoanCounter_ = 0;

	clearCounter = 0;
}

//ゲーム起動・再開時に必ず呼び出す処理
void GameScene::GameInit(void)
{

}

//更新処理
void GameScene::Update(void)
{
	front_->Update();

		if (spoanCounter_ < 30) {
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
		if (front_->GetAlive()) {
			//死亡した敵データを消去する
			size_t size = enemys.size();   //敵のテーブルの要素数を取得
			std::vector<EnemyBase*>::iterator eitr;
			for (int ii = (int)size; ii > 0; ii--) {
				eitr = enemys.begin() + (ii - 1);
				if (!(*eitr)->GetAlive()) {
					(*eitr)->Release();
					delete(*eitr);
					enemys.erase(eitr);
				}
			}
		}
		size_t size = enemys.size();               //敵のテーブルの要素数を取得
		for (auto e : enemys) {
			e->Update();
		}



		//衝突判定
		CollisionCheck();
		if (front_->GetAlive() && BaseCounter > 0&&clearCounter<30) {
			//死亡した敵データを消去する
			size_t size = enemys.size();   //敵のテーブルの要素数を取得
			std::vector<EnemyBase*>::iterator eitr;
			for (int ii = (int)size; ii > 0; ii--) {
				eitr = enemys.begin() + (ii - 1);
				if (!(*eitr)->GetAlive()) {
					(*eitr)->Release();
					delete(*eitr);
					enemys.erase(eitr);
				}
			}
		}
		else  {
			EraseEnemys();
			SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAMEOVER);

		}


}


//描画処理
void GameScene::Draw(void)
{
	DrawGraph(0,0, img_, false);

	DrawGraph(Application::SCREEN_SIZE_X / 2 - 176 , Application::SCREEN_SIZE_Y - 650, imgtower, false);

	front_->Draw();

	for (auto e:enemys) {
		e->Draw();
	}
	int php = front_->GetHp();

	DrawFormatString(32, 0, GetColor(0xff, 0xff, 0xff), "プレイヤーHP : %3d", php);

	DrawFormatString(32, 20, GetColor(0xff, 0xff, 0xff), "防衛地点 %3d/1", BaseCounter);

	DrawFormatString(32, 40, GetColor(0xff, 0xff, 0xff), "Enemy :  %3d/30", clearCounter);
}

//解放処理(最後の1回のみ使用)
void GameScene::Release(void)
{
	DeleteGraph (img_);

	front_->Release();
	delete front_;

	EraseEnemys();
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

	//防衛地点の情報
	Vector2 bPos = AsoUtility::Round({ 1000, Application::SCREEN_SIZE_Y - 650 });
	Vector2 bSize = { 372, Application::SCREEN_SIZE_Y };


	//敵の数だけチェックを行う
	size_t size = enemys.size();
	for (int ii = 0; ii < size; ii++) {
		Pos = enemys[ii]->GetEnemyPos();
		if (!enemys[ii]->GetAlive())continue;

		Vector2 ePos = AsoUtility::Round(Pos);
		Vector2 eSize = enemys[ii]->GetEnemySize();

		//敵とプレイヤーの衝突判定
		if (CollisionChackRectCenter(pPos, pSize, ePos, eSize)) {
			front_->SetDamage(1); 
			//プレイヤーにダメージを与える
		}
		if (!front_->GetAlive()) {
			break;
		}

		//敵とプレイヤーの弾の衝突判定
		if (front_->GetAttackFlg()) {
			//弾を発射している
			if (CollisionChackRectCenter(aPos, aSize, ePos, eSize)) {
				enemys[ii]->SetDamage(10);   //敵にダメージを与える
				clearCounter++;
				}
		}

		if (CollisionChackRectCenter(bPos, bSize, ePos, eSize)) {
			BaseCounter-=1;
			enemys[ii]->SetDamage(10);   //敵にダメージを与える
			clearCounter++;

		}

		if (!enemys[ii]->GetAlive())continue;
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
		return false;
	}

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
