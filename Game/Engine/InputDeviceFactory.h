/***************************************************
作成者			：15CU0210 小林 裕樹
ファイル名		：InputDeviceFactory.h
内容			：入力デバイス用基本クラス。
				　このクラスを継承してエンジンに渡す。

--- 履歴 ---
17/04/28 ファイル作成						// 小林
17/04/29 入力デバイスごとにメソッドを作成	// 小林
****************************************************/
#pragma once
#include "../stdafx.h"
#include "MyInputCodeList.h"

class CInputDeviceFactory
{
private:
	virtual void Init() = 0;
public:
	CInputDeviceFactory();
	virtual ~CInputDeviceFactory();

	virtual void Update() = 0;

	// 生成
	virtual void CreateKeyboard() = 0;
	virtual void CreateMouse() = 0;
	virtual void CreateJoystick() = 0;

	// 解放
	virtual void Release() = 0;
	virtual void ReleaseKeyboard() = 0;
	virtual void ReleaseMouse() = 0;
	virtual void ReleaseJoystick() = 0;

	// キーボード入力判断
	virtual bool GetKeyDown(MyKeyboardCode code_) = 0;
	virtual bool GetKeyDownOnce(MyKeyboardCode code_) = 0;
	virtual bool GetKeyUp(MyKeyboardCode code_) = 0;
	virtual bool GetKeyOff(MyKeyboardCode code_) = 0;

	// マウス入力判断
	virtual bool GetMouseButtonDown(MyMouseCode code_) = 0;
	virtual bool GetMouseButtonDownOnce(MyMouseCode code_) = 0;
	virtual bool GetMouseButtonUp(MyMouseCode code_) = 0;
	virtual bool GetMouseButtonOff(MyMouseCode code_) = 0;
	virtual bool GetMouseWheelUp() = 0;
	virtual bool GetMouseWheelDown() = 0;

	// ゲームパッド入力判断
	virtual bool GetButtonDown(MyPadCode code_) = 0;
	virtual bool GetButtonDownOnce(MyPadCode code_) = 0;
	virtual bool GetButtonUp(MyPadCode code_) = 0;
	virtual bool GetButtonOff(MyPadCode code_) = 0;

	virtual bool GetStickUp(MyPadCode code_) = 0;
	virtual bool GetStickDown(MyPadCode code_) = 0;
	virtual bool GetStickLeft(MyPadCode code_) = 0;
	virtual bool GetStickRight(MyPadCode code_) = 0;

	// 入力量取得用
	virtual float GetInputQuantity() = 0;
};
