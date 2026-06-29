#pragma once

//---------------------
// 列挙型定義
//---------------------
enum E_SCENE_ID {
	E_SCENE_NON,
	E_SCENE_TITLE,                      //タイトル画面
	E_SCENE_SELECT,                     //レベル選択画面
	E_SCENE_GAME,                       //ゲームプレイ画面
	E_SCENE_GAMEOVER,                   //ゲームオーバー画面
	E_SCENE_CLEAR,						//ゲームクリア画面

	E_SCENE_ID_MAX
};

//フェードの状態
enum E_FADE_STAT_ID {
	E_STAT_FADE_NON,
	E_STAT_FADE_OUT,                    //フェードアウト(徐々に暗転する)
	E_STAT_FADE_IN,                     //フェードイン(徐々に明転する)

	E_STAT_FADE_MAX,
};


//構造体の例
struct POSITION
{
	int x;
	int y;
};
