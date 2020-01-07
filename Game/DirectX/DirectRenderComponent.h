#pragma once
#include "../stdafx.h"
#include "../Engine/RenderComponent.h"

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

class DirectRenderComponent : public CRenderComponent
{
protected:
	ID3D11InputLayout*	pVertexLayout = NULL;
	ID3D11Buffer*		pVertexBuffer = NULL;

	ID3D11VertexShader*	pVertexShader = NULL;		// effectではなく、個別にバーテックスシェーダー
	ID3D11PixelShader*	pPixelShader = NULL;		// effextではなく、個別にピクセルシェーダー

	ID3D11Buffer*		pConstantBuffer = NULL;	//アプリ←→シェーダー架け橋　ディフューズを渡す為のコンスタンとバッファ
	D3DXVECTOR3			Color;					//(1, 0, 1);	//紫色

	ID3D11SamplerState*	pSampleLinear = NULL;
	ID3D11ShaderResourceView*	pTexture = NULL;

	D3DXMATRIX WorldMatrix;

	int VerticsCount;

	void CreateBlendState(ID3D11Device* pDevice_, ID3D11DeviceContext*	pDeviceContext_);
	void CreateRasterizerState(ID3D11Device* pDevice_, ID3D11DeviceContext*	pDeviceContext_);

public:
	void Rendering(ID3D11DeviceContext*	_pDeviceContext,
		D3DXMATRIX _ViewMat,
		D3DXMATRIX _ProjMat);
	void Initialize(ID3D11Device*	_pDevice,
		ID3D11DeviceContext*	_pDeviceContext);

	void Release() override;
protected:
	virtual void SetShader(ID3D11Device*	_pDevice,
		ID3D11DeviceContext*	_pDeviceContext,
		LPCWSTR _pFileName);
	void TransformToMatrix();
public:
	DirectRenderComponent();
	~DirectRenderComponent();
};

