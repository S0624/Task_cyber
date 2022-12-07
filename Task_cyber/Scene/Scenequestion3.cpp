#include"DxLib.h"
#include "Scenequestion3.h"
#include"../game.h"
#include"SceneAnswer3.h"
#include"../Pad.h"

namespace
{
	const char* kQuestion = "���ł�\n";
	const char* kQuestionText = "���l�����C�����Ă��Ȃ����m�F���邽�߂�\n"
		"����ɃX�}�z��q�؂��ă��[���A�v�������`�F�b�N�������A�ƍ߂ɂ͂Ȃ�Ȃ��B";
	const char* kQuestionOptions = "�Z�@�@�@�@�@�@�@�@�@�@�~�@�@�@�@�@";			//�K�C�h
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
	m_hFieldGraphic = LoadGraph("data/sky.jpg");			//�w�i�摜�̓ǂݍ���
	knum = 0;
}

void Scenequestion3::end()
{
	DeleteGraph(m_hFieldGraphic);							//�摜�f�[�^�̍폜
}

void Scenequestion3::fead()
{
	if (m_checkPush == false)								//�t�F�[�h�A�E�g����
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
	if (m_checkPush == true)							//�t�F�[�h�C���̏���
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (++m_fadeTimer == fade_interval) {

		}
	}
}

SceneBase* Scenequestion3::update()
{
	fead();											//�t�F�[�h�����̌Ăяo��
	m_pos.x -= m_vec.x;								//�^�C�}�[�̃J�E���g�J�n

	kText = kQuestionText;							//��蕶�̑��

	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�������ꂽ��E�ɂ��炷
	{
		m_boxPos.x += 200;
		if (m_boxPos.x > 650)
		{
			m_boxPos.x = 650;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))				//���������ꂽ�獶�ɂ��炷
	{
		m_boxPos.x -= 200;
		if (m_boxPos.x < 450)
		{
			m_boxPos.x = 450;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1) || m_pos.x < 300)		//�����ꂽ�ʒu�ɂ���Đ����𓾂�
	{														//�܂��̓^�C���A�b�v
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

	if (m_fadeValue > 255)					//�t�F�[�h�C�������珈��������
	{
		return(new SceneAnswer3);			//�����ɐ؂�ւ�
		m_fadeValue = 255;
		m_checkPush = false;
	}
	if (m_pos.x < 300)						//�^�C�}�[���[���ɂȂ�����^�C�}�[�𓮂����̂���߂�
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
	DrawString(600, 150, kQuestion, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kQuestionOptions, -1)) / 2, 400, kQuestionOptions, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

	DrawBox(static_cast<int>(m_boxPos.x), static_cast<int>(m_boxPos.y),
		static_cast<int>(m_boxPos.x) + 25, static_cast<int>(m_boxPos.y) + 25, GetColor(255, 0, 25), false);					//���삷��l�p�̕\��


	DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(100, 255, 100), true);						//�c�莞�ԂŐF��ς���
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