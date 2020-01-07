/***************************************************

--- —š—ğ ---
17/04/24 ƒtƒ@ƒCƒ‹ì¬
17/04/30 Initialize(),Release()ì¬

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

