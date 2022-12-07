#pragma once
#include"SceneBase.h"

class SceneResult : public SceneBase			//�x�[�X�N���X���p�����ă^�C�g���N���X�̍쐬
{
public:
	SceneResult();
	virtual ~SceneResult() {}

	virtual void init()override;
	virtual void end()override;

	void Fead();

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	int m_hFieldHandle;		// �w�i
	static constexpr int fade_interval = 60;
	int m_fadeTimer = fade_interval; //�t�F�[�h�^�C�}�[
	int m_fadeValue = 255; //����`�Ƃ̃u�����h�
	bool m_checkPush;
};