#pragma once
#include "../Engine/RenderEngine.h"
#include "../stdafx.h"
#include "DirectRenderComponent.h"
//#include "Polygon.h"



class DirectRender : public CRenderEngine
{
private:
	ID3D11Device*			pDevice = NULL;
	ID3D11DeviceContext*	pDeviceContext = NULL;
	IDXGISwapChain*			pSwapChain = NULL;
	ID3D11RenderTargetView* pRenderTargetView = NULL;

	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjMatrix;

	int WindowWidth = 1920;
	int WindowHeight = 1280;
public:
	// 初期化
	void Initialize(HWND _hWnd) override;

	// 描画
	void Rendering(HWND _hWnd) override;
	
	// 解放
	void Release(void) override;

	// コンポーネントの初期化
	// レンダーエンジンから必要な値を渡す
	virtual void InitRenderComp(CComponent* comp_) override;

protected:
	// カメラを更新
	virtual void UpdateCamera() override;

	// 任意の動的要素の視覚状態を更新
	virtual void UpdateSceneElements() override;

	// バックバッファにレンダリング
	virtual void RenderScene() override;

	// バック/スワップバッファを入れ替え
	virtual void SwapBuffers() override;

	// 画面クリア
	virtual void ClearRenderView() override;

	// 座標変換
	virtual void TransformMatrix() override;

public :
	// コンストラクタ
	DirectRender();

	// デストラクタ
	~DirectRender();

};

