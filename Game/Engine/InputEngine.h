/***************************************************
�t�@�C����	�FInputEngine.h
���e			�F���̓f�o�C�X�̑�����s��

--- ���� ---
17/04/28 �t�@�C���쐬
17/04/29 ���͏��̗񋓑̍쐬
17/04/30 ���̓f�o�C�X���ƂɃ��\�b�h���쐬
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

	// �f�o�C�X����
	virtual void CreateKeyboard(HWND hWnd_);
	virtual void CreateMouse(HWND hWnd_);
	virtual void CreateJoystick(HWND hWnd_);

	// �f�o�C�X���
	virtual void Release();
	virtual void ReleaseKeyboard();
	virtual void ReleaseMouse();
	virtual void ReleaseJoystick();

	// �L�[�{�[�h���͔��f
	virtual bool GetKeyDown(MyKeyboardCode code_);
	virtual bool GetKeyDownOnce(MyKeyboardCode code_);
	virtual bool GetKeyUp(MyKeyboardCode code_);
	virtual bool GetKeyOff(MyKeyboardCode code_);

	// �}�E�X���͔��f
	virtual bool GetMouseButtonDown(MyMouseCode code_);
	virtual bool GetMouseButtonDownOnce(MyMouseCode code_);
	virtual bool GetMouseButtonUp(MyMouseCode code_);
	virtual bool GetMouseButtonOff(MyMouseCode code_);
	virtual bool GetMouseWheelUp();
	virtual bool GetMouseWheelDown();

	// �Q�[���p�b�h���͔��f
	virtual bool GetButtonDown(MyPadCode code_);
	virtual bool GetButtonDownOnce(MyPadCode code_);
	virtual bool GetButtonUp(MyPadCode code_);
	virtual bool GetButtonOff(MyPadCode code_);

	virtual bool GetStickUp(MyPadCode code_);
	virtual bool GetStickDown(MyPadCode code_);
	virtual bool GetStickLeft(MyPadCode code_);
	virtual bool GetStickRight(MyPadCode code_);

	// float GetInputQuantity(EInputPack action_);
	// �^�u���b�g�Ƃ���������Swipe�̗l�Ȃ̂��ǉ�����B
};

