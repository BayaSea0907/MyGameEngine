/***************************************************
15CU0210 小林裕樹
GameObject.h


--- 履歴 ---
17/04/20 ファイル作成
17/04/21 プロパティ/メソッド定義

****************************************************/

#pragma once
#include "Transform.h"
#include <list>
#include <vector>
#include <typeinfo>
#include <algorithm>

using namespace std;
class CComponent;
class GameObject;


class ObjectList
{
	static ObjectList* instance;
	
	ObjectList() {}
	~ObjectList() {}
public:	
	list<GameObject*> objectList;

	static ObjectList& GetInstance() {
		return *instance;
	}

	void Initialilze()
	{
		if (instance == NULL)
			instance = new ObjectList;
	}

	void Release(){
		if (instance != NULL)
			delete instance;
	}
};



class GameObject
{
protected:
	//メンバ変数
	list<CComponent *> ComponentList;
public:
	FTransform Transform;

public:
	virtual void Initialize();
	virtual void Update(const float DeltaTime);
	virtual void Release();

	void PushComponent(CComponent *comp_);
	//bool GetComponent(const type_info& type_, CComponent** getComp_);

public:
	template <class Type = CComponent>
	void GetComponent(vector<CComponent*>& GetCompVec_)
	{

		for (auto comp : ComponentList)
		{
			if (dynamic_cast<Type*>(comp) != nullptr)
				GetCompVec_.push_back(comp);
		}
	}

public:
	GameObject();
	~GameObject();
};

class CComponent
{
public:
	GameObject* gameObject;
public:
	CComponent* GetType();
	bool IsType(const type_info& type);
	virtual void Initialize(GameObject* go_);
	virtual void Update(const float deltaTime);
	virtual void Release();

	CComponent(){};
	virtual ~CComponent();
};
