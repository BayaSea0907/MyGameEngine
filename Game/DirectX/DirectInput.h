/***************************************************
�t�@�C����		�FDirectInput.h
���e			�F���̓f�o�C�X�p��{�N���X�B
�@���̃N���X���p�����ăG���W���ɓn���B

 --- ���� ---
 17/04/28 �t�@�C���쐬	
 17/04/29 �t�@�N�g���[�N���X���p�����č쐬
          CALLBACK�ƁAstatic���g��Ȃ��悤�ɏC��  
 17/04/30 ���͒����v�t���[���̌^��int�ɕύX
          �r���܂�byte�������̂Ńo�O���o���B
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
	// �f�o�C�X�̃|�C���^
	LPDIRECTINPUT8			m_lpDI;
	LPDIRECTINPUTDEVICE8	m_lpKeyboard;
	LPDIRECTINPUTDEVICE8	m_lpMouse;
	LPDIRECTINPUTDEVICE8	m_lpJoystick;

	// ���݂̓��͏��
	DIMOUSESTATE	m_mouseCurrentState;					
	DIJOYSTATE		m_joystickCurrentState;			
	byte			m_keyboardCurrentState[DI_KEYBOARD_BUFFER_SIZE];	
	
	// �P�t���[���O�̓��͏��
	DIMOUSESTATE	m_mousePrevState;						
	DIJOYSTATE		m_joystickPrevState;				
	byte			m_keyboardPrevState[DI_KEYBOARD_BUFFER_SIZE];

	// ������Ă���Ԃ̍��v�t���[�����L��
	int m_joystickKeepFrame[DI_JOYSTICK1_BUTTON_SIZE];
	int m_mouseKeepFrame[DI_JOYSTICK2_BUTTON_SIZE];
	int m_keyboardKeepFrame[DI_KEYBOARD_BUFFER_SIZE];


	// �C�ӂ̃f�o�C�X���X�V
	void UpdateKeyboard();
	void UpdateMouse();
	void UpdateJoystick();

	// �f�o�C�X���ڑ�����Ă��邩�`�F�b�N	�����TRUE
	bool IsKeyboardConected();
	bool IsMouseConected();
	bool IsJoystickConected();
	bool CheckInputDeviceConectted();

	FVector m_lStickQuantity     = { 0.0f, 0.0f, 0.0f };
	FVector m_rStickQuantity    = { 0.0f, 0.0f, 0.0f };
	FVector m_mouseInputQuantity         = { 0.0f, 0.0f, 0.0f };

	// �P�t���[���̓��͗ʂ��擾 ������
	float GetInputQuantity() { return 0.0f; }

	// InputComponent��T���āA���͔��f������
	void CheckInputComponent();			// ���̖��O�ł�
public:
	CDirectInput();
	~CDirectInput();

	void Initialize();
	void Update();
	void Release();

	// �C�ӂ̃f�o�C�X���쐬
	void CreateKeyboard(HWND hWnd_);
	void CreateMouse(HWND hWnd_);
	void CreateJoystick(HWND hWnd_);

	// �C�ӂ̃f�o�C�X�����
	void ReleaseKeyboard();
	void ReleaseMouse();
	void ReleaseJoystick();

	// �L�[�{�[�h���͔��f
	bool GetKeyDown(MyKeyboardCode code_);
	bool GetKeyDownOnce(MyKeyboardCode code_);
	bool GetKeyUp(MyKeyboardCode code_);
	bool GetKeyOff(MyKeyboardCode code_);

	// �}�E�X���͔��f
	bool GetMouseButtonDown(MyMouseCode code_);
	bool GetMouseButtonDownOnce(MyMouseCode code_);
	bool GetMouseButtonUp(MyMouseCode code_);
	bool GetMouseButtonOff(MyMouseCode code_);
	bool GetMouseWheelUp();						
	bool GetMouseWheelDown();						

	// �Q�[���p�b�h���͔��f
	bool GetButtonDown(MyPadCode code_);
	bool GetButtonDownOnce(MyPadCode code_);
	bool GetButtonUp(MyPadCode code_);
	bool GetButtonOff(MyPadCode code_);

	bool GetStickUp(MyPadCode code_) ;
	bool GetStickDown(MyPadCode code_);
	bool GetStickLeft(MyPadCode code_);
	bool GetStickRight(MyPadCode code_);
};
