#pragma once
#include"SceneBase.h"
class SceneAnswer2 : public SceneBase			//ベースクラスを継承してタイトルクラスの作成
{
public:
	SceneAnswer2();
	virtual ~SceneAnswer2() {}

	//初期化
	virtual void init()override;
	//終了処理
	virtual void end()override;

	//フェード処理
	virtual void fead();

	//答えがあっていたかを渡す関数
	virtual int checkAnswer();

	//更新処理
	virtual SceneBase* update()override;
	//描画処理
	virtual void draw() override;

private:
	int m_hFieldGraphic;
	static constexpr int fade_interval = 15;
	int m_fadeTimer = fade_interval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合
	bool m_checkPush;

	bool m_isEnd;

	int m_num;
	bool m_numAnswer;;
};