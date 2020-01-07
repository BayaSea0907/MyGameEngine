#pragma once
#include "GameObject.h"

class CRenderComponent : public CComponent
{
public:
	virtual void Rendering();
	virtual void Initialize();
	virtual void Release() override;

	CRenderComponent();
	virtual ~CRenderComponent();
};

