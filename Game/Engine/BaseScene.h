/***************************************************
�t�@�C����	�FBaseScene.h
���e	�@�@�F�Q�[���̏������������邽�߂̊��N���X�B

--- ���� ---
17/05/01 �t�@�C���쐬
17/05/04 �v���p�e�B/���\�b�h��`
****************************************************/
#pragma once
#include "../stdafx.h"
#include "GameObject.h"

enum MySceneState;

class CBaseScene
{
private:
public:
	CBaseScene();
	virtual ~CBaseScene();

	virtual GameObject* GetGameObject();
	// virtual vector<GameObject*> GetGameObjectArray();
	virtual void Update();
	virtual void ReleaseGameObject();
	virtual void Release();
	virtual MySceneState GetNextSceneState() { return (MySceneState)-1; }
};

