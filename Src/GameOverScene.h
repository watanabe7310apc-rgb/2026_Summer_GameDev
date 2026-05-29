#pragma once

class GameOverScene
{

public:

	// コンストラクタ
	GameOverScene(void);

	// デストラクタ
	~GameOverScene(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// ゲームオーバー画像
	int imgGameOver_;

	// スタート画像
	int imgStart_;

};