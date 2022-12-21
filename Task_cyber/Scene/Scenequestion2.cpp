#include"DxLib.h"
#include"Scenequestion2.h"
#include"../game.h"
#include"SceneAnswer2.h"
#include"../Pad.h"

namespace
{
	const char* kQuestion = "問題です\n";		//問題
	const char* kQuestionText = "実在する会社等を装ったメールやショートメッセージを送りつけ、メール等に記載されたリンクから本物そっくりの偽サイトへ誘導し、"		//問題
		"\nID・パスワード等の個人情報を入力させて盗み取る手口のことをワンクリック詐欺という。\n";
	const char* kCircle = "〇";											//ガイド
	const char* kCross = "×";											//ガイド
	const char* kText = "";
	int knum = 0;
	bool kanswer = false;
}
Scenequestion2::Scenequestion2() :
	m_pos(),
	m_boxPos(),
	m_vec(),
	m_hFieldGraphic(-1),
	m_isEnd(-1),
	m_frameCount(),
	m_checkPush(false)
{

}
void Scenequestion2::init()
{
	m_pos.x = 1000;
	m_boxPos.x = 345;
	m_boxPos.y = 420;
	m_vec.x = 1;
	m_isEnd = false;
	m_hFieldGraphic = LoadGraph("data/sky.jpg");			//背景画像の読み込み
	knum = 0;

}

void Scenequestion2::end()
{
	DeleteGraph(m_hFieldGraphic);							//画像データの削除
}

void Scenequestion2::fead()
{
	if (m_checkPush == false)								//フェードアウト処理
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
	if (m_checkPush == true)							//フェードインの処理
	{
		m_fadeValue = 255 * m_fadeTimer / fade_interval;
		if (++m_fadeTimer == fade_interval) {

		}
	}
}

SceneBase* Scenequestion2::update()
{
	fead();											//フェード処理の呼び出し
	m_pos.x -= m_vec.x;								//タイマーのカウント開始

	kText = kQuestionText;							//問題文の代入

	if (Pad::isTrigger(PAD_INPUT_RIGHT))			//右が押されたら右にずらす
	{
		m_boxPos.x += 400;
		if (m_boxPos.x > 745)
		{
			m_boxPos.x = 745;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))				//左が押されたら左にずらす
	{
		m_boxPos.x -= 400;
		if (m_boxPos.x < 345)
		{
			m_boxPos.x = 345;
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1) || m_pos.x < 300)		//押された位置によって正解を得る
	{														//またはタイムアップ
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
	if (m_fadeValue > 255)					//フェードインしたら処理をする
	{
		return(new SceneAnswer2);			//mainに切り替え
		m_fadeValue = 255;
		m_checkPush = false;
	}
	if (m_pos.x < 300)						//タイマーがゼロになったらタイマーを動かすのをやめる
	{
		m_pos.x = 300;
		m_vec.x = 0;
	}
	return this;
}

int Scenequestion2::num() const
{
	int num;
	num = knum;

	return num;
}

bool Scenequestion2::answerNum() const
{
	bool answer;
	answer = kanswer;
	return answer;
}

void Scenequestion2::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	SetFontSize(50);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kQuestion, -1)) / 2,
		150, kQuestion, GetColor(255, 255, 255));			//タイトル画面の表示
	SetFontSize(19);
	DrawString((Game::kScreenWindth - GetDrawStringWidth(kText, -1)) / 2,
		350, kText, GetColor(255, 255, 255));			//タイトル画面の表示

	SetFontSize(45);
	DrawString(350, 425, kCircle, GetColor(255, 100, 100));			//タイトル画面の表示
	DrawString(750, 425, kCross, GetColor(0, 170, 170));			//タイトル画面の表示

	DrawBox(static_cast<int>(m_boxPos.x), static_cast<int>(m_boxPos.y),
		static_cast<int>(m_boxPos.x) + 60, static_cast<int>(m_boxPos.y) + 60, GetColor(255, 0, 255), false);					//操作する四角の表示


	DrawBox(300, 600, static_cast<int>(m_pos.x), 625, GetColor(100, 255, 100), true);						//残り時間で色を変える
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