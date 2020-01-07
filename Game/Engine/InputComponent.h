/***************************************************
InputComponent.h

--- 履歴 ---
17/05/12 ファイル作成
17/05/12 プロパティ/メソッド定義

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

