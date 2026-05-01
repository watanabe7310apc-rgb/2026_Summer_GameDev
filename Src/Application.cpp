#include<DxLib.h>
#include"Manager/InputManager.h"
#include"Application.h"
#include"FpsControl/FpsControl.h"

Application* Application::instance_ = nullptr;

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return* instance_;
}

void Application::Init(void)
{

	//アプリケーションの初期設定
	SetWindowText("Base Soldier");
	
	//ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(false);

	//DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	//FPS初期化
	fps_ = new FpsControl;
	fps_->Init();

	//乱数のシード値を設定する
	DATEDATA date;

	//現在時刻を取得する
	GetDateTime(&date);

	//乱数の初期値を設定する
	//設定する数値によって、ランダムの出方が変わる
	SRand(date.Year + date.Mon + date.Day + date.Hour + date.Min + date.Sec);

}

void Application :: Run(void)
{
	InputManager& inputManager = InputManager::GetInstance();
	//SceneManager& sceneManager = SceneManager::GetInstance();

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレームレート更新
		//1/60秒超過していないなら再ループさせる
		if (!fps_->UpdateFrameRate())continue;

		inputManager.Update();
		//sceneManager.Update();

		//sceneManager.Draw();

		fps_->CalcFrameRate();   //フレームレート計算
		fps_->DrawFrameRate();   //フレームレート描画

		ScreenFlip();
	}
}

void Application::Destroy(void)
{
	//シーン解放処理
	//SceneManager::GetInstace().Destroy();

	//入力制御解放
	InputManager::GetInstance().Destroy();

	//フレームレート解放
	delete fps_;

	//DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

	//インスタンスのメモリ解放
	delete instance_;
}

bool Application::IsInitFail(void)const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void)const
{
	return isReleaseFail_;
}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
}