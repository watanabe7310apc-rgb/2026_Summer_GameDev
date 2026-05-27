#include <DxLib.h>
#include "GameScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"
#include "EnemyBase.h"
#include "EnemyDragon.h"

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

	img_ = LoadGraph("image/ゲーム背景(城壁).jpg");
}

//ゲーム起動・再開時に必ず呼び出す処理
void GameScene::GameInit(void)
{

}

//更新処理
void GameScene::Update(void)
{
	front_->Update();

	size_t size = enemys.size();               //敵のテーブルの要素数を取得
	for (auto e : enemys) {
		e->Update();
	}
	//エンカウンター
	enCounter++;
	if (enCounter > ENCOUNT) {

		//敵の生成
		EnemyBase* e = nullptr;

		//ランダムに種別を決める
		int rr = GetRand(static_cast<int>(EnemyBase::E_ENEMY_ID::E_TYPE_MAX) - 1);
		EnemyBase::E_ENEMY_ID type = static_cast<EnemyBase::E_ENEMY_ID>(rr);
		type = EnemyBase::E_ENEMY_ID::E_TYPE_DRAGON;   //デバック用

		//種別に対応した派生クラスのインスタンスを生成
		switch (type) {
		case EnemyBase::E_ENEMY_ID::E_TYPE_DRAGON:
			e = new EnemyDragon();
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


//描画処理
void GameScene::Draw(void)
{
	DrawGraph(0,0, img_, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(Application::SCREEN_SIZE_X*0.75, Application::SCREEN_SIZE_Y/3, 1100, Application::SCREEN_SIZE_Y,
		GetColor(100, 100, 100), true);

	front_->Draw();

	for (auto e:enemys) {
		e->Draw();
	}

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
	//プレイヤーの情報
	//プレイヤーの座標を取得
	Vector2 pPos = front_->GetFrontPos();
	//前衛のサイズ
	Vector2 pSize = { PlayerFront::SIZE_X,PlayerFront::SIZE_Y };
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
		return true;
	}

	return false;
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
