#pragma once
#include"SceneBase.h"
#include"../Vec2.h"

class Scenequestion2 : public SceneBase			//�x�[�X�N���X���p�����ă^�C�g���N���X�̍쐬
{
public:
	Scenequestion2();
	virtual ~Scenequestion2() {}

	//������
	virtual void init()override;
	//�I������
	virtual void end()override;

	//�t�F�[�h����
	virtual void fead();

	//�X�V����
	virtual SceneBase* update()override;
	//���̔ԍ���n���֐�
	virtual int num() const;
	//������n���֐�
	bool answerNum() const;
	//�`��
	virtual void draw() override;

private:
	Vec2 m_pos;
	Vec2 m_boxPos;
	Vec2 m_vec;
	int m_hFieldGraphic;
	bool m_isEnd;
	int m_frameCount;
	static constexpr int fade_interval = 15;
	int m_fadeTimer = fade_interval; //�t�F�[�h�^�C�}�[
	int m_fadeValue = 255; //����`�Ƃ̃u�����h�
	bool m_checkPush;
};