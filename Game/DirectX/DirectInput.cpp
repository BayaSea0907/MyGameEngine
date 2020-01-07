#include "DirectInput.h"

CDirectInput::CDirectInput()
{
}

CDirectInput::~CDirectInput()
{
}

//--------------------------------------------------
// ライブラリ初期化と生成
//--------------------------------------------------
void CDirectInput::Initialize()
{
	m_lpDI = NULL;
	m_lpKeyboard = NULL;
	m_lpMouse = NULL;
	m_lpJoystick = NULL;

	ZeroMemory(&m_mouseCurrentState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_mousePrevState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_joystickCurrentState, sizeof(DIJOYSTATE));
	ZeroMemory(&m_joystickPrevState, sizeof(DIJOYSTATE));
	ZeroMemory(&m_keyboardCurrentState, sizeof(BYTE) * DI_KEYBOARD_BUFFER_SIZE);

	// DirectInputDeviceの作成
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_lpDI, NULL);
}

//--------------------------------------------------
// キーボードの生成
//--------------------------------------------------
void CDirectInput::CreateKeyboard(HWND hWnd_)
{
	// デバイスの作成
	m_lpDI->CreateDevice(GUID_SysKeyboard, &m_lpKeyboard, NULL);

	if (m_lpKeyboard != NULL)
	{
		// データ形式を設定
		m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);

		// 協調レベルの設定 
		m_lpKeyboard->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		// 更新
		m_lpKeyboard->Acquire();
	}
}

//--------------------------------------------------
// マウス生成
//--------------------------------------------------
void CDirectInput::CreateMouse(HWND hWnd_)
{
	// デバイスの作成
	m_lpDI->CreateDevice(GUID_SysMouse, &m_lpMouse, NULL);

	if (m_lpMouse != NULL)
	{
		// データ形式を設定
		m_lpMouse->SetDataFormat(&c_dfDIMouse);

		// モードを設定（フォアグラウンド＆非排他モード）
		m_lpMouse->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		// デバイスの設定
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_ABS;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS ）DIPROPAXISMODE_REL		<<<<<<<<<<<<<<<<<<<<<<<<<

		m_lpMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

		//更新
		m_lpMouse->Acquire();
	}
}

//--------------------------------------------------
// ゲームパッドの生成
//--------------------------------------------------
void CDirectInput::CreateJoystick(HWND hWnd_)
{
	// デバイスの作成
	m_lpDI->CreateDevice(GUID_Joystick, &m_lpJoystick, NULL);

	if (m_lpJoystick != NULL)
	{
		// データ形式を設定
		m_lpJoystick->SetDataFormat(&c_dfDIJoystick);

		// 強調レベルの設定
		m_lpJoystick->SetCooperativeLevel(hWnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		// スティックの範囲を指定
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_DEVICE;
		diprg.diph.dwObj = 0;
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		m_lpJoystick->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 更新
		m_lpJoystick->Acquire();
	}
}

//----------------------------------------------------------
// ライブラリの更新
//----------------------------------------------------------
void CDirectInput::Update()
{
	CheckInputComponent();

	UpdateKeyboard();
	UpdateMouse();
	UpdateJoystick();
}
//--------------------------------------------------
// キーボードの更新
//--------------------------------------------------
void CDirectInput::UpdateKeyboard()
{
	if (!IsKeyboardConected()) return;

	// デバイスが取得できるまで更新
	if (FAILED(m_lpKeyboard->Poll()))
	{
		while (m_lpKeyboard->Acquire() == DIERR_INPUTLOST);
	}
	else m_lpKeyboard->Acquire();

	// 入力情報のバックアップ
	memcpy(&m_keyboardPrevState, &m_keyboardCurrentState, sizeof(byte) * DI_KEYBOARD_BUFFER_SIZE);

	// 入力情報を更新
	m_lpKeyboard->GetDeviceState(sizeof(byte) * DI_KEYBOARD_BUFFER_SIZE, &m_keyboardCurrentState);	
	for (int i = 0; i < DI_KEYBOARD_BUFFER_SIZE; i++)
	{
		if (m_keyboardCurrentState[i] || m_keyboardKeepFrame[i] == -1)
		{
			m_keyboardKeepFrame[i]++;
		}
		else if (m_keyboardKeepFrame[i] > 0)
		{
			m_keyboardKeepFrame[i] = -1;
		}
	}
}

//--------------------------------------------------
// マウスの更新
//--------------------------------------------------
void CDirectInput::UpdateMouse()
{
	if (!IsMouseConected()) return;

	// デバイスが取得できるまで更新
	if (FAILED(m_lpMouse->Poll()))
	{
		while (m_lpMouse->Acquire() == DIERR_INPUTLOST);
	}
	else m_lpMouse->Acquire();

	// 入力情報のバックアップ
	memcpy(&m_mousePrevState, &m_mouseCurrentState, sizeof(DIMOUSESTATE));

	// 入力情報を更新
	m_lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseCurrentState);

	for (int i = 0; i < DI_MOUSE1_BUTTON_SIZE; i++)
	{
		if (m_mouseCurrentState.rgbButtons[i] || m_mouseKeepFrame[i] == -1)
		{
			m_mouseKeepFrame[i]++;
		}
		else if (m_mouseKeepFrame[i] > 0)
		{
			m_mouseKeepFrame[i] = -1;
		}
	}

	// 前フレームからの入力量を記憶
	/*
	m_mouceInputQuantity.x += (FLOAT)(m_mouseCurrentState.lX - m_mousePrevState.lX) / -INPUT_QUANTITY_RATE;
	m_mouceInputQuantity.y += (FLOAT)(m_mouseCurrentState.lY - m_mousePrevState.lY) / -INPUT_QUANTITY_RATE;
	m_mouceInputQuantity.z += (FLOAT)(m_mouseCurrentState.lZ - m_mousePrevState.lZ) / INPUT_QUANTITY_RATE;
	*/
}

//--------------------------------------------------
// ゲームパッドの更新
//--------------------------------------------------
void CDirectInput::UpdateJoystick()
{
	if (!IsJoystickConected()) return;

	// デバイスが取得できるまで更新
	if (FAILED(m_lpJoystick->Poll()))
	{
		while (m_lpJoystick->Acquire() == DIERR_INPUTLOST);
	}
	else m_lpJoystick->Acquire();

	// 入力情報のバックアップ
	memcpy(&m_joystickPrevState, &m_joystickCurrentState, sizeof(DIJOYSTATE));

	// 入力情報を更新
	m_lpJoystick->GetDeviceState(sizeof(DIJOYSTATE), &m_joystickCurrentState);
	for (int i = 0; i < DI_JOYSTICK1_BUTTON_SIZE; i++)
	{
		if (m_joystickCurrentState.rgbButtons[i] || m_joystickKeepFrame[i] == -1)
		{
			m_joystickKeepFrame[i]++;
		}
		else if (m_joystickKeepFrame[i] > 0)
		{
			m_joystickKeepFrame[i] = -1;
		}
	}
	/*
	// 前フレームからの入力量を記憶
	// 左スティック
	m_lStickQuantity.x += (FLOAT)(m_joystickCurrentState.lX - m_joystickPrevState.lX) / -INPUT_QUANTITY_RATE;
	m_lStickQuantity.y += (FLOAT)(m_joystickCurrentState.lY - m_joystickPrevState.lY) / -INPUT_QUANTITY_RATE;
	m_lStickQuantity.z += (FLOAT)(m_joystickCurrentState.lZ - m_joystickPrevState.lZ) / INPUT_QUANTITY_RATE;

	// 右スティック
	m_rStickQuantity.x += (FLOAT)(m_joystickCurrentState.lRx - m_joystickPrevState.lRx) / -INPUT_QUANTITY_RATE;
	m_rStickQuantity.y += (FLOAT)(m_joystickCurrentState.lRy - m_joystickPrevState.lRy) / -INPUT_QUANTITY_RATE;
	m_rStickQuantity.z += (FLOAT)(m_joystickCurrentState.lRz - m_joystickPrevState.lRz) / INPUT_QUANTITY_RATE;
	*/
}

void CDirectInput::CheckInputComponent()
{
	vector<CComponent*> component;
	auto& oList = ObjectList::GetInstance().objectList;
	for (auto obj : oList)
	{
		obj->GetComponent<>(component);
		for (auto comp : component)
			dynamic_cast<CInputComponent*>(comp)->CheckAction();
	}
}

//--------------------------------------------------
// ライブラリ開放
//--------------------------------------------------
void CDirectInput::Release()
{
	ReleaseKeyboard();
	ReleaseMouse();
	ReleaseJoystick();

	// DirectInputDeviceの解放
	SAFE_RELEASE(m_lpDI);
}

//--------------------------------------------------
// キーボードの開放
//--------------------------------------------------
void CDirectInput::ReleaseKeyboard()
{
	if (!IsKeyboardConected()) return;

	m_lpKeyboard->Unacquire();
	SAFE_RELEASE(m_lpKeyboard);
}
//--------------------------------------------------
// マウスの開放
//--------------------------------------------------
void CDirectInput::ReleaseMouse()
{
	if (!IsMouseConected()) return;

	m_lpMouse->Unacquire();
	SAFE_RELEASE(m_lpMouse);
}
//--------------------------------------------------
// ゲームパッドの開放
//--------------------------------------------------
void CDirectInput::ReleaseJoystick()
{
	if (!IsJoystickConected()) return;

	m_lpJoystick->Unacquire();
	SAFE_RELEASE(m_lpJoystick);
}

//--------------------------------------------------
//　入力してるか
//--------------------------------------------------
bool CDirectInput::GetKeyDown (MyKeyboardCode code_) { return m_keyboardKeepFrame[code_] > 0; }
bool CDirectInput::GetButtonDown      (MyPadCode      code_) {	return m_joystickKeepFrame[code_] > 0;}
bool CDirectInput::GetMouseButtonDown    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] > 0; }

//----------------------------------------------------------
// 入力した瞬間か
//----------------------------------------------------------
bool CDirectInput::GetKeyDownOnce (MyKeyboardCode code_) { return m_keyboardKeepFrame[code_] == 1;}
bool CDirectInput::GetButtonDownOnce      (MyPadCode      code_) { return m_joystickKeepFrame[code_] == 1;}
bool CDirectInput::GetMouseButtonDownOnce    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] == 1; }

//----------------------------------------------------------
//　入力をやめた瞬間か
//----------------------------------------------------------
bool CDirectInput::GetKeyUp (MyKeyboardCode code_) { return m_keyboardKeepFrame[code_] == -1;}
bool CDirectInput::GetButtonUp      (MyPadCode      code_) { return m_joystickKeepFrame[code_] == -1;}
bool CDirectInput::GetMouseButtonUp    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] == -1; }

//----------------------------------------------------------
//　入力をやめてるか
//----------------------------------------------------------
bool CDirectInput::GetKeyOff (MyKeyboardCode code_) {	return m_keyboardKeepFrame[code_] == 0;}
bool CDirectInput::GetButtonOff      (MyPadCode      code_) {	return m_joystickKeepFrame[code_] == 0;}
bool CDirectInput::GetMouseButtonOff    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] == 0; }


//--------------------------------------------------
// スティックの入力情報を返す
//--------------------------------------------------

// 上
bool CDirectInput::GetStickUp(MyPadCode code_)	
{
	if      (code_ == ELECOM_R_STICK) return (m_joystickCurrentState.lRy < -100);
	else if (code_ == ELECOM_L_STICK)  return (m_joystickCurrentState.lY < -100);
	return false;
}

// 下
bool CDirectInput::GetStickDown(MyPadCode code_)
{
	if      (code_ == ELECOM_R_STICK)	return (m_joystickCurrentState.lRy > 100);
	else if (code_ == ELECOM_L_STICK)	return (m_joystickCurrentState.lY  > 100);
	return false;
}

// 右
bool CDirectInput::GetStickRight(MyPadCode code_)
{
	if      (code_ == ELECOM_R_STICK)	return (m_joystickCurrentState.lRx > 100);
	else if (code_ == ELECOM_L_STICK)	return (m_joystickCurrentState.lX  > 100);
	return false;
}

// 左
bool CDirectInput::GetStickLeft(MyPadCode code_)
{
	if      (code_ == ELECOM_R_STICK)	return (m_joystickCurrentState.lRx < -100);
	else if (code_ == ELECOM_L_STICK)	return (m_joystickCurrentState.lX  < -100);
	return false;
}


//--------------------------------------------------
// マウスホイールが上に回された時
//--------------------------------------------------
bool CDirectInput::GetMouseWheelUp()
{
	return (m_mouseCurrentState.lZ - m_mousePrevState.lZ) > 0;
}
//--------------------------------------------------
// マウスホイールが下に回された時
//--------------------------------------------------
bool CDirectInput::GetMouseWheelDown()
{
	return (m_mouseCurrentState.lZ - m_mousePrevState.lZ) < 0;
}

//---------------------------------------------------------
// DirectInputDeviceがあるか
//---------------------------------------------------------
bool CDirectInput::CheckInputDeviceConectted()
{
	return m_lpDI != NULL;
}

//---------------------------------------------------------
// キーボードがあるか
//---------------------------------------------------------
bool CDirectInput::IsKeyboardConected()
{
	return m_lpKeyboard != NULL;
}

//---------------------------------------------------------
// マウスがあるか
//---------------------------------------------------------
bool CDirectInput::IsMouseConected()
{
	return m_lpMouse != NULL;
}

//---------------------------------------------------------
// ゲームパッドがあるか
//---------------------------------------------------------
bool CDirectInput::IsJoystickConected()
{
	return m_lpJoystick != NULL;
}