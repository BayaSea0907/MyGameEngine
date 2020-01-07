/***************************************************

--- ���� ---
17/04/24 �t�@�C���쐬
17/04/30 Initialize(),Release()�쐬

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

