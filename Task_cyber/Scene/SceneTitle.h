#pragma once
#include"SceneBase.h"

class SceneTitle : public SceneBase			//ベースクラスを継承してタイトルクラスの作成
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}

	virtual void init()override;
	virtual void end()override;

	void Fead();


	virtual SceneBase* update()override;
	virtual void draw() override;

private:
	int m_hFieldGraph;		// 背景
	static constexpr int fade_interval = 60;
	int m_fadeTimer = fade_interval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合
	bool m_checkPush;
};