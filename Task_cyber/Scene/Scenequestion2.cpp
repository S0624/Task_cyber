#include"DxLib.h"
#include"Scenequestion2.h"
#include"../game.h"
#include"SceneAnswer2.h"
#include"../Pad.h"

namespace
{
	const char* kQuestion = "問題です\n";
	const char* kQuestionText = "実在する会社等を装ったメールやショートメッセージを送りつけ、メール等に記載されたリンクから本物そっくりの偽サイトへ誘導し、"
		"\nID・パスワード等の個人情報を入力させて盗み取る手口のことをワンクリック詐欺という。\n";
	const char* kQuestionOptions = "〇 → 1ボタン       　×→ 2ボタン";
	const char* kText = "";
	int knum = 0;
	bool kanswer = false;
}
Scenequestion2::Scenequestion2() :
	m_pos(),
	m_vec(),
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_frameCount(),
	m_checkPush(false)
{

}
void Scenequestion2::init()
{
	//m_num = 0;
	//m_num = false;
	m_pos.x = 1000;
	m_vec.x = 1;
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");
	knum = 0;

}

void Scenequestion2::end()
{
	DeleteGraph(m_hFieldGraphic);
}

void Scenequestion2::Fead()
{
	if (m_checkPush == false)
	{
		m_fadeValue = 255 * (m_fadeTimer / fade_interval);
		if (--m_fadeTimer == 0) {
			return;
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

SceneBase* Scenequestion2::update()
{
	//if(kQuestionNum[0] && kQuestionNum[1] && kQuestionNum[2] == 1 )
	//if (Pad::isTrigger(PAD_INPUT_1))
	//{
	//	return(new SceneMain);			//mainに切り替え
	//	//m_isEnd = true;					//mainに切り替え
	//}


	//int num = 1;
	Fead();
	m_pos.x -= m_vec.x;
	kText = kQuestionText;
	
	if (Pad::isTrigger(PAD_INPUT_1) || m_pos.x < 300)
	{
		kanswer = true;
		m_checkPush = true;
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		kanswer = false;
		m_checkPush = true;
	}
	if (m_fadeValue > 255)
	{
		return(new SceneAnswer2);			//mainに切り替え
		m_fadeValue = 255;
		m_checkPush = false;
	}
	if (m_pos.x < 300)
	{
		m_pos.x = 300;
		m_vec.x = 0;
	}
	return this;
}

int Scenequestion2::Num() const
{
	int num;
	num = knum;

	return num;
}

bool Scenequestion2::AnswerNum() const
{
	bool answer;
	answer = kanswer;
	return answer;
}

void Scenequestion2::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	//DrawString(620, 480, kTitleText, GetColor(255, 255, 255));			//タイトル画面の表示
	//DrawString(620, 580, kExplanationText, GetColor(255, 255, 255));			//メイン画面の表示
	DrawString(600, 150, kQuestion, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2, 350, kText, GetColor(255, 255, 255));			//タイトル画面の表示
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kQuestionOptions, -1)) / 2, 400, kQuestionOptions, GetColor(255, 255, 255));			//タイトル画面の表示

	DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(100, 255, 100), true);
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