#include "DirectInput.h"

CDirectInput::CDirectInput()
{
}

CDirectInput::~CDirectInput()
{
}

//--------------------------------------------------
// ���C�u�����������Ɛ���
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

	// DirectInputDevice�̍쐬
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_lpDI, NULL);
}

//--------------------------------------------------
// �L�[�{�[�h�̐���
//--------------------------------------------------
void CDirectInput::CreateKeyboard(HWND hWnd_)
{
	// �f�o�C�X�̍쐬
	m_lpDI->CreateDevice(GUID_SysKeyboard, &m_lpKeyboard, NULL);

	if (m_lpKeyboard != NULL)
	{
		// �f�[�^�`����ݒ�
		m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);

		// �������x���̐ݒ� 
		m_lpKeyboard->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		// �X�V
		m_lpKeyboard->Acquire();
	}
}

//--------------------------------------------------
// �}�E�X����
//--------------------------------------------------
void CDirectInput::CreateMouse(HWND hWnd_)
{
	// �f�o�C�X�̍쐬
	m_lpDI->CreateDevice(GUID_SysMouse, &m_lpMouse, NULL);

	if (m_lpMouse != NULL)
	{
		// �f�[�^�`����ݒ�
		m_lpMouse->SetDataFormat(&c_dfDIMouse);

		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		m_lpMouse->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		// �f�o�C�X�̐ݒ�
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_ABS;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS �jDIPROPAXISMODE_REL		<<<<<<<<<<<<<<<<<<<<<<<<<

		m_lpMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

		//�X�V
		m_lpMouse->Acquire();
	}
}

//--------------------------------------------------
// �Q�[���p�b�h�̐���
//--------------------------------------------------
void CDirectInput::CreateJoystick(HWND hWnd_)
{
	// �f�o�C�X�̍쐬
	m_lpDI->CreateDevice(GUID_Joystick, &m_lpJoystick, NULL);

	if (m_lpJoystick != NULL)
	{
		// �f�[�^�`����ݒ�
		m_lpJoystick->SetDataFormat(&c_dfDIJoystick);

		// �������x���̐ݒ�
		m_lpJoystick->SetCooperativeLevel(hWnd_, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

		// �X�e�B�b�N�͈̔͂��w��
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_DEVICE;
		diprg.diph.dwObj = 0;
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		m_lpJoystick->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �X�V
		m_lpJoystick->Acquire();
	}
}

//----------------------------------------------------------
// ���C�u�����̍X�V
//----------------------------------------------------------
void CDirectInput::Update()
{
	CheckInputComponent();

	UpdateKeyboard();
	UpdateMouse();
	UpdateJoystick();
}
//--------------------------------------------------
// �L�[�{�[�h�̍X�V
//--------------------------------------------------
void CDirectInput::UpdateKeyboard()
{
	if (!IsKeyboardConected()) return;

	// �f�o�C�X���擾�ł���܂ōX�V
	if (FAILED(m_lpKeyboard->Poll()))
	{
		while (m_lpKeyboard->Acquire() == DIERR_INPUTLOST);
	}
	else m_lpKeyboard->Acquire();

	// ���͏��̃o�b�N�A�b�v
	memcpy(&m_keyboardPrevState, &m_keyboardCurrentState, sizeof(byte) * DI_KEYBOARD_BUFFER_SIZE);

	// ���͏����X�V
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
// �}�E�X�̍X�V
//--------------------------------------------------
void CDirectInput::UpdateMouse()
{
	if (!IsMouseConected()) return;

	// �f�o�C�X���擾�ł���܂ōX�V
	if (FAILED(m_lpMouse->Poll()))
	{
		while (m_lpMouse->Acquire() == DIERR_INPUTLOST);
	}
	else m_lpMouse->Acquire();

	// ���͏��̃o�b�N�A�b�v
	memcpy(&m_mousePrevState, &m_mouseCurrentState, sizeof(DIMOUSESTATE));

	// ���͏����X�V
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

	// �O�t���[������̓��͗ʂ��L��
	/*
	m_mouceInputQuantity.x += (FLOAT)(m_mouseCurrentState.lX - m_mousePrevState.lX) / -INPUT_QUANTITY_RATE;
	m_mouceInputQuantity.y += (FLOAT)(m_mouseCurrentState.lY - m_mousePrevState.lY) / -INPUT_QUANTITY_RATE;
	m_mouceInputQuantity.z += (FLOAT)(m_mouseCurrentState.lZ - m_mousePrevState.lZ) / INPUT_QUANTITY_RATE;
	*/
}

//--------------------------------------------------
// �Q�[���p�b�h�̍X�V
//--------------------------------------------------
void CDirectInput::UpdateJoystick()
{
	if (!IsJoystickConected()) return;

	// �f�o�C�X���擾�ł���܂ōX�V
	if (FAILED(m_lpJoystick->Poll()))
	{
		while (m_lpJoystick->Acquire() == DIERR_INPUTLOST);
	}
	else m_lpJoystick->Acquire();

	// ���͏��̃o�b�N�A�b�v
	memcpy(&m_joystickPrevState, &m_joystickCurrentState, sizeof(DIJOYSTATE));

	// ���͏����X�V
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
	// �O�t���[������̓��͗ʂ��L��
	// ���X�e�B�b�N
	m_lStickQuantity.x += (FLOAT)(m_joystickCurrentState.lX - m_joystickPrevState.lX) / -INPUT_QUANTITY_RATE;
	m_lStickQuantity.y += (FLOAT)(m_joystickCurrentState.lY - m_joystickPrevState.lY) / -INPUT_QUANTITY_RATE;
	m_lStickQuantity.z += (FLOAT)(m_joystickCurrentState.lZ - m_joystickPrevState.lZ) / INPUT_QUANTITY_RATE;

	// �E�X�e�B�b�N
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
// ���C�u�����J��
//--------------------------------------------------
void CDirectInput::Release()
{
	ReleaseKeyboard();
	ReleaseMouse();
	ReleaseJoystick();

	// DirectInputDevice�̉��
	SAFE_RELEASE(m_lpDI);
}

//--------------------------------------------------
// �L�[�{�[�h�̊J��
//--------------------------------------------------
void CDirectInput::ReleaseKeyboard()
{
	if (!IsKeyboardConected()) return;

	m_lpKeyboard->Unacquire();
	SAFE_RELEASE(m_lpKeyboard);
}
//--------------------------------------------------
// �}�E�X�̊J��
//--------------------------------------------------
void CDirectInput::ReleaseMouse()
{
	if (!IsMouseConected()) return;

	m_lpMouse->Unacquire();
	SAFE_RELEASE(m_lpMouse);
}
//--------------------------------------------------
// �Q�[���p�b�h�̊J��
//--------------------------------------------------
void CDirectInput::ReleaseJoystick()
{
	if (!IsJoystickConected()) return;

	m_lpJoystick->Unacquire();
	SAFE_RELEASE(m_lpJoystick);
}

//--------------------------------------------------
//�@���͂��Ă邩
//--------------------------------------------------
bool CDirectInput::GetKeyDown (MyKeyboardCode code_) { return m_keyboardKeepFrame[code_] > 0; }
bool CDirectInput::GetButtonDown      (MyPadCode      code_) {	return m_joystickKeepFrame[code_] > 0;}
bool CDirectInput::GetMouseButtonDown    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] > 0; }

//----------------------------------------------------------
// ���͂����u�Ԃ�
//----------------------------------------------------------
bool CDirectInput::GetKeyDownOnce (MyKeyboardCode code_) { return m_keyboardKeepFrame[code_] == 1;}
bool CDirectInput::GetButtonDownOnce      (MyPadCode      code_) { return m_joystickKeepFrame[code_] == 1;}
bool CDirectInput::GetMouseButtonDownOnce    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] == 1; }

//----------------------------------------------------------
//�@���͂���߂��u�Ԃ�
//----------------------------------------------------------
bool CDirectInput::GetKeyUp (MyKeyboardCode code_) { return m_keyboardKeepFrame[code_] == -1;}
bool CDirectInput::GetButtonUp      (MyPadCode      code_) { return m_joystickKeepFrame[code_] == -1;}
bool CDirectInput::GetMouseButtonUp    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] == -1; }

//----------------------------------------------------------
//�@���͂���߂Ă邩
//----------------------------------------------------------
bool CDirectInput::GetKeyOff (MyKeyboardCode code_) {	return m_keyboardKeepFrame[code_] == 0;}
bool CDirectInput::GetButtonOff      (MyPadCode      code_) {	return m_joystickKeepFrame[code_] == 0;}
bool CDirectInput::GetMouseButtonOff    (MyMouseCode    code_) { return m_mouseKeepFrame[code_] == 0; }


//--------------------------------------------------
// �X�e�B�b�N�̓��͏���Ԃ�
//--------------------------------------------------

// ��
bool CDirectInput::GetStickUp(MyPadCode code_)	
{
	if      (code_ == ELECOM_R_STICK) return (m_joystickCurrentState.lRy < -100);
	else if (code_ == ELECOM_L_STICK)  return (m_joystickCurrentState.lY < -100);
	return false;
}

// ��
bool CDirectInput::GetStickDown(MyPadCode code_)
{
	if      (code_ == ELECOM_R_STICK)	return (m_joystickCurrentState.lRy > 100);
	else if (code_ == ELECOM_L_STICK)	return (m_joystickCurrentState.lY  > 100);
	return false;
}

// �E
bool CDirectInput::GetStickRight(MyPadCode code_)
{
	if      (code_ == ELECOM_R_STICK)	return (m_joystickCurrentState.lRx > 100);
	else if (code_ == ELECOM_L_STICK)	return (m_joystickCurrentState.lX  > 100);
	return false;
}

// ��
bool CDirectInput::GetStickLeft(MyPadCode code_)
{
	if      (code_ == ELECOM_R_STICK)	return (m_joystickCurrentState.lRx < -100);
	else if (code_ == ELECOM_L_STICK)	return (m_joystickCurrentState.lX  < -100);
	return false;
}


//--------------------------------------------------
// �}�E�X�z�C�[������ɉ񂳂ꂽ��
//--------------------------------------------------
bool CDirectInput::GetMouseWheelUp()
{
	return (m_mouseCurrentState.lZ - m_mousePrevState.lZ) > 0;
}
//--------------------------------------------------
// �}�E�X�z�C�[�������ɉ񂳂ꂽ��
//--------------------------------------------------
bool CDirectInput::GetMouseWheelDown()
{
	return (m_mouseCurrentState.lZ - m_mousePrevState.lZ) < 0;
}

//---------------------------------------------------------
// DirectInputDevice�����邩
//---------------------------------------------------------
bool CDirectInput::CheckInputDeviceConectted()
{
	return m_lpDI != NULL;
}

//---------------------------------------------------------
// �L�[�{�[�h�����邩
//---------------------------------------------------------
bool CDirectInput::IsKeyboardConected()
{
	return m_lpKeyboard != NULL;
}

//---------------------------------------------------------
// �}�E�X�����邩
//---------------------------------------------------------
bool CDirectInput::IsMouseConected()
{
	return m_lpMouse != NULL;
}

//---------------------------------------------------------
// �Q�[���p�b�h�����邩
//---------------------------------------------------------
bool CDirectInput::IsJoystickConected()
{
	return m_lpJoystick != NULL;
}