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
	const char* kQuestionOptions = "〇 → 1ボタン       　×→ 2ボタン";
	const char* kText = "";
	constexpr int kFrameCount = 150;
	int knum = 0;
	bool kanswer = false;
}
Scenequestion3::Scenequestion3() :
	m_pos(),
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
	m_vec.x = 1;
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
	knum = 0;

	m_frameCount = kFrameCount;
}

void Scenequestion3::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void Scenequestion3::Fead()
{
	if (m_checkPush == false)
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
	if (m_checkPush == true)
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (++m_fadeTimer == fade_interval) {

		}
	}
}

SceneBase* Scenequestion3::update()
{
	Fead();
	m_pos.x -= m_vec.x;
	m_frameCount--;
	
	kText = kQuestionText;
	
	if (Pad::isTrigger(PAD_INPUT_1) || m_pos.x < 300)
	{
		kanswer = true;
		m_checkPush = true;
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		kanswer = false;
		m_checkPush = true;
	}
	if (m_fadeValue > 255)
	{
		return(new SceneAnswer3);			//mainに切り替え
		m_fadeValue = 255;
		m_checkPush = false;
	}
	if (m_pos.x < 300)
	{
		m_pos.x = 300;
		m_vec.x = 0;
	}
	return this;
}

int Scenequestion3::Num() const
{
	int num;
	num = knum;

	return num;
}

bool Scenequestion3::AnswerNum() const
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

	DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(100, 255, 100), true);
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