#include"DxLib.h"
#include "Scenequestion5.h"
#include"../game.h"
#include"SceneAnswer5.h"
#include"../Pad.h"

namespace
{
	const char* kQuestion = "���ł�\n";
	const char* kQuestionText = "�����̃p�\�R�����E�C���X��s���v���O�����̔�Q�Ɋ��������̂ŁA\n"
		"�}���Ńp�\�R���̓d����؂�A�ċN�������B";
	const char* kQuestionOptions = "�Z �� 1�{�^��       �@�~�� 2�{�^��";
	const char* kText = "";
	constexpr int kFrameCount = 150;
	int knum = 0;
	bool kanswer = false;
}
Scenequestion5::Scenequestion5() :
	m_pos(),
	m_vec(),
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_frameCount(),
	m_checkPush(false)
{

}
void Scenequestion5::init()
{
	m_pos.x = 1000;
	m_vec.x = 1;
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
	knum = 0;

	m_frameCount = kFrameCount;
}

void Scenequestion5::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void Scenequestion5::Fead()
{
	if (m_checkPush == false)
	{
		m_fadeValue = 255 * (m_fadeTimer / fade_interval);
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
		m_fadeValue = 255 * (m_fadeTimer / fade_interval);
		if (++m_fadeTimer == fade_interval) {

		}
	}
}

SceneBase* Scenequestion5::update()
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
		return(new SceneAnswer5);			//main�ɐ؂�ւ�
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

int Scenequestion5::Num() const
{
	int num;
	num = knum;

	return num;
}

bool Scenequestion5::AnswerNum() const
{
	bool answer;
	answer = kanswer;
	return answer;
}

void Scenequestion5::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	DrawString(600, 150, kQuestion, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kQuestionOptions, -1)) / 2, 400, kQuestionOptions, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

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