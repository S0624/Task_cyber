#pragma once
#include"SceneBase.h"

class SceneResult : public SceneBase			//ベースクラスを継承してタイトルクラスの作成
{
public:
	SceneResult();
	virtual ~SceneResult() {}

	//初期化
	virtual void init()override;
	//終了処理
	virtual void end()override;

	//フェード処理
	virtual void fead();

	//更新処理
	virtual SceneBase* update() override;
	//描画処理
	virtual void draw() override;

private:
	int m_hFieldHandle;		// 背景
	static constexpr int fade_interval = 60;
	int m_fadeTimer = fade_interval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合
	bool m_checkPush;
};