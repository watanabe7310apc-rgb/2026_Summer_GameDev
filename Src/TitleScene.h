#pragma once

#include "../SceneBase.h"


class TitleScene:public SceneBase
{
public:

	static constexpr int TITLE_SIZE_WID = 600;		// タイトル画像の横サイズ
	static constexpr int TITLE_SIZE_HIG = 250;		// タイトル画像の縦サイズ

	TitleScene(void);
	~TitleScene(void);

	void SystemInit(void) override;			        // 初期化処理(最初の1回のみ実行)
	void GameInit(void) override;		  	        // ゲーム起動・再開時に必ず呼び出す処理
	void Update(void) override;				        // 更新処理
	void Draw(void) override;				        // 描画処理
	void Release(void) override;				    // 解放処理(最後の１回のみ実行)


private:
	int imgTitle_;			                // タイトル画像

	int imgStart_;                          // スタート画画像
	
};