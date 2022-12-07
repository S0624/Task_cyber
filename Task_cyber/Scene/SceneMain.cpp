#include"DxLib.h"
#include"SceneMain.h"
#include"../Pad.h"
#include"Scenequestion1.h"
#include"Scenequestion2.h"
#include"Scenequestion3.h"
#include"../game.h"

namespace
{
	const char* const kTitleText = "メイン";
	const char* const kExplanationText = "1ボタンを押してください";
	const char*  kAnswer = "正解は…\n";
	const char*  kAnswerText1 = "〇が正解。画面に書いてある電話番号には絶対電話してはだめです。\n"
		"ブラウザを閉じるか、パソコンを再起動しましょう。\n";
	const char*  kAnswerText2 = "×が正解。正しい名前はフィッシング詐欺。\n"
		"ワンクリック詐欺は、Webサイトや電子メールに記載されたURLを一度クリックしただけで、一方的にサービスへの入会などの契約成立を宣言され、\n"
		"多額の料金の支払いを求められるという詐欺のことです。\n";
	const char*  kAnswerText3 = "〇\n";
	const char*  kmistake = "不正解\n";
	const char*  kcorrect = "正解!\n";
	int kAnswerNum[3]{ 0,0,0 };
	const char*  kText = "";
	const char*  klegitimate = "";
	constexpr int kFrameCount = 15;

	Scenequestion1 m_question;
	//Scenequestion2 m_question;
	//Scenequestion3 m_question;
}

SceneMain::SceneMain():
	m_hFieldGraphic(-1),
	m_isEnd(-1), 
	m_checkPush(false),
	m_num(0),
	m_numAnswer(false)
{

}
void SceneMain::init()
{
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
}

void SceneMain::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void SceneMain::Fead()
{
	if (m_checkPush == false)
	{
		m_fadeValue = 255 * (m_fadeTimer / fade_interval);
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
		m_fadeValue = 255 * (m_fadeTimer / fade_interval);
		if (++m_fadeTimer == fade_interval) {

		}
	}
}

SceneBase* SceneMain::update()
{
	Fead();

	//if(kQuestionNum[0] && kQuestionNum[1] && kQuestionNum[2] == 1 )
	//if (Pad::isTrigger(PAD_INPUT_1))
	//{
	//	return(new SceneResult);			//mainに切り替え
	//	//m_isEnd = true;					//mainに切り替え
	//}
	//int num = m_question.checkNum();
	

	//switch (m_num)
	
	switch (m_question.Num())
	{
	case 0:
		kText = kAnswerText1;
		kAnswerNum[0] = 1;

		if (m_question.AnswerNum() == true)
		{
			klegitimate = kmistake;
		}
		else
		{
			klegitimate = kcorrect;
		}

		//if (m_frameCount >= kFrameCount)
		 //{
		//return(new SceneMain);			//mainに切り替え
		//}
		break;
	case 1:
		kText = kAnswerText2;
		kAnswerNum[1] = 1;
		if (m_question.AnswerNum() == false)
		{
			klegitimate = kmistake;
		}
		else
		{
			klegitimate = kcorrect;
		}
		break;
	case 2:
	default:
		kText = kAnswerText3;
		kAnswerNum[2] = 1;
		if (m_question.AnswerNum() == true)
		{
			klegitimate = kmistake;
		}
		else
		{
			klegitimate = kcorrect;
		}
		break;

	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_checkPush = true;
	}
	if (m_fadeValue > 255)
	{
		if (kAnswerNum[1] == 0)
		{
			return(new Scenequestion2);			//mainに切り替え
		}
		m_fadeValue = 255;
		m_checkPush = false;
	}
	return this;
}
void SceneMain::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	DrawString(600, 150, kAnswer, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString(600, 250, klegitimate, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//タイトル画面の表示

	DrawFormatString(0, 0, GetColor(255, 255, 255), ":%d", kAnswerNum[0]);
	DrawFormatString(0, 20, GetColor(255, 255, 255), ":%d", kAnswerNum[1]);
	DrawFormatString(0, 40, GetColor(255, 255, 255), ":%d", kAnswerNum[2]);
	DrawFormatString(0, 100, GetColor(255, 255, 255), ":%d", m_question.Num());
	
	DrawFormatString(0, 200, GetColor(255, 255, 255), ":%d", m_fadeValue);

	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	if (m_question.AnswerNum() == false)
	{
		DrawFormatString(0, 80, GetColor(255, 255, 255), "false");
	}
	else
	{
		DrawFormatString(0, 80, GetColor(255, 255, 255), "true");
	}
}