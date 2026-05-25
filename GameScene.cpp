#include <DxLib.h>
#include "GameScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"

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

	img_ = LoadGraph("image/grassland-dot3.jpg");
}

//ゲーム起動・再開時に必ず呼び出す処理
void GameScene::GameInit(void)
{

}

//更新処理
void GameScene::Update(void)
{
	front_->Update();

}

//描画処理
void GameScene::Draw(void)
{
	DrawGraph(0,0, img_, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(Application::SCREEN_SIZE_X*0.75, Application::SCREEN_SIZE_Y/3, 1100, Application::SCREEN_SIZE_Y,
		GetColor(100, 100, 100), true);

	front_->Draw();
}

//解放処理(最後の1回のみ使用)
void GameScene::Release(void)
{
	DeleteGraph (img_);

	front_->Release();
	delete front_;
}

////当たり判定処理
//void GameScene::CollisionCheck(void)
//{
//	//プレイヤーの情報
//	//Vector2 pPos=
//}
//bool GameScene::CollisionChackRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2)
//{
//	//1つ目の矩形の座標を求める
//	Vector2 stPos1 = cPos1;
//
//}
