#include <cassert>
#include"SceneManager.h"
#include "SceneTitle.h"
#include "Scenequestion1.h"
#include "../Pad.h"

SceneManager::SceneManager() :
	m_pScene (nullptr)
{

}


void SceneManager::init()
{
	m_pScene = new SceneTitle;
	//m_pScene = new Scenequestion1;
	m_pScene->init();
}

void SceneManager::end()
{
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->end();
	delete m_pScene;
}

void SceneManager::update()
{
	Pad::update();
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;
	// SceneBaseのupdate処理呼び出し
	SceneBase* pScene = m_pScene->update();
	if (pScene != m_pScene)
	{
		m_pScene->end();
		delete m_pScene;
		// 初期化
		m_pScene = pScene;
		m_pScene->init();
	}
}

void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->draw();
}