/***************************************************
ファイル名	：SceneEngine.h
内容	　　：ゲームを管理するためのクラス

--- 履歴 ---
17/05/04 ファイル作成
17/05/04 プロパティ/メソッド定義
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
	int loadWaitFrame;					 // 仮

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

