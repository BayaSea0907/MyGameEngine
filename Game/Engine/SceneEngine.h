/***************************************************
�t�@�C����	�FSceneEngine.h
���e	�@�@�F�Q�[�����Ǘ����邽�߂̃N���X

--- ���� ---
17/05/04 �t�@�C���쐬
17/05/04 �v���p�e�B/���\�b�h��`
****************************************************/
#pragma once
#include "../stdafx.h"
#include "BaseScene.h"

class CSceneEngine
{
private:
	CBaseScene* m_pCurrentScene;
	CBaseScene* m_pNextScene;
	CBaseScene* m_pLoadScene;
	int loadWaitFrame;					 // ��

	void Loading();
	void SetGameObjectToWorld(CBaseScene* scene_);
public:
	CSceneEngine();
	~CSceneEngine();

	void Initialize();
	void SetCurrentScene(CBaseScene* next_);
	void SetNextScene(CBaseScene* next_);
	void SetLoadScene(CBaseScene* scene_);

	void Update();
	void Release();
};

