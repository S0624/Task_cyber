#include"DxLib.h"
#include"SceneResult.h"
#include"SceneAnswer1.h"
#include"SceneAnswer2.h"
#include"SceneAnswer3.h"
#include"SceneAnswer4.h"
#include"SceneAnswer5.h"
#include"SceneTitle.h"
#include"../Pad.h"

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
}
SceneResult::SceneResult() :
	m_hFieldHandle(-1),
	m_checkPush(false)
{
	m_hFieldHandle = LoadGraph("data/blue.png");
}

void SceneResult::init()
{

}

void SceneResult::end()
{

}

void SceneResult::Fead()
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

	Fead();
	kAnswercnt = 0;
	(kAnswercnt = scene1.CheckAnswer() + scene2.CheckAnswer() + scene3.CheckAnswer()
		+ scene4.CheckAnswer() + scene5.CheckAnswer());

	if (Pad::isTrigger(PAD_INPUT_1))
	{
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
	//DrawString(600, 480, kTitleText, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString(547, 580, kExplanationText, GetColor(255, 255, 255));			//タイトル画面の表示
	
	DrawFormatString(560, 400, GetColor(255, 255, 255), " %d問正解しました", kAnswercnt);
	{
		if (scene1.CheckAnswer() == 1)
		{
			DrawFormatString(300, 175, GetColor(255, 255, 255), " 1問目 :　〇");
		}
		else
		{
			DrawFormatString(300, 175, GetColor(255, 255, 255), " 1問目 :　×");
		}
		if (scene2.CheckAnswer() == 1)
		{
			DrawFormatString(600, 175, GetColor(255, 255, 255), " 2問目 :　〇");
		}
		else
		{
			DrawFormatString(600, 175, GetColor(255, 255, 255), " 2問目 :　×");
		}
		if (scene3.CheckAnswer() == 1)
		{
			DrawFormatString(900, 175, GetColor(255, 255, 255), " 3問目 :　〇");
		}
		else
		{
			DrawFormatString(900, 175, GetColor(255, 255, 255), " 3問目 :　×");
		}
		if (scene4.CheckAnswer() == 1)
		{
			DrawFormatString(450, 225, GetColor(255, 255, 255), " 4問目 :　〇");
		}
		else
		{
			DrawFormatString(450, 225, GetColor(255, 255, 255), " 4問目 :　×");
		}
		if (scene5.CheckAnswer() == 1)
		{
			DrawFormatString(750, 225, GetColor(255, 255, 255), " 5問目 :　〇");
		}
		else
		{
			DrawFormatString(750, 225, GetColor(255, 255, 255), " 5問目 :　×");
		}

	}
	
	//DrawFormatString(0, 0, GetColor(255, 0, 0), " %d", scene1.CheckAnswer());
	//DrawFormatString(0, 20, GetColor(255, 0, 0), " %d", scene2.CheckAnswer());
	//DrawFormatString(0, 40, GetColor(255, 0, 0), " %d", scene3.CheckAnswer());
	//DrawFormatString(0, 60, GetColor(255, 0, 0), " %d", scene4.CheckAnswer());
	//DrawFormatString(0, 80, GetColor(255, 0, 0), " %d", scene5.CheckAnswer());


	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}
