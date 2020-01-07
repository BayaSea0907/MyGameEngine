#pragma once
#include <vector>
#include "../../stdafx.h"
#include "../../Engine/BaseScene.h"
#include "../MySceneState.h"

class CStage : public CBaseScene
{
private:
	GameObject* m_pPlayer = NULL;
	vector<GameObject*> m_pEnemyArray;
	MySceneState m_eNextSceneState = SCENE_NONE;
public:
	CStage();
	~CStage();

	GameObject* GetGameObject();
	vector<GameObject*> GetGameObjectArray();

	void Update();
	void ReleaseGameObject();
	void Release();
	MySceneState GetNextSceneState();
};

