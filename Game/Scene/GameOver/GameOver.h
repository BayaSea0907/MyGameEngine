#pragma once
#include "../../stdafx.h"
#include "../../Engine/BaseScene.h"
#include "../MySceneState.h"

class CGameOver : public CBaseScene
{
private:
	MySceneState m_eNextSceneState = SCENE_NONE;
public:
	CGameOver();
	~CGameOver();

	GameObject* GetGameObject();
	// vector<GameObject*> GetGameObjectArray();
	void Update();
	void ReleaseGameObject();
	void Release();
	MySceneState GetNextSceneState();
};

