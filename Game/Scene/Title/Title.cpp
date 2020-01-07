#include "Title.h"

CTitle::CTitle()
{
	IsOpeningFinish = false;
	m_eMenuState = MENU_NO_SELECT;
	m_eNextSceneState = SCENE_NONE;
}

CTitle::~CTitle()
{
}


GameObject* CTitle::GetGameObject()
{
	return NULL;
}

// 毎フレーム行う処理
void CTitle::Update()
{
	if(IsOpeningFinish)
	{
		Menu();
	} 
	else
	{
		Opening();
	}
}

// オープニング処理
void CTitle::Opening()
{
	/*
	if (GameEngine::inputEngine->GetButtonDown(START))
	{
		IsOpeningFinish = true;
	}
	*/
}

// メニュー処理
void CTitle::Menu()
{
	/*
	// メニュー選択途中処理
	if(m_eMenuState == MENU_NO_SELECT)
	{
		if (GameEngine::inputEngine->GetLStickUp())
		{
			GameEngine::soundEngine->Play(se_select);
			m_eMenuState = MENU_START;
		}
		else if (GameEngine::inputEngine->GetLStickDown())
		{
			GameEngine::soundEngine->Play(se_select);
			m_eMenuState = MENU_END;
		}
	}
	// メニュー選択後の処理
	else if(GameEngine::inputEngine->GetButtonDown(START))
	{
		GameEngine::soundEngine->Play(se_select);
		switch(m_eMenuState)
		{
		case MENU_START:
			m_pNextScene = SCENE_STAGE;
			break;

		case MENU_END:
			m_pNextScene = SCENE_END;
			break;
		}
	}
	*/
}

void CTitle::ReleaseGameObject()
{

}

void CTitle::Release()
{

}

MySceneState CTitle::GetNextSceneState()
{
	return m_eNextSceneState;
}