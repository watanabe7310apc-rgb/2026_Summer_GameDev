#pragma once
#include "SceneBase.h"
class GameScene;

class MenuScene : public SceneBase
{
public:

	static constexpr int TITLE_SIZE_X = 465;		// タイトル画像の横サイズ
	static constexpr int TITLE_SIZE_Y = 400;		// タイトル画像の縦サイズ

	static constexpr int START_SIZE_X = 318;       //スタートボタンの横サイズ
	static constexpr int START_SIZE_Y = 228;

	MenuScene(void);
	~MenuScene(void);

	void SystemInit(void) override;			        // 初期化処理(最初の1回のみ実行)
	void GameInit(void) override;		  	        // ゲーム起動・再開時に必ず呼び出す処理
	void Update(void) override;				        // 更新処理
	void Draw(void) override;				        // 描画処理
	void Release(void) override;				    // 解放処理(最後の１回のみ実行)


	int GetLevel(void) { return Select_; }


private:

	int imgSelect_;			                // タイトル画像

	int imgHaikei_;                          // スタート画画像

	int Select_;

	bool Slide_;							//カーソルの移動管理フラグ

};

