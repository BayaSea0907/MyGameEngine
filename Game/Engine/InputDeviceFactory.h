/***************************************************
�쐬��			�F15CU0210 ���� �T��
�t�@�C����		�FInputDeviceFactory.h
���e			�F���̓f�o�C�X�p��{�N���X�B
				�@���̃N���X���p�����ăG���W���ɓn���B

--- ���� ---
17/04/28 �t�@�C���쐬						// ����
17/04/29 ���̓f�o�C�X���ƂɃ��\�b�h���쐬	// ����
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

	// ����
	virtual void CreateKeyboard() = 0;
	virtual void CreateMouse() = 0;
	virtual void CreateJoystick() = 0;

	// ���
	virtual void Release() = 0;
	virtual void ReleaseKeyboard() = 0;
	virtual void ReleaseMouse() = 0;
	virtual void ReleaseJoystick() = 0;

	// �L�[�{�[�h���͔��f
	virtual bool GetKeyDown(MyKeyboardCode code_) = 0;
	virtual bool GetKeyDownOnce(MyKeyboardCode code_) = 0;
	virtual bool GetKeyUp(MyKeyboardCode code_) = 0;
	virtual bool GetKeyOff(MyKeyboardCode code_) = 0;

	// �}�E�X���͔��f
	virtual bool GetMouseButtonDown(MyMouseCode code_) = 0;
	virtual bool GetMouseButtonDownOnce(MyMouseCode code_) = 0;
	virtual bool GetMouseButtonUp(MyMouseCode code_) = 0;
	virtual bool GetMouseButtonOff(MyMouseCode code_) = 0;
	virtual bool GetMouseWheelUp() = 0;
	virtual bool GetMouseWheelDown() = 0;

	// �Q�[���p�b�h���͔��f
	virtual bool GetButtonDown(MyPadCode code_) = 0;
	virtual bool GetButtonDownOnce(MyPadCode code_) = 0;
	virtual bool GetButtonUp(MyPadCode code_) = 0;
	virtual bool GetButtonOff(MyPadCode code_) = 0;

	virtual bool GetStickUp(MyPadCode code_) = 0;
	virtual bool GetStickDown(MyPadCode code_) = 0;
	virtual bool GetStickLeft(MyPadCode code_) = 0;
	virtual bool GetStickRight(MyPadCode code_) = 0;

	// ���͗ʎ擾�p
	virtual float GetInputQuantity() = 0;
};
