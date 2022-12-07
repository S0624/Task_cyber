#pragma once
#include "SceneBase.h"
#include"../Vec2.h"
class Scenequestion1 :public SceneBase
{
public:
	Scenequestion1();
	virtual ~Scenequestion1() {}

	//初期化
	virtual void init()override;
	//終了処理
	virtual void end()override;

	//フェード処理
	virtual void fead();

	//更新処理
	virtual SceneBase* update()override;
	//問題の番号を渡す関数
	virtual int num() const;
	//答えを渡す関数
	bool answerNum() const;
	//描画
	virtual void draw() override;

private:
	Vec2 m_pos;
	Vec2 m_boxPos;
	Vec2 m_vec;
	int m_hFieldGraphic;
	bool m_isEnd;
	int m_frameCount;
	static constexpr int fade_interval = 15;
	int m_fadeTimer = fade_interval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合
	bool m_checkPush;
};

