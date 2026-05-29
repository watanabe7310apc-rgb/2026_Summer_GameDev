#pragma once

class TitleScene
{
public:

	static constexpr int TITLE_SIZE_WID = 600;		//タイトル画像の横サイズ
	static constexpr int TITLE_SIZE_HIG = 250;		//タイトル画像の縦サイズ

	TitleScene(void);

	~TitleScene(void);

	void Init(void);		  	    //ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);				    //更新処理
	void Draw(void);				    //描画処理
	bool Release(void);				    //解放処理(最後の１回のみ実行)

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

private:

	//タイトル画面
	int imgTitle_;

	//スタート画面
	int imgTitle_;
};