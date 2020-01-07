#include "Clear.h"

CClear::CClear()
{
}


CClear::~CClear()
{
}

GameObject* CClear::GetGameObject()
{
	return NULL;
}

void CClear::Update()
{

}

void CClear::ReleaseGameObject()
{

}

void CClear::Release()
{

}

MySceneState CClear::GetNextSceneState()
{
	return m_eNextSceneState;
}