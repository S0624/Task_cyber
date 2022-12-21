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

	int kRed = 255;
	int kGreen = 10;
	int kBlue = 10;
	int kCheck = 0;

	int kSoundSE1;
	int kSoundSE2;
	int kSoundSE3;

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
	kSoundSE1 = LoadSoundMem("Sound/SE1.mp3");
	kSoundSE2 = LoadSoundMem("Sound/SE3.mp3");
	kSoundSE3 = LoadSoundMem("Sound/SE4.mp3");

	if (m_question.answerNum() == true)
	{
		PlaySoundMem(kSoundSE2, DX_PLAYTYPE_BACK);
	}
	else
	{
		PlaySoundMem(kSoundSE3, DX_PLAYTYPE_BACK);
	}
}

void SceneAnswer1::end()
{
	DeleteGraph(m_hFieldGraphic);
	DeleteSoundMem(kSoundSE1);
	DeleteSoundMem(kSoundSE2);
	DeleteSoundMem(kSoundSE3);
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
		kRed = 0;
		kGreen = 100;
		kBlue = 255;
		kCheck = 0;
	}
	else
	{
		klegitimate = kcorrect;
		kCheck = 1;
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		PlaySoundMem(kSoundSE1, DX_PLAYTYPE_BACK);
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
	SetFontSize(50);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kAnswer, -1)) / 2,
		200, kAnswer, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(klegitimate, -1)) / 2,
		300, klegitimate, GetColor(kRed, kGreen, kBlue));			//�^�C�g����ʂ̕\��
	SetFontSize(30);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2,
		400, kText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

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
