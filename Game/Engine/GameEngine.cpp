#include "GameEngine.h"


CGameEngine::CGameEngine()
{
	CollisionEngine = NULL;
	RenderEngine = NULL;
	InputEngine = NULL;
	
}


CGameEngine::~CGameEngine()
{
}

//初期化
void CGameEngine::Initialise(HWND hWnd_)
{
	try {
		if (RenderEngine == NULL) {
			RenderEngine = new DirectRender();
			RenderEngine->Initialize(hWnd_);
		}

		if (CollisionEngine == NULL) {
			CollisionEngine = new CCollisionEngine();
			CollisionEngine->Initialize();
		}

		// Input
		if (InputEngine == NULL) {
			InputEngine = new CDirectInput;
			InputEngine->Initialize();
			InputEngine->CreateJoystick(hWnd_);
			InputEngine->CreateKeyboard(hWnd_);
			InputEngine->CreateMouse(hWnd_);
		}

		// Scene
		// if (SceneEngine == NULL) {
		//	 SceneEngine = new CSceneEngine();
		//	 SceneEngine->Initialize();
		// }

		ObjectList::GetInstance().Initialilze();
		
		nowTime = GetNanoTime(chrono::system_clock::now());
	}
	catch(bad_alloc& err) {
		throw err;
	}

	/*********************  仮にゲームのオブジェクトを生成する  ******************/
	float pos = -1000.0f, scale = 10.0f;
	CComponent* comp;
	auto& oList = ObjectList::GetInstance().objectList;


	oList.push_back(new GameObject);		//
	oList.push_back(new GameObject);		//
	oList.push_back(new GameObject);		//
	for (auto obj : oList) {
		// Render
		comp = new DirectRenderComponent;
		obj->PushComponent(comp);
		RenderEngine->InitRenderComp(comp);

		// Input	仮
		comp = new CInputComponent;
		obj->PushComponent(comp);

		obj->Transform.Position.x = pos = pos + 1000.0f;
		obj->Transform.Scale.x = obj->Transform.Scale.y = obj->Transform.Scale.z = scale;

	}

	GCamera* cmr = new GCamera;
	oList.push_back(cmr);
	cmr->Transform.Position = { 0.0f, 0.0f, -1500.0f };
	cmr->SetMoveSpeed(500.0f);
	cmr->SetTargetPos({ 1000.0f, 100.0f, -2000.0f });
	RenderEngine->SetCamera(cmr);
	/************************************************************************/
}

//更新
void CGameEngine::Update()
{
	try {
		seconds_df beforeTime = nowTime;
		nowTime = (GetNanoTime(chrono::system_clock::now()));
		deltaTime = nowTime - beforeTime;

		if (InputEngine != NULL)
		{
			InputEngine->Update();
		}
		
		/*
		TCHAR str[256];
		_stprintf_s(str, TEXT("%fs/f\n"), (float)(deltaTime.count()));
		OutputDebugString(str);
		*/

		auto& oList = ObjectList::GetInstance().objectList;
		
		for (auto obj : oList)
		{
			obj->Update((float)(deltaTime.count()));
		}

		//Animation
		//Physics
		CollisionEngine->Judge();
		//Audio
		//Render
		if (RenderEngine != NULL) {
			RenderEngine->Rendering(hWnd);
		}
	}
	// 例外処理
	catch (bad_alloc& err)
	{
		_RPTN(_CRT_ERROR, "Bad allocation.\n%s\n", err.what());
		throw err;
	}
	catch (invalid_argument err)
	{
		// 関数の仮引数で不正な値を渡された場合に使用する。
		_RPTN(_CRT_ERROR, "Invalid argument.\n%s\n", err.what());
		throw err;
	}
	catch (runtime_error err)
	{
		// 論理エラーで取りきることのできない実行時エラー。
		_RPTN(_CRT_ERROR, "Runtime error.\n%s\n", err.what());
		throw err;
	}
	catch (domain_error err)
	{
		// 主に数学関連の処理で想定範囲外の値が渡された場合に使用する。
		_RPTN(_CRT_ERROR, "Domain error.\n%s\n", err.what());
		throw err;
	}
	// length_error
	// out_of_range
	// range_error
	// overflow_error
	// underflow_error
	// system_error
	catch (...)
	{
		_RPTN(_CRT_ERROR, "an unexpected error.%s\n", "");
		throw;
	}
}

//解放
void CGameEngine::Release()
{
	auto& oList = ObjectList::GetInstance().objectList;

	for (auto obj : oList)
	{
		obj->Release();
	}

	if (InputEngine != NULL) {
		InputEngine->Release();
		delete InputEngine;
	}

	if (CollisionEngine != NULL) {
		CollisionEngine->Release();
		delete CollisionEngine;
	}

	if (RenderEngine != NULL) {
		RenderEngine->Release();
		delete RenderEngine;
	}
}

seconds_df CGameEngine::GetNanoTime(const chrono::system_clock::time_point tp_)
{
	return chrono::duration_cast<seconds_df>(chrono::duration_cast<microseconds_df>(tp_.time_since_epoch()));
}

// EOF