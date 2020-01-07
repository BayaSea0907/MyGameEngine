/***************************************************
ファイル名		：DirectInput.h
内容			：入力デバイス用基本クラス。
　このクラスを継承してエンジンに渡す。

 --- 履歴 ---
 17/04/28 ファイル作成	
 17/04/29 ファクトリークラスを継承して作成
          CALLBACKと、staticを使わないように修正  
 17/04/30 入力中合計フレームの型をintに変更
          途中までbyteだったのでバグが出た。
 ****************************************************/
#pragma once
#pragma warning(disable:4996)

#define DIRECTINPUT_VERSION 0x0800
#define INPUT_QUANTITY_RATE 150
#define DI_KEYBOARD_BUFFER_SIZE 256
#define DI_JOYSTICK1_BUTTON_SIZE 32
#define DI_JOYSTICK2_BUTTON_SIZE 128
#define DI_MOUSE1_BUTTON_SIZE 4
#define DI_MOUSE2_BUTTON_SIZE 8

#include <dInput.h>
#include "../stdafx.h"
#include "../Engine/InputEngine.h"
#include "../Engine/MyInputCodeList.h"
#include "../Engine/InputComponent.h"
#include "../Math.h"
#pragma comment(lib,"dxguid")
#pragma comment(lib,"dInput8")


class CDirectInput : public CInputEngine
{
private:
	// デバイスのポインタ
	LPDIRECTINPUT8			m_lpDI;
	LPDIRECTINPUTDEVICE8	m_lpKeyboard;
	LPDIRECTINPUTDEVICE8	m_lpMouse;
	LPDIRECTINPUTDEVICE8	m_lpJoystick;

	// 現在の入力情報
	DIMOUSESTATE	m_mouseCurrentState;					
	DIJOYSTATE		m_joystickCurrentState;			
	byte			m_keyboardCurrentState[DI_KEYBOARD_BUFFER_SIZE];	
	
	// １フレーム前の入力情報
	DIMOUSESTATE	m_mousePrevState;						
	DIJOYSTATE		m_joystickPrevState;				
	byte			m_keyboardPrevState[DI_KEYBOARD_BUFFER_SIZE];

	// 押されている間の合計フレームを記憶
	int m_joystickKeepFrame[DI_JOYSTICK1_BUTTON_SIZE];
	int m_mouseKeepFrame[DI_JOYSTICK2_BUTTON_SIZE];
	int m_keyboardKeepFrame[DI_KEYBOARD_BUFFER_SIZE];


	// 任意のデバイスを更新
	void UpdateKeyboard();
	void UpdateMouse();
	void UpdateJoystick();

	// デバイスが接続されているかチェック	あればTRUE
	bool IsKeyboardConected();
	bool IsMouseConected();
	bool IsJoystickConected();
	bool CheckInputDeviceConectted();

	FVector m_lStickQuantity     = { 0.0f, 0.0f, 0.0f };
	FVector m_rStickQuantity    = { 0.0f, 0.0f, 0.0f };
	FVector m_mouseInputQuantity         = { 0.0f, 0.0f, 0.0f };

	// １フレームの入力量を取得 未実装
	float GetInputQuantity() { return 0.0f; }

	// InputComponentを探して、入力判断をする
	void CheckInputComponent();			// 仮の名前です
public:
	CDirectInput();
	~CDirectInput();

	void Initialize();
	void Update();
	void Release();

	// 任意のデバイスを作成
	void CreateKeyboard(HWND hWnd_);
	void CreateMouse(HWND hWnd_);
	void CreateJoystick(HWND hWnd_);

	// 任意のデバイスを解放
	void ReleaseKeyboard();
	void ReleaseMouse();
	void ReleaseJoystick();

	// キーボード入力判断
	bool GetKeyDown(MyKeyboardCode code_);
	bool GetKeyDownOnce(MyKeyboardCode code_);
	bool GetKeyUp(MyKeyboardCode code_);
	bool GetKeyOff(MyKeyboardCode code_);

	// マウス入力判断
	bool GetMouseButtonDown(MyMouseCode code_);
	bool GetMouseButtonDownOnce(MyMouseCode code_);
	bool GetMouseButtonUp(MyMouseCode code_);
	bool GetMouseButtonOff(MyMouseCode code_);
	bool GetMouseWheelUp();						
	bool GetMouseWheelDown();						

	// ゲームパッド入力判断
	bool GetButtonDown(MyPadCode code_);
	bool GetButtonDownOnce(MyPadCode code_);
	bool GetButtonUp(MyPadCode code_);
	bool GetButtonOff(MyPadCode code_);

	bool GetStickUp(MyPadCode code_) ;
	bool GetStickDown(MyPadCode code_);
	bool GetStickLeft(MyPadCode code_);
	bool GetStickRight(MyPadCode code_);
};
