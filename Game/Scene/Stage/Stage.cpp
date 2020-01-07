#include "Stage.h"

CStage::CStage()
{
	m_eNextSceneState = SCENE_NONE;
}

CStage::~CStage()
{
}

GameObject* CStage::GetGameObject()
{
	return NULL;
}

vector<GameObject*> CStage::GetGameObjectArray()
{
	return m_pEnemyArray;
}

void CStage::Update()
{
	// Init
	vector < GameObject*> obj;

	for (int i = 0; i < 5; i++)
	{
		obj.push_back(new GameObject());
		// obj[i]->SetTransform("obj.txt");
	}

	for (int i = 0; i < 5; i++)
	{
		obj[i]->Update(0.0f);
	}

}

void CStage::Release()
{

}

void CStage::ReleaseGameObject()
{

}

MySceneState CStage::GetNextSceneState()
{
	return m_eNextSceneState;
}