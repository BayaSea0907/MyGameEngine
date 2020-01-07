#pragma once
#include "../stdafx.h"

//シェーダーに渡す値
struct SHADER_GLOBAL
{
	D3DXMATRIX	mWVP;	//ワールドから射影までの変換行列
	D3DXVECTOR4 vDiffuse;	//デュフューズ色
};

//頂点の構造体
struct SimpleVertex
{
	D3DXVECTOR3 Pos;	// 位置
	D3DXVECTOR2 cTex;	// テクスチャ画像
};

class CPolygon
{
private:
	ID3D11InputLayout*	m_pVertexLayout = NULL;
	ID3D11Buffer*		m_pVertexBuffer = NULL;

	ID3D11VertexShader*	m_pVertexShader = NULL;		// effectではなく、個別にバーテックスシェーダー
	ID3D11PixelShader*	m_pPixelShader  = NULL;		// effextではなく、個別にピクセルシェーダー

	ID3D11Buffer*		m_pConstantBuffer = NULL;	//アプリ←→シェーダー架け橋　ディフューズを渡す為のコンスタンとバッファ
	D3DXVECTOR3			m_vColor;					//(1, 0, 1);	//紫色

	ID3D11SamplerState*	m_pSampleLinear = NULL;
	ID3D11ShaderResourceView*	m_pTexture = NULL;

	int VerticsCount;
public:
	CPolygon();
	~CPolygon();

	HRESULT init(
		HWND _hWnd,
		ID3D11Device*	_pDevice,
		ID3D11DeviceContext*	_pDeviceContext,
		IDXGISwapChain*	_pSwapChain,
		ID3D11RenderTargetView*	_pRenderTargetView);
	void Render(
		ID3D11Device*	_pDevice,
		ID3D11DeviceContext*	_pDeviceContext,
		IDXGISwapChain*	_pSwapChain,
		ID3D11RenderTargetView*	_pRenderTargetView);
	void Release(void);

	HRESULT SetShader(ID3D11Device*	_pDevice,
		ID3D11DeviceContext*	_pDeviceContext,
		LPCWSTR _pFileName);
};

