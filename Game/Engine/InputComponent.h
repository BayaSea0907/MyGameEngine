/***************************************************
InputComponent.h

--- ���� ---
17/05/12 �t�@�C���쐬
17/05/12 �v���p�e�B/���\�b�h��`

****************************************************/
#include "../stdafx.h"
#include "GameObject.h"

enum InputPatern
{
	OFF = -1,
	ON,
	ONCE,
	RELEASE
};

#pragma once
class CInputComponent : public CComponent
{
private:
public:
	virtual void Initialize() ;
	virtual void Release() ;
	virtual void CheckAction();
	virtual void AddAction(LPCSTR actionName_, MyKeyboardCode code_, InputPatern patern_, (void*));

	CInputComponent();
	virtual ~CInputComponent();
};

