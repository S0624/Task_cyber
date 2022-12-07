#include"DxLib.h"
#include"SceneAnswer3.h"
#include"../Pad.h"
#include"Scenequestion3.h"
#include"Scenequestion4.h"
#include"../game.h"

namespace
{
	const char* kAnswer = "正解は…\n";
	const char* kAnswerText = "×が正解。浮気はよくないことですが、勝手にLINEを開いたり、\n"
		"メールアプリを開いてメールを見てしまうと不正アクセス行為の禁止等に関する法律違反になる可能性があります。\n";
	const char* kmistake = "不正解\n";
	const char* kcorrect = "正解!\n";
	const char* kText = "";
	const char* klegitimate = "";
	constexpr int kFrameCount = 15;

	int kCheck = 0;

	Scenequestion3 m_question;
}

SceneAnswer3::SceneAnswer3() :
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_checkPush(false),
	m_num(0),
	m_numAnswer(false)
{

}
void SceneAnswer3::init()
{
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
}

void SceneAnswer3::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void SceneAnswer3::Fead()
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

SceneBase* SceneAnswer3::update()
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
		
		return(new Scenequestion4);			//mainに切り替え
		
		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}
void SceneAnswer3::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	DrawString(600, 150, kAnswer, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString(600, 250, klegitimate, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//タイトル画面の表示

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
int SceneAnswer3::CheckAnswer()
{
	int check = 0;
	check = kCheck;
	return check;
}
