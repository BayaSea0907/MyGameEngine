/***************************************************
作成者		：小林
ファイル名	：GameManager.h
内容	　　：ゲームのシーンを管理するクラス

--- 履歴 ---
17/05/04 ファイル作成				  // 小林
****************************************************/
#pragma once
#include "../stdafx.h"
#include "../Engine/GameEngine.h"
#include "MySceneState.h"
#include "Stage/Stage.h"
#include "Title/Title.h"
#include "Load/Load.h"
#include "GameOver/GameOver.h"
#include "Clear/Clear.h"

class CGameManager
{
private:
	CBaseScene* m_pCurrentrScene;
	CBaseScene* m_pNextScene;
	CBaseScene* m_pLoadScene;		// ロード画面用
	MySceneState m_eNextSceneState;
	
	CGameEngine* m_pGameEngine;

public:
	CGameManager();
	~CGameManager();

	void Initialize(CGameEngine* gameEngine_);
	void Update();
	void Release();
};

