#include <DxLib.h>
#include "Fader.h"
#include "Application.h"

Fader::Fader(void)
{

}

//デストラクタ
Fader::~Fader(void)
{

}

//初期化処理(最初の1回のみ実行)
bool Fader::SystemInit(void)
{
	GameInit();

	return true;
}

//ゲーム起動・再開時に必ず呼び出す処理
void Fader::GameInit(void)
{
	stat = STATE::NONE;
	alpha = 0.0f;
	endFlg = true;
}

//更新処理
void Fader::Update(void)
{
	if (endFlg)return;

	switch (stat) {
	case STATE::NONE:
			return;
	case STATE::FADE_OUT:
			alpha += FADE_SPEED_ALPHA;
			if (alpha > 255.0f) {
				//フェードアウト終了
				alpha = 255.0f;
				endFlg = true;
				stat = STATE::NONE;
			}
			break;
	case STATE::FADE_IN:
			alpha -= FADE_SPEED_ALPHA;
			if (alpha < 0) {
				//フェードイン終了
				alpha = 0.0f;
				endFlg = true;
				stat = STATE::NONE;
			}
			break;
		default:
			return;
	}
}
//描画処理
void Fader::Draw(void)
{
	switch (stat) {
	case STATE::NONE:
		return;
	case STATE::FADE_OUT:
	case STATE::FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);   //表示の際にα値をブレンドするモードに設定
		DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y,
			GetColor(0, 0, 0), true);   //透明度を変化させた板を表示するイメージ
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);   //表示に何もブレンドしない通常のモードに戻す
		break;
	default:
		return;
	}
}

//解放処理(最後の1回のみ実行)
bool Fader::Release(void)
{
	return true;
}

void Fader::SetFade(STATE id)
{
	stat = id;
	if (stat != STATE::NONE) {
	endFlg = false;
	}
}
