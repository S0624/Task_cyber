#include"DxLib.h"
#include "SceneAnswer2.h"
#include"../Pad.h"
#include"Scenequestion2.h"
#include"Scenequestion3.h"
#include"../game.h"

namespace
{
	const char* kAnswer = "正解は…\n";
	const char* kAnswerText = "×が正解。正しい名前はフィッシング詐欺。\n"
		"ワンクリック詐欺は、Webサイトや電子メールに記載されたURLを一度クリックしただけで、一方的にサービスへの入会などの契約成立を宣言され、\n"
		"多額の料金の支払いを求められるという詐欺のことです。\n";
	const char* kmistake = "不正解\n";
	const char* kcorrect = "正解!\n";
	const char* kText = "";
	const char* klegitimate = "";
	constexpr int kFrameCount = 15;

	int kCheck = 0;

	Scenequestion2 m_question;
}

SceneAnswer2::SceneAnswer2() :
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_checkPush(false),
	m_num(0),
	m_numAnswer(false)
{

}
void SceneAnswer2::init()
{
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
}

void SceneAnswer2::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void SceneAnswer2::Fead()
{
	if (m_checkPush == false)
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (--m_fadeTimer == 0) {
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

SceneBase* SceneAnswer2::update()
{
	Fead();

	kText = kAnswerText;
	if (m_question.AnswerNum() == true)
	{
		klegitimate = kmistake;
		kCheck = 0;
	}
	else
	{
		klegitimate = kcorrect;
		kCheck = 1;
	}
	
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_checkPush = true;
	}
	if (m_fadeValue > 255)
	{
		return(new Scenequestion3);			//mainに切り替え
		
		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}
void SceneAnswer2::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	DrawString(600, 150, kAnswer, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString(600, 250, klegitimate, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//タイトル画面の表示

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int SceneAnswer2::CheckAnswer()
{
	int check = 0;
	check = kCheck;
	return check;
}
