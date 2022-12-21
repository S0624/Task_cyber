#include"DxLib.h"
#include"SceneTitle.h"
#include"Scenequestion1.h"
#include"SceneMain.h"
#include"../game.h"
#include"../Pad.h"

namespace
{
	const char* const kTitleText = "サイバークイズ";
	const char* const kExplanationText = "ボタンを押してください";
	int kSoundSE1;
}

SceneTitle::SceneTitle() :
	m_hFieldGraph(-1),
	m_checkPush(false)
{
	m_hFieldGraph = LoadGraph("data/blue.png");
	kSoundSE1 = LoadSoundMem("Sound/SE1.mp3");
}

void SceneTitle::init()
{

}

void SceneTitle::end()
{
	DeleteGraph(m_hFieldGraph);
	DeleteSoundMem(kSoundSE1);
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
		PlaySoundMem(kSoundSE1, DX_PLAYTYPE_BACK);
		//return(new SceneMain);			//mainに切り替え
	}
	if (m_fadeValue > 255)
	{
		return(new Scenequestion1);			//mainに切り替え
		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_hFieldGraph, true);
	SetFontSize(40);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kTitleText, -1)) / 2,
		380, kTitleText, GetColor(255, 255, 255));			//タイトル画面の表示
	SetFontSize(25);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kExplanationText, -1)) / 2,
		580, kExplanationText, GetColor(255, 255, 255));			//タイトル画面の表示
	SetFontSize(20);


	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0,0,0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
