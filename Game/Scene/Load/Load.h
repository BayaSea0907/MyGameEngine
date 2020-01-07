#pragma once
#include "../../stdafx.h"
#include "../../Engine/BaseScene.h"
#include "../MySceneState.h"

class CLoad : public CBaseScene
{
private:
	MySceneState m_eNextSceneState = SCENE_NONE;
public:
	CLoad();
	~CLoad();

	GameObject* GetGameObject();
	// vector<GameObject*> GetGameObjectArray();
	void Update();
	void ReleaseGameObject();
	void Release();
	MySceneState GetNextSceneState();
};

