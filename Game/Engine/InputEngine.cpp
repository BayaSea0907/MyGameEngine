#include "InputEngine.h"

CInputEngine::CInputEngine()
{
}

CInputEngine::~CInputEngine()
{
}

//--------------------------------------------------
// キーボード作成
//--------------------------------------------------
void CInputEngine::CreateKeyboard(HWND hWnd_)
{
}
//--------------------------------------------------
// マウス作成
//--------------------------------------------------
void CInputEngine::CreateMouse(HWND hWnd_)
{
}
//--------------------------------------------------
// ジョイパッド作成
//--------------------------------------------------
void CInputEngine::CreateJoystick(HWND hWnd_)
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CInputEngine::Initialize()
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CInputEngine::Update()
{
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CInputEngine::Release() 
{
}
//--------------------------------------------------
// キーボード解放
//--------------------------------------------------
void CInputEngine::ReleaseKeyboard()
{
}
//--------------------------------------------------
// マウス解放
//--------------------------------------------------
void CInputEngine::ReleaseMouse()
{
}
//--------------------------------------------------
// ジョイパッド解放
//--------------------------------------------------
void CInputEngine::ReleaseJoystick()
{
}

//--------------------------------------------------
// 押されているか
//--------------------------------------------------
bool CInputEngine::GetKeyDown(MyKeyboardCode code_) { return false; }
bool CInputEngine::GetMouseButtonDown(MyMouseCode  code_) { return false; }
bool CInputEngine::GetButtonDown(MyPadCode code_) { return false; }

//--------------------------------------------------
// 押された瞬間
//--------------------------------------------------
bool CInputEngine::GetKeyDownOnce (MyKeyboardCode code_) { return false; }
bool CInputEngine::GetMouseButtonDownOnce    (MyMouseCode    code_) { return false; }
bool CInputEngine::GetButtonDownOnce      (MyPadCode      code_) { return false; }

//--------------------------------------------------
// 離された瞬間	
//--------------------------------------------------
bool CInputEngine::GetKeyUp (MyKeyboardCode  code_) { return false; }
bool CInputEngine::GetMouseButtonUp    (MyMouseCode     code_) { return false; }
bool CInputEngine::GetButtonUp      (MyPadCode       code_) { return false; }

//--------------------------------------------------
// 離されているか
//--------------------------------------------------
bool CInputEngine::GetKeyOff (MyKeyboardCode     code_) { return false; }
bool CInputEngine::GetMouseButtonOff    (MyMouseCode        code_) { return false; }
bool CInputEngine::GetButtonOff      (MyPadCode          code_) {	return false; }

//--------------------------------------------------
// 左スティックの入力情報を返す
//--------------------------------------------------
bool CInputEngine::GetStickUp        (MyPadCode          code_) { return false; }
bool CInputEngine::GetStickDown      (MyPadCode          code_) { return false; }
bool CInputEngine::GetStickLeft      (MyPadCode          code_) { return false; }
bool CInputEngine::GetStickRight     (MyPadCode          code_) { return false; }

//--------------------------------------------------
// マウスホイールが下に回された時
//--------------------------------------------------
bool CInputEngine::GetMouseWheelUp()   { return false; }
bool CInputEngine::GetMouseWheelDown() { return false ;}

//--------------------------------------------------
// １フレームの入力量
//--------------------------------------------------
/*
float CInputEngine::GetInputQuantity()
{
	m_pInputDevice->GetInputQuantity();
}
*/
