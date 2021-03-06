/***************************************************

--- 履歴 ---
17/04/24 ファイル作成
17/04/30 Initialize(),Release()作成

****************************************************/


#pragma once


#include "CollisionComponent.h"
#include <list>

using namespace std;

class CCollisionEngine
{
	list<CCollisionComponent *> CollisionList;
public:
	void Initialize();
	void Release();

	virtual void Judge();

	CCollisionEngine();
	~CCollisionEngine();
};

