/***************************************************
	GameEngine.h

	--- ���� ---
	17/04/20 �t�@�C���쐬
	17/04/21 �v���p�e�B/���\�b�h��`	

****************************************************/

#pragma once


#include <list>
#include <algorithm>
#include <memory>
//#include <mmsystem.h>
#include <locale>
#include <chrono>
#include <Windows.h>

#include "../stdafx.h"
#include "RenderEngine.h"
#include "CollisionEngine.h"
#include "GameObject.h"
#include "InputEngine.h"
//#include "SceneEngine.h"

#include "../DirectX/DirectInput.h"
#include "../DirectX/DirectRender.h"
#include "../DirectX/DirectRenderComponent.h"


//�^��`
typedef unsigned int uint;
typedef unsigned char byte;

// ���Ԓ�`
using microseconds_df = chrono::duration<double, std::ratio<1, 1000000>>;
using seconds_df = chrono::duration<double, std::ratio<1, 1>>;

using namespace std;

class CGameEngine
{
	HWND hWnd;

//	CInputEngine* InputEngine;
	CRenderEngine* RenderEngine;
	CCollisionEngine* CollisionEngine;

	seconds_df nowTime;
	seconds_df deltaTime;
public:
	//CSceneEngine* SceneEngine;			// �̂���private�ɂ��邱��
	CInputEngine* InputEngine;				// ����

	CGameEngine();
	~CGameEngine();

	//������
	void Initialise(HWND hWnd_);

	//�X�V
	void Update();

	//���
	void Release();

private:
	seconds_df GetNanoTime(const chrono::system_clock::time_point tp_);
};

