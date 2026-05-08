#include "SceneBase.h"

//コンストラクタ
SceneBase::SceneBase(void)
{
}

//デストラクタ
SceneBase::~SceneBase(void)
{
}

//初期化処理(最初の1回のみ実行)
void SceneBase::SystemInit(void)
{
}

//ゲーム起動・再開時に必ず呼び出す処理
void SceneBase::GameInit(void)
{
}

//更新処理
void SceneBase::Update(void)
{
}

//描画処理
void SceneBase::Draw(void)
{
}

//解放処理(最後の1回のみ使用)
void SceneBase::Release(void)
{
}
