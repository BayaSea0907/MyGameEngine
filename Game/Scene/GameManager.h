/***************************************************
�쐬��		�F����
�t�@�C����	�FGameManager.h
���e	�@�@�F�Q�[���̃V�[�����Ǘ�����N���X

--- ���� ---
17/05/04 �t�@�C���쐬				  // ����
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
	CBaseScene* m_pLoadScene;		// ���[�h��ʗp
	MySceneState m_eNextSceneState;
	
	CGameEngine* m_pGameEngine;

public:
	CGameManager();
	~CGameManager();

	void Initialize(CGameEngine* gameEngine_);
	void Update();
	void Release();
};

