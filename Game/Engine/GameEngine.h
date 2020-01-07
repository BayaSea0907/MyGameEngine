/***************************************************
	GameEngine.h

	--- 履歴 ---
	17/04/20 ファイル作成
	17/04/21 プロパティ/メソッド定義	

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


//型定義
typedef unsigned int uint;
typedef unsigned char byte;

// 時間定義
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
	//CSceneEngine* SceneEngine;			// のちにprivateにすること
	CInputEngine* InputEngine;				// 同上

	CGameEngine();
	~CGameEngine();

	//初期化
	void Initialise(HWND hWnd_);

	//更新
	void Update();

	//解放
	void Release();

private:
	seconds_df GetNanoTime(const chrono::system_clock::time_point tp_);
};

