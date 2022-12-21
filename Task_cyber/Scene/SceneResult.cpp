#include"DxLib.h"
#include"SceneResult.h"
#include"SceneAnswer1.h"
#include"SceneAnswer2.h"
#include"SceneAnswer3.h"
#include"SceneAnswer4.h"
#include"SceneAnswer5.h"
#include"SceneTitle.h"
#include"../Pad.h"
#include"../game.h"

namespace
{
	const char* const kTitleText = "リザルト";
	const char* const kExplanationText = "ボタンを押してください";
		
	SceneAnswer1 scene1;
	SceneAnswer2 scene2;
	SceneAnswer3 scene3;
	SceneAnswer4 scene4;
	SceneAnswer5 scene5;
	int kAnswercnt;
	int kSoundSE1;
	int kSoundSE2;
}
SceneResult::SceneResult() :
	m_hFieldHandle(-1),
	m_checkPush(false)
{
	m_hFieldHandle = LoadGraph("data/blue.png");

}

void SceneResult::init()
{
	kSoundSE1 = LoadSoundMem("Sound/SE1.mp3");
	kSoundSE2 = LoadSoundMem("Sound/SE7.mp3");
	PlaySoundMem(kSoundSE2, DX_PLAYTYPE_BACK);
}

void SceneResult::end()
{
	DeleteGraph(m_hFieldHandle);
	DeleteSoundMem(kSoundSE1);
	DeleteSoundMem(kSoundSE2);
}

void SceneResult::fead()
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

SceneBase* SceneResult::update()
{

	fead();
	kAnswercnt = 0;
	(kAnswercnt = scene1.checkAnswer() + scene2.checkAnswer() + scene3.checkAnswer()
		+ scene4.checkAnswer() + scene5.checkAnswer());

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		PlaySoundMem(kSoundSE1, DX_PLAYTYPE_BACK);
		m_checkPush = true;
	}
	if (m_fadeValue > 255)
	{
		m_fadeValue = 255;
		m_checkPush = false;
		return(new SceneTitle);			//mainに切り替え
		}
	return this;
}

void SceneResult::draw()
{
	DrawGraph(0, 0, m_hFieldHandle, true);
	SetFontSize(40);
	DrawFormatString((Game::kScreenWindth - GetDrawStringWidth(" %d問正解しました", -1)) / 2,
		400, GetColor(255, 170, 170), " %d問正解しました", kAnswercnt);

	SetFontSize(30);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kExplanationText, -1)) / 2,
		580, kExplanationText, GetColor(255, 255, 255));			//タイトル画面の表示
	
	{
		if (scene1.checkAnswer() == 1)
		{
			DrawFormatString(300, 175, GetColor(255, 255, 255), " 1問目 :　〇");
		}
		else
		{
			DrawFormatString(300, 175, GetColor(255, 255, 255), " 1問目 :　×");
		}
		if (scene2.checkAnswer() == 1)
		{
			DrawFormatString(600, 175, GetColor(255, 255, 255), " 2問目 :　〇");
		}
		else
		{
			DrawFormatString(600, 175, GetColor(255, 255, 255), " 2問目 :　×");
		}
		if (scene3.checkAnswer() == 1)
		{
			DrawFormatString(900, 175, GetColor(255, 255, 255), " 3問目 :　〇");
		}
		else
		{
			DrawFormatString(900, 175, GetColor(255, 255, 255), " 3問目 :　×");
		}
		if (scene4.checkAnswer() == 1)
		{
			DrawFormatString(450, 225, GetColor(255, 255, 255), " 4問目 :　〇");
		}
		else
		{
			DrawFormatString(450, 225, GetColor(255, 255, 255), " 4問目 :　×");
		}
		if (scene5.checkAnswer() == 1)
		{
			DrawFormatString(750, 225, GetColor(255, 255, 255), " 5問目 :　〇");
		}
		else
		{
			DrawFormatString(750, 225, GetColor(255, 255, 255), " 5問目 :　×");
		}

	}



	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}
