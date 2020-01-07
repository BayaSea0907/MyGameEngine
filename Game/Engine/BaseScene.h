/***************************************************
ファイル名	：BaseScene.h
内容	　　：ゲームの処理を実装するための基底クラス。

--- 履歴 ---
17/05/01 ファイル作成
17/05/04 プロパティ/メソッド定義
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

