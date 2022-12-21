#include"DxLib.h"
#include "SceneAnswer2.h"
#include"../Pad.h"
#include"Scenequestion2.h"
#include"Scenequestion3.h"
#include"../game.h"

namespace
{
	const char* kAnswer = "�����́c\n";
	const char* kAnswerText = "�~�������B���������O�̓t�B�b�V���O���\�B\n"
		"�����N���b�N���\�́AWeb�T�C�g��d�q���[���ɋL�ڂ��ꂽURL����x�N���b�N���������ŁA\n"
		"����I�ɃT�[�r�X�ւ̓���Ȃǂ̌_�񐬗���錾����A\n"
		"���z�̗����̎x���������߂���Ƃ������\�̂��Ƃł��B\n";
	const char* kmistake = "�s����\n";
	const char* kcorrect = "����!\n";
	const char* kText = "";
	const char* klegitimate = "";
	constexpr int kFrameCount = 15;

	int kRed = 255;
	int kGreen = 10;
	int kBlue = 10;
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

void SceneAnswer2::fead()
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
		m_checkPush = true;
	}
	if (m_fadeValue > 255)
	{
		return(new Scenequestion3);			//main�ɐ؂�ւ�
		
		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}
void SceneAnswer2::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	SetFontSize(50);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kAnswer, -1)) / 2,
		200, kAnswer, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(klegitimate, -1)) / 2,
		300, klegitimate, GetColor(kRed, kGreen, kBlue));			//�^�C�g����ʂ̕\��
	SetFontSize(27);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2,
		400, kText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int SceneAnswer2::checkAnswer()
{
	int check = 0;
	check = kCheck;
	return check;
}
