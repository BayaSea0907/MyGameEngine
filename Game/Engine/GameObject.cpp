#include "GameObject.h"

ObjectList* ObjectList::instance = NULL;

GameObject::GameObject()
{
//	ComponentList.push_back(new DirectRenderComponent);
}


GameObject::~GameObject()
{
}


void GameObject::Initialize()
{

}

void GameObject::Update(const float DeltaTime)
{
}

void GameObject::Release()
{
	for (auto obj : ComponentList)
	{
		obj->Release();
	}
}

void GameObject::PushComponent(CComponent* comp_)
{
	comp_->Initialize(this);
	ComponentList.push_back(comp_);
}

/*
bool GameObject::GetComponent(const type_info& type_, CComponent** getComp_)
{
	auto itr = find_if(ComponentList.begin(), ComponentList.end(),
		[&type_](CComponent* comp) { return comp->IsType(type_); });
	

	if (itr == ComponentList.end()) {
		return false;
	}
	*getComp_ = *itr;
	return true;
}
*/


/************************************************************************/

CComponent::~CComponent()
{
	gameObject = NULL;
}

void CComponent::Initialize(GameObject* go_)
{
	gameObject = go_;
}

void CComponent::Update(const float deltaTime)
{

}

CComponent* CComponent::GetType()
{
	return this;
}

bool CComponent::IsType(const type_info& type_)
{
	return typeid(*this) == type_;
}

void CComponent::Release()
{

}