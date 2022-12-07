#pragma once
#include"SceneBase.h"

class SceneAnswer1 : public SceneBase			//�x�[�X�N���X���p�����ă^�C�g���N���X�̍쐬
{
public:
	SceneAnswer1();
	virtual ~SceneAnswer1() {}

	//������
	virtual void init()override;
	//�I������
	virtual void end()override;

	//�t�F�[�h����
	virtual void fead();

	//�����������Ă�������n���֐�
	virtual int checkAnswer();

	//�X�V����
	virtual SceneBase* update()override;
	//�`�揈��
	virtual void draw() override;

private:
	int m_hFieldGraphic;
	static constexpr int fade_interval = 15;
	int m_fadeTimer = fade_interval; //�t�F�[�h�^�C�}�[
	int m_fadeValue = 255; //����`�Ƃ̃u�����h�
	bool m_checkPush;

	bool m_isEnd;

	int m_num;
	bool m_numAnswer;
};