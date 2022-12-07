#pragma once
#include"SceneBase.h"

class SceneTitle : public SceneBase			//�x�[�X�N���X���p�����ă^�C�g���N���X�̍쐬
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}

	//������
	virtual void init()override;
	//�I������
	virtual void end()override;
	//�t�F�[�h����
	virtual void fead();

	//�X�V����
	virtual SceneBase* update()override;
	//�`�揈��
	virtual void draw() override;

private:
	int m_hFieldGraph;		// �w�i
	static constexpr int fade_interval = 60;
	int m_fadeTimer = fade_interval; //�t�F�[�h�^�C�}�[
	int m_fadeValue = 255; //����`�Ƃ̃u�����h�
	bool m_checkPush;
};