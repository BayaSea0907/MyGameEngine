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

// ���t���[���s������
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

// �I�[�v�j���O����
void CTitle::Opening()
{
	/*
	if (GameEngine::inputEngine->GetButtonDown(START))
	{
		IsOpeningFinish = true;
	}
	*/
}

// ���j���[����
void CTitle::Menu()
{
	/*
	// ���j���[�I��r������
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
	// ���j���[�I����̏���
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