#include"DxLib.h"
#include"SceneTitle.h"
#include"Scenequestion1.h"
#include"SceneMain.h"
#include"../Pad.h"

namespace
{
	const char* const kTitleText = "�T�C�o�[�N�C�Y";
	const char* const kExplanationText = "�{�^���������Ă�������";
}

SceneTitle::SceneTitle() :
	m_hFieldGraph(-1),
	m_checkPush(false)
{
	m_hFieldGraph = LoadGraph("data/blue.png");
}

void SceneTitle::init()
{

}

void SceneTitle::end()
{

}

void SceneTitle::fead()
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
	if(m_checkPush == true)
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (++m_fadeTimer == fade_interval) {

		}
	}
}


SceneBase* SceneTitle::update()
{
	fead();
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_checkPush = true;
		//return(new SceneMain);			//main�ɐ؂�ւ�
	}
	if (m_fadeValue > 255)
	{
		return(new Scenequestion1);			//main�ɐ؂�ւ�
		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_hFieldGraph, true);
	DrawString(570, 480, kTitleText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString(547, 580, kExplanationText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0,0,0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
