#pragma once

#include "..//StDefine.h"

class Fader
{
public:
	static constexpr float FADE_SPEED_ALPHA = 3;   //フェードの速さ


	// 状態
	enum class STATE
	{
		NONE,
		FADE_OUT,	// 徐々に暗転
		FADE_IN		// 徐々に明転
	};

	Fader(void);     //コンストラクタ
	~Fader(void);    //デストラクタ

	bool SystemInit(void);   //初期化処理(最初の1回のみ実行)
	void GameInit(void);     //ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);       //更新処理
	void Draw(void);         //描画処理
	bool Release(void);      //解放処理(最後の1回のみ実行)

	//ゲッター・セッター関数
	STATE GetNowState(void) { return stat; }
	bool IsEnd(void) { return endFlg; }
	void SetFade(STATE id);

private:
	STATE stat;     //ステータス
	float alpha;             //アルファ値用の変数
	bool endFlg;             //フェード処理終了フラグ(true=未実行/false=実行中)
};
