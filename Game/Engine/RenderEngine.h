/***************************************************

--- 履歴 ---
17/04/23 ファイル/クラス作成

****************************************************/


#pragma once

#include "RenderComponent.h"
#include "Camera.h"
#include "../stdafx.h"
#include <list>
using namespace std;

// レンダリングエンジン
class CRenderEngine
{
protected:
	//表示するオブジェクトのRenderComponentリスト
	//list<CRenderComponent *> RenderCompList;

	//利用するカメラのポインタ
	GCamera* Camera;
public:
	// 初期化
	virtual void Initialize(HWND hWnd_);

	// 描画
	virtual void Rendering(HWND hWnd_);

	// 解放
	virtual void Release();

	// カメラをセット
	void SetCamera(GCamera* sCamera_);

	virtual void InitRenderComp(CComponent* comp_);
	/*
	// コンポーネントリストに追加
	void PushRenderComp(CComponent* rComp_);
	void PushRenderComp(CRenderComponent* rComp_);
	*/
protected:
	// カメラを更新
	virtual void UpdateCamera() = 0;

	// 任意の動的要素の視覚状態を更新
	virtual void UpdateSceneElements() = 0;
	
	// バックバッファにレンダリング
	virtual void RenderScene();
	
	// バック/スワップバッファを入れ替え
	virtual void SwapBuffers() = 0;
	
	// 画面クリア
	virtual void ClearRenderView() = 0;

	// 座標変換
	virtual void TransformMatrix() = 0;
public :
	// コンストラクタ
	CRenderEngine();

	// デストラクタ
	virtual ~CRenderEngine();
};

