#include "SceneEngine.h"

CSceneEngine::CSceneEngine()
{
}

CSceneEngine::~CSceneEngine()
{
}

void CSceneEngine::Initialize()
{
	m_pCurrentScene = NULL;
	m_pNextScene = NULL;
	m_pLoadScene = NULL;
	loadWaitFrame = 0;
}

// 今すぐ適用したいシーンをセット	ロード画面を挟まないでもいいなら使ってよし
void CSceneEngine::SetCurrentScene(CBaseScene* next_)
{
	if (m_pCurrentScene == NULL)
	{
		m_pCurrentScene = next_;
	}
	// else if (0);
}

// 次に適用したいシーンをセット
void CSceneEngine::SetNextScene(CBaseScene* next_)
{
	if (m_pNextScene == NULL)
	{
		m_pNextScene = next_;
	} 
	// else if ();
}

// シーン移動時に毎回呼び出すシーンをセット
void CSceneEngine::SetLoadScene(CBaseScene* scene_)
{
	if (m_pLoadScene == NULL)
	{
		m_pLoadScene = scene_;
	}
	// else if (0);
}

// オブジェクトリストにシーンが持ってるオブジェクトを渡す
void CSceneEngine::SetGameObjectToWorld(CBaseScene* scene_)
{
	// ここでオブジェクトリストにオブジェクトをセット
	// SetGameObject(scene_->GetGameObject());
}

// 更新
void CSceneEngine::Update()
{
	if (m_pCurrentScene != NULL)
	{
		// m_pCurrentScene->Update();
	} 	
	else	
	{
		Loading();
	}
}

// シーンが移動するごとに、数秒間写す
void CSceneEngine::Loading()
{
	if (loadWaitFrame < 180 && m_pLoadScene != NULL)
	{
		m_pLoadScene->Update();
	}
	else
	{
		SetCurrentScene(m_pNextScene);
		SAFE_RELEASE(m_pNextScene)
	}
}

void CSceneEngine::Release()
{
	SAFE_DELETE(m_pCurrentScene);
	SAFE_DELETE(m_pNextScene);
	SAFE_DELETE(m_pLoadScene);
}