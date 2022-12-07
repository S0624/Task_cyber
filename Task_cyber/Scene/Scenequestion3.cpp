#include"DxLib.h"
#include "Scenequestion3.h"
#include"../game.h"
#include"SceneAnswer3.h"
#include"../Pad.h"

namespace
{
	const char* kQuestion = "問題です\n";
	const char* kQuestionText = "恋人が浮気をしていないか確認するために\n"
		"勝手にスマホを拝借してメールアプリ等をチェックしたが、犯罪にはならない。";
	const char* kQuestionOptions = "〇　　　　　　　　　　×　　　　　";			//ガイド
	const char* kText = "";
	int knum = 0;
	bool kanswer = false;
}
Scenequestion3::Scenequestion3() :
	m_pos(),
	m_boxPos(),
	m_vec(),
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_frameCount(),
	m_checkPush(false)
{

}
void Scenequestion3::init()
{
	m_pos.x = 1000;
	m_boxPos.x = 450;
	m_boxPos.y = 395;
	m_vec.x = 1;
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");			//背景画像の読み込み
	knum = 0;
}

void Scenequestion3::end()
{
	DeleteGraph(m_hFieldGraphic);							//画像データの削除
}

void Scenequestion3::fead()
{
	if (m_checkPush == false)								//フェードアウト処理
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (--m_fadeTimer == 0) {
			return;
		}
		if (m_fadeValue < 0)
		{
			m_fadeValue = 0;
			m_fadeTimer = 0;
		}
	}
	if (m_checkPush == true)							//フェードインの処理
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (++m_fadeTimer == fade_interval) {

		}
	}
}

SceneBase* Scenequestion3::update()
{
	fead();											//フェード処理の呼び出し
	m_pos.x -= m_vec.x;								//タイマーのカウント開始

	kText = kQuestionText;							//問題文の代入

	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右が押されたら右にずらす
	{
		m_boxPos.x += 200;
		if (m_boxPos.x > 650)
		{
			m_boxPos.x = 650;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))				//左が押されたら左にずらす
	{
		m_boxPos.x -= 200;
		if (m_boxPos.x < 450)
		{
			m_boxPos.x = 450;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1) || m_pos.x < 300)		//押された位置によって正解を得る
	{														//またはタイムアップ
		if (m_boxPos.x == 450 || m_pos.x < 300)
		{
			kanswer = true;
			m_checkPush = true;
		}
		if (m_boxPos.x == 650)
		{
			kanswer = false;
			m_checkPush = true;
		}
	}

	if (m_fadeValue > 255)					//フェードインしたら処理をする
	{
		return(new SceneAnswer3);			//答えに切り替え
		m_fadeValue = 255;
		m_checkPush = false;
	}
	if (m_pos.x < 300)						//タイマーがゼロになったらタイマーを動かすのをやめる
	{
		m_pos.x = 300;
		m_vec.x = 0;
	}
	return this;
}

int Scenequestion3::num() const
{
	int num;
	num = knum;

	return num;
}

bool Scenequestion3::answerNum() const
{
	bool answer;
	answer = kanswer;
	return answer;
}

void Scenequestion3::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	DrawString(600, 150, kQuestion, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kQuestionOptions, -1)) / 2, 400, kQuestionOptions, GetColor(255, 255, 255));			//タイトル画面の表示

	DrawBox(static_cast<int>(m_boxPos.x), static_cast<int>(m_boxPos.y),
		static_cast<int>(m_boxPos.x) + 25, static_cast<int>(m_boxPos.y) + 25, GetColor(255, 0, 25), false);					//操作する四角の表示


	DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(100, 255, 100), true);						//残り時間で色を変える
	if (m_pos.x < 650)
	{
		DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(255, 255, 100), true);
	}
	if (m_pos.x < 400)
	{
		DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(255, 100, 100), true);
	}
	DrawBox(300 - 1, 600 - 1, 1000 + 1, 625 + 1, GetColor(0, 255, 255), false);


	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}