/***************************************************
作成者		：小林
ファイル名	：Title.h
内容	　　：最初に呼び出すシーン

--- 履歴 ---
17/05/04 ファイル作成				  // 小林
****************************************************/
#pragma once
#include "../../stdafx.h"
#include "../../Engine/BaseScene.h"
#include "../MySceneState.h"

enum MenuState
{
	MENU_NO_SELECT = -1,
	MENU_START,
	MENU_END,
};
class CTitle : public CBaseScene
{
	bool IsOpeningFinish;
	MenuState m_eMenuState;
	MySceneState m_eNextSceneState = SCENE_NONE;

	GameObject* m_pTitle;
	GameObject* m_pMenuStart;
	GameObject* m_pMenuEnd;

public:
	CTitle();
	~CTitle();

	GameObject* GetGameObject();
	// vector<GameObject*> GetGameObjectArray();
	void Update();
	void ReleaseGameObject();
	void Release();
	MySceneState GetNextSceneState();

	void Opening();
	void Menu();
};