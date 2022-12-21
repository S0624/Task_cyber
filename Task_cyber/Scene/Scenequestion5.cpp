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
	const char* kCircle = "�Z";											//�K�C�h
	const char* kCross = "�~";											//�K�C�h
	const char* kText = "";
	int knum = 0;
	bool kanswer = false;
	int kSoundSE1;
	int kSoundSE2;
	int kSoundSE3;
}
Scenequestion5::Scenequestion5() :
	m_pos(),
	m_boxPos(),
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
	m_boxPos.x = 345;
	m_boxPos.y = 420;
	m_vec.x = 1;
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");			//�w�i�摜�̓ǂݍ���
	knum = 0;
	kSoundSE1 = LoadSoundMem("Sound/SE1.mp3");
	kSoundSE2 = LoadSoundMem("Sound/SE2.mp3");
	kSoundSE3 = LoadSoundMem("Sound/SE6.mp3");
	PlaySoundMem(kSoundSE3, DX_PLAYTYPE_LOOP);
}

void Scenequestion5::end()
{
	DeleteGraph(m_hFieldGraphic);
	DeleteSoundMem(kSoundSE1);
	DeleteSoundMem(kSoundSE2);
	DeleteSoundMem(kSoundSE3);
}

void Scenequestion5::fead()
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

SceneBase* Scenequestion5::update()
{
	fead();											//�t�F�[�h�����̌Ăяo��
	m_pos.x -= m_vec.x;								//�^�C�}�[�̃J�E���g�J�n

	kText = kQuestionText;							//��蕶�̑��

	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//�E�������ꂽ��E�ɂ��炷
	{
		PlaySoundMem(kSoundSE2, DX_PLAYTYPE_BACK);
		m_boxPos.x += 400;
		if (m_boxPos.x > 745)
		{
			m_boxPos.x = 745;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))				//���������ꂽ�獶�ɂ��炷
	{
		PlaySoundMem(kSoundSE2, DX_PLAYTYPE_BACK);
		m_boxPos.x -= 400;
		if (m_boxPos.x < 345)
		{
			m_boxPos.x = 345;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1) || m_pos.x < 300)		//�����ꂽ�ʒu�ɂ���Đ����𓾂�
	{														//�܂��̓^�C���A�b�v
		PlaySoundMem(kSoundSE1, DX_PLAYTYPE_BACK);
		if (m_boxPos.x == 345 || m_pos.x < 300)
		{
			kanswer = true;
			m_checkPush = true;
		}
		if (m_boxPos.x == 745)
		{
			kanswer = false;
			m_checkPush = true;
		}
	}

	if (m_fadeValue > 255)					//�t�F�[�h�C�������珈��������
	{
		return(new SceneAnswer5);			//�����ɐ؂�ւ�
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

int Scenequestion5::num() const
{
	int num;
	num = knum;

	return num;
}

bool Scenequestion5::answerNum() const
{
	bool answer;
	answer = kanswer;
	return answer;
}

void Scenequestion5::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	SetFontSize(50);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kQuestion, -1)) / 2,
		150, kQuestion, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��
	SetFontSize(20);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2,
		350, kText, GetColor(255, 255, 255));			//�^�C�g����ʂ̕\��

	SetFontSize(45);
	DrawString(350, 425, kCircle, GetColor(255, 100, 100));			//�^�C�g����ʂ̕\��
	DrawString(750, 425, kCross, GetColor(0, 170, 170));			//�^�C�g����ʂ̕\��

	DrawBox(static_cast<int>(m_boxPos.x), static_cast<int>(m_boxPos.y),
		static_cast<int>(m_boxPos.x) + 60, static_cast<int>(m_boxPos.y) + 60, GetColor(255, 0, 255), false);					//���삷��l�p�̕\��


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