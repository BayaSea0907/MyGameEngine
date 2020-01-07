#include "Polygon.h"


CPolygon::CPolygon()
{
}


CPolygon::~CPolygon()
{
}

HRESULT CPolygon::init(
	HWND _hWnd,
	ID3D11Device*	_pDevice,
	ID3D11DeviceContext*	_pDeviceContext,
	IDXGISwapChain*	_pSwapChain,
	ID3D11RenderTargetView*	_pRenderTargetView)
{
	//m_vColor = { 1, 0, 1 };
	
	// シェーダーをセット
	SetShader(_pDevice, _pDeviceContext, L"Simple.hlsl");

	float vtx = 0.5f;
	//バーテックスバッファ作成
	SimpleVertex vertices[] = {
		D3DXVECTOR3(-vtx, -vtx, 0),	D3DXVECTOR2(0, 1),		//頂点1
		D3DXVECTOR3(-vtx, vtx, 0),	D3DXVECTOR2(0, 0),		//頂点2
		D3DXVECTOR3(vtx, -vtx, 0),	D3DXVECTOR2(1, 1),		//頂点3
		D3DXVECTOR3(vtx, vtx, 0),	D3DXVECTOR2(1, 0)		//頂点4
	};

	VerticsCount = sizeof(vertices) / sizeof(vertices[0]);


	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * VerticsCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
		return E_FAIL;

	//バーテックスバッファをセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//プリミティブ・トポロジーをセット
	_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* pIr = NULL;
	_pDevice->CreateRasterizerState(&rdc, &pIr);
	_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);

	
	//テクスチャ用サンプラ作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);

	if (FAILED(D3DX11CreateShaderResourceViewFromFile(_pDevice, L"sprite.jpg", NULL, NULL, &m_pTexture, NULL)))
	{
		return E_FAIL;
	}
	
	/*
	//コンスタントバッファ作成 ここではディフューズ色を渡す
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SHADER_GLOBAL);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;


	if (FAILED(_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}
	*/

	return S_OK;
}

void CPolygon::Render(ID3D11Device*	_pDevice,
	ID3D11DeviceContext*	_pDeviceContext,
	IDXGISwapChain*	_pSwapChain,
	ID3D11RenderTargetView*	_pRenderTargetView) {
	
	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	//ワールドトランスフォーム（絶対座標変換）
	D3DXMatrixRotationY(&mWorld, 0.0f);
	
	//ビュートランスフォーム（視点座標変換）
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -2.0f);		//カメラ（視点）位置
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	//注視位置
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		//上方位置
	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);
	
	//プロジェクトトランスフォーム(射影変換)
	D3DXMatrixPerspectiveFovLH(&mProj, (FLOAT)D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


	//ワールド・ビュー・プロジェクション行列をシェーダーに渡す
	_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);	//g_mWVPはVertexシェーダ
	_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);	//g_mWVPはVertexシェーダ

	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SHADER_GLOBAL sg;
		sg.mWVP = mWorld * mView * mProj;
		D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
		sg.vDiffuse = D3DXVECTOR4(1, 0, 1, 1);
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_GLOBAL));
		_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}

	//用いるシェーダーの登録	(effectの"テクニック"に相当
	_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	
	_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//プリミティブをレンダリング
	_pDeviceContext->Draw(VerticsCount, 0);
}


void CPolygon::Release(void) {
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);

	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);
}


HRESULT CPolygon::SetShader(ID3D11Device*	_pDevice,
	ID3D11DeviceContext*	_pDeviceContext,
	LPCWSTR _pFileName)
{
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;


	//ブロブからパーテックスシェーダー作成
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader))) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}


	//頂点インプットレイアウト定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//頂点インプットレイアウトを作成
	if (FAILED(_pDevice->CreateInputLayout(layout, numElements,
		pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
		return E_FAIL;

	//頂点インプットレイアウトをセット
	_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//ブロブからピクセルシェーダーを作成
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader))) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	return S_OK;
}