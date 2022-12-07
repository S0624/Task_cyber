#include"DxLib.h"
#include "SceneAnswer1.h"
#include"../Pad.h"
#include"Scenequestion1.h"
#include"Scenequestion2.h"
#include"../game.h"

namespace
{
	const char* kAnswer = "�����́c\n";
	const char* kAnswerText = "�Z�������B��ʂɏ����Ă���d�b�ԍ��ɂ͐�Γd�b���Ă͂��߂ł��B\n"
		"�u���E�U����邩�A�p�\�R�����ċN�����܂��傤�B\n";
	const char* kmistake = "�s����\n";
	const char* kcorrect = "����!\n";
	const char* kText = "";
	const char* klegitimate = "";
	constexpr int kFrameCount = 15;

	int kCheck = 0;

	Scenequestion1 m_question;
}

SceneAnswer1::SceneAnswer1() :
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_checkPush(false),
	m_num(0),
	m_numAnswer(false)
{

}
void SceneAnswer1::init()
{
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
}

void SceneAnswer1::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void SceneAnswer1::fead()
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

SceneBase* SceneAnswer1::update()
{
	fead();
	
	kText = kAnswerText;
	if (m_question.answerNum() == true)
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
		
		return(new Scenequestion2);			//main�ɐ؂�ւ�

		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}
void SceneAnswer1::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	DrawString(600, 150, kAnswer, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString(600, 250, klegitimate, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int SceneAnswer1::checkAnswer()
{
	int check = 0;
	check = kCheck;
	return check;
}
