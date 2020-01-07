#include "GameManager.h"

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}
void CGameManager::Initialize(CGameEngine* gameEngine_)
{
	m_pNextScene = NULL;
	m_pLoadScene = NULL;
	m_eNextSceneState = SCENE_NONE;

	m_pGameEngine = gameEngine_;

	m_pLoadScene = new CLoad();	
	m_pCurrentrScene = new CTitle();

	m_pGameEngine->SceneEngine->SetCurrentScene(m_pCurrentrScene);
	m_pGameEngine->SceneEngine->SetLoadScene(m_pLoadScene);
}

void CGameManager::Update()
{
	m_eNextSceneState = m_pCurrentrScene->GetNextSceneState();

	switch (m_eNextSceneState)
	{
	case SCENE_TITLE:
		m_pNextScene = new CTitle();
		m_pGameEngine->SceneEngine->SetNextScene(m_pNextScene);
		break;

	case SCENE_STAGE:
		m_pNextScene = new CStage();
		m_pGameEngine->SceneEngine->SetNextScene(m_pNextScene);
		break;

	case SCENE_CLEAR:
		m_pNextScene = new CClear();
		m_pGameEngine->SceneEngine->SetNextScene(m_pNextScene);
		break;

	case SCENE_GAME_OVER:
		m_pNextScene = new CGameOver();
		m_pGameEngine->SceneEngine->SetNextScene(m_pNextScene);
		break;

	case SCENE_NONE:
		break;
	}
}

void CGameManager::Release()
{

}