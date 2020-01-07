/***************************************************
ファイル名	：InputEngine.h
内容			：入力デバイスの操作を行う

--- 履歴 ---
17/04/28 ファイル作成
17/04/29 入力情報の列挙体作成
17/04/30 入力デバイスごとにメソッドを作成
****************************************************/

#pragma once
#include "../stdafx.h"
#include "InputComponent.h"
#include "MyInputCodeList.h"



class CInputEngine
{
private:
public:
	CInputEngine();
	virtual ~CInputEngine();

	virtual void Update();
	virtual void Initialize();

	// デバイス生成
	virtual void CreateKeyboard(HWND hWnd_);
	virtual void CreateMouse(HWND hWnd_);
	virtual void CreateJoystick(HWND hWnd_);

	// デバイス解放
	virtual void Release();
	virtual void ReleaseKeyboard();
	virtual void ReleaseMouse();
	virtual void ReleaseJoystick();

	// キーボード入力判断
	virtual bool GetKeyDown(MyKeyboardCode code_);
	virtual bool GetKeyDownOnce(MyKeyboardCode code_);
	virtual bool GetKeyUp(MyKeyboardCode code_);
	virtual bool GetKeyOff(MyKeyboardCode code_);

	// マウス入力判断
	virtual bool GetMouseButtonDown(MyMouseCode code_);
	virtual bool GetMouseButtonDownOnce(MyMouseCode code_);
	virtual bool GetMouseButtonUp(MyMouseCode code_);
	virtual bool GetMouseButtonOff(MyMouseCode code_);
	virtual bool GetMouseWheelUp();
	virtual bool GetMouseWheelDown();

	// ゲームパッド入力判断
	virtual bool GetButtonDown(MyPadCode code_);
	virtual bool GetButtonDownOnce(MyPadCode code_);
	virtual bool GetButtonUp(MyPadCode code_);
	virtual bool GetButtonOff(MyPadCode code_);

	virtual bool GetStickUp(MyPadCode code_);
	virtual bool GetStickDown(MyPadCode code_);
	virtual bool GetStickLeft(MyPadCode code_);
	virtual bool GetStickRight(MyPadCode code_);

	// float GetInputQuantity(EInputPack action_);
	// タブレットとか増え時はSwipeの様なのも追加する。
};

