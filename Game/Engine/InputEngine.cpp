#include "InputEngine.h"

CInputEngine::CInputEngine()
{
}

CInputEngine::~CInputEngine()
{
}

//--------------------------------------------------
// �L�[�{�[�h�쐬
//--------------------------------------------------
void CInputEngine::CreateKeyboard(HWND hWnd_)
{
}
//--------------------------------------------------
// �}�E�X�쐬
//--------------------------------------------------
void CInputEngine::CreateMouse(HWND hWnd_)
{
}
//--------------------------------------------------
// �W���C�p�b�h�쐬
//--------------------------------------------------
void CInputEngine::CreateJoystick(HWND hWnd_)
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CInputEngine::Initialize()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CInputEngine::Update()
{
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CInputEngine::Release() 
{
}
//--------------------------------------------------
// �L�[�{�[�h���
//--------------------------------------------------
void CInputEngine::ReleaseKeyboard()
{
}
//--------------------------------------------------
// �}�E�X���
//--------------------------------------------------
void CInputEngine::ReleaseMouse()
{
}
//--------------------------------------------------
// �W���C�p�b�h���
//--------------------------------------------------
void CInputEngine::ReleaseJoystick()
{
}

//--------------------------------------------------
// ������Ă��邩
//--------------------------------------------------
bool CInputEngine::GetKeyDown(MyKeyboardCode code_) { return false; }
bool CInputEngine::GetMouseButtonDown(MyMouseCode  code_) { return false; }
bool CInputEngine::GetButtonDown(MyPadCode code_) { return false; }

//--------------------------------------------------
// �����ꂽ�u��
//--------------------------------------------------
bool CInputEngine::GetKeyDownOnce (MyKeyboardCode code_) { return false; }
bool CInputEngine::GetMouseButtonDownOnce    (MyMouseCode    code_) { return false; }
bool CInputEngine::GetButtonDownOnce      (MyPadCode      code_) { return false; }

//--------------------------------------------------
// �����ꂽ�u��	
//--------------------------------------------------
bool CInputEngine::GetKeyUp (MyKeyboardCode  code_) { return false; }
bool CInputEngine::GetMouseButtonUp    (MyMouseCode     code_) { return false; }
bool CInputEngine::GetButtonUp      (MyPadCode       code_) { return false; }

//--------------------------------------------------
// ������Ă��邩
//--------------------------------------------------
bool CInputEngine::GetKeyOff (MyKeyboardCode     code_) { return false; }
bool CInputEngine::GetMouseButtonOff    (MyMouseCode        code_) { return false; }
bool CInputEngine::GetButtonOff      (MyPadCode          code_) {	return false; }

//--------------------------------------------------
// ���X�e�B�b�N�̓��͏���Ԃ�
//--------------------------------------------------
bool CInputEngine::GetStickUp        (MyPadCode          code_) { return false; }
bool CInputEngine::GetStickDown      (MyPadCode          code_) { return false; }
bool CInputEngine::GetStickLeft      (MyPadCode          code_) { return false; }
bool CInputEngine::GetStickRight     (MyPadCode          code_) { return false; }

//--------------------------------------------------
// �}�E�X�z�C�[�������ɉ񂳂ꂽ��
//--------------------------------------------------
bool CInputEngine::GetMouseWheelUp()   { return false; }
bool CInputEngine::GetMouseWheelDown() { return false ;}

//--------------------------------------------------
// �P�t���[���̓��͗�
//--------------------------------------------------
/*
float CInputEngine::GetInputQuantity()
{
	m_pInputDevice->GetInputQuantity();
}
*/
