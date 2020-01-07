#pragma once
#include "../../stdafx.h"
#include "../../Engine/BaseScene.h"
#include "../MySceneState.h"

class CClear : public CBaseScene
{
private:
	MySceneState m_eNextSceneState = SCENE_NONE;
public:
	CClear();
	~CClear();

	GameObject* GetGameObject();
	// vector<GameObject*> GetGameObjectArray();
	void Update();
	void ReleaseGameObject();
	void Release();
	MySceneState GetNextSceneState();
};

