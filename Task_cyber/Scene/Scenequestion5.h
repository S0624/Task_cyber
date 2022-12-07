#pragma once
#include "SceneBase.h"
#include"../Vec2.h"
class Scenequestion5 :public SceneBase
{
public:
	Scenequestion5();
	virtual ~Scenequestion5() {}

	virtual void init()override;
	virtual void end()override;

	void Fead();

	virtual SceneBase* update()override;
	int Num() const;
	bool AnswerNum() const;
	virtual void draw() override;


	//virtual bool isEnd()override { return m_isEnd; }
private:
	//int m_QuestionNum[3]{ 0,0,0 };
	Vec2 m_pos;
	Vec2 m_vec;
	int m_hFieldGraphic;
	bool m_isEnd;
	int m_frameCount;
	static constexpr int fade_interval = 15;
	int m_fadeTimer = fade_interval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合
	bool m_checkPush;
};