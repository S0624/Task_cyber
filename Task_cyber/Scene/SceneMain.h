#pragma once
#include"SceneBase.h"


class SceneMain : public SceneBase			//ベースクラスを継承してタイトルクラスの作成
{
public:
	SceneMain();
	virtual ~SceneMain() {}

	virtual void init()override;
	virtual void end()override;

	void Fead();


	virtual SceneBase* update()override;
	virtual void draw() override;

	/*void checkNum(int num) { m_num = num; }
	void checkAnswer(bool numAnswer) { m_numAnswer = numAnswer; }*/

	//void setAnswer(int isNum, bool isNumAnswer);

	//virtual bool isEnd()override { return m_isEnd; }
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