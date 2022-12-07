#pragma once
#include"SceneBase.h"
class SceneAnswer3 : public SceneBase			//ベースクラスを継承してタイトルクラスの作成
{
public:
	SceneAnswer3();
	virtual ~SceneAnswer3() {}

	virtual void init()override;
	virtual void end()override;

	void Fead();


	virtual SceneBase* update()override;
	virtual void draw() override;

	int CheckAnswer();

private:
	int m_hFieldGraphic;
	static constexpr int fade_interval = 15;
	int m_fadeTimer = fade_interval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合
	bool m_checkPush;

	bool m_isEnd;

	int m_num;
	bool m_numAnswer;
};