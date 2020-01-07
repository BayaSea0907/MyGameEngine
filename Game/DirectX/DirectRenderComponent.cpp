#include "DirectRenderComponent.h"


DirectRenderComponent::DirectRenderComponent()
{
}


DirectRenderComponent::~DirectRenderComponent()
{
}

void DirectRenderComponent::Rendering(ID3D11DeviceContext*	_pDeviceContext,
	D3DXMATRIX _ViewMat,
	D3DXMATRIX _ProjMat)
{

	TransformToMatrix();

	//ワールド・ビュー・プロジェクション行列をシェーダーに渡す
	//ディフューズカラーをシェーダーに渡す	
	_pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);//g_mWVPはVertexシェーダーで使用するので、"VSSet"　（PSsetではない）
	_pDeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);//g_vDiffuseはPixelシェーダーで使用するので、"PSSet"　（VSsetではない）

	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(_pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		SHADER_GLOBAL sg;
		sg.mWVP = WorldMatrix * _ViewMat * _ProjMat;
		D3DXMatrixTranspose(&sg.mWVP, &sg.mWVP);
		sg.vDiffuse = D3DXVECTOR4(1, 0, 1, 1);
		memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SHADER_GLOBAL));
		_pDeviceContext->Unmap(pConstantBuffer, 0);
	}
	
	// 頂点バッファを登録
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	//使用するシェーダーの登録　（effectの”テクニック”に相当）
	_pDeviceContext->VSSetShader(pVertexShader, NULL, 0);
	_pDeviceContext->PSSetShader(pPixelShader, NULL, 0);

	//テクスチャーをシェーダーに渡す
	_pDeviceContext->PSSetSamplers(0, 1, &pSampleLinear);
	_pDeviceContext->PSSetShaderResources(0, 1, &pTexture);

	_pDeviceContext->Draw(VerticsCount, 0);
}

void DirectRenderComponent::Initialize(ID3D11Device* pDevice_, ID3D11DeviceContext*	pDeviceContext_)
{
	// シェーダーをセット
	SetShader(pDevice_, pDeviceContext_, L"Simple.hlsl");

	float vtx = 50.f;
	//バーテックスバッファ作成
	SimpleVertex vertices[] = {
		D3DXVECTOR3(-vtx, -vtx, 0),	D3DXVECTOR2(0, 1),		//頂点1
		D3DXVECTOR3(-vtx, vtx, 0),	D3DXVECTOR2(0, 0),		//頂点2
		D3DXVECTOR3(vtx, -vtx, 0),	D3DXVECTOR2(1, 1),		//頂点3
		D3DXVECTOR3(vtx, vtx, 0),		D3DXVECTOR2(1, 0)	//頂点4
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
	if (FAILED(pDevice_->CreateBuffer(&bd, &InitData, &pVertexBuffer)))
		throw runtime_error("DirectRenderComponent::Initialize : Create failed.");


	//バーテックスバッファをセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	pDeviceContext_->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	//プリミティブ・トポロジーをセット
	pDeviceContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	CreateBlendState(pDevice_, pDeviceContext_);
	CreateRasterizerState(pDevice_, pDeviceContext_);
	
	//テクスチャ用サンプラ作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pDevice_->CreateSamplerState(&SamDesc, &pSampleLinear);

	if (FAILED(D3DX11CreateShaderResourceViewFromFile(pDevice_, L"sprite.jpg", NULL, NULL, &pTexture, NULL)))
	{
		throw runtime_error("DirectRenderComponent::Initialize : Load failed.");
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SHADER_GLOBAL);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(pDevice_->CreateBuffer(&cb, NULL, &pConstantBuffer)))
	{
		throw runtime_error("DirectRender::Initialize() : Failed create buffer.");
	}
}


// ブレンドステート作成
void DirectRenderComponent::CreateBlendState(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_)
{
	// ブレンドステートの設定
	ID3D11BlendState* pBlendState = NULL;
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.IndependentBlendEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	pDevice_->CreateBlendState(&BlendDesc, &pBlendState);
	pDeviceContext_->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
}

// ラスタライザステート作成
void DirectRenderComponent::CreateRasterizerState(ID3D11Device* pDevice_, ID3D11DeviceContext*	pDeviceContext_)
{
	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* pIr = NULL;
	pDevice_->CreateRasterizerState(&rdc, &pIr);
	pDeviceContext_->RSSetState(pIr);
	SAFE_RELEASE(pIr);
}

void DirectRenderComponent::Release()
{
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pSampleLinear);
	SAFE_RELEASE(pConstantBuffer);
	SAFE_RELEASE(pPixelShader);
	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pVertexBuffer);
	SAFE_RELEASE(pVertexLayout);
}

void DirectRenderComponent::SetShader(ID3D11Device*	_pDevice,
	ID3D11DeviceContext*	_pDeviceContext,
	LPCWSTR _pFileName)
{
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;


	//ブロブからパーテックスシェーダー作成
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		throw runtime_error("DirectRenderComponent::SetShader : Load failed.");
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(), NULL, &pVertexShader))) {
		SAFE_RELEASE(pCompiledShader);
		throw runtime_error("DirectRenderComponent::SetShader : failed.");
	}


	//頂点インプットレイアウト定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//頂点インプットレイアウトを作成
	if (FAILED(_pDevice->CreateInputLayout(layout, numElements,
		pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &pVertexLayout)))
		throw runtime_error("DirectRenderComponent::SetShader : error.");

	//頂点インプットレイアウトをセット
	_pDeviceContext->IASetInputLayout(pVertexLayout);

	//ブロブからピクセルシェーダーを作成
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		throw runtime_error("DirectRenderComponent::SetShader : Load failed.");
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(), NULL, &pPixelShader))) {
		SAFE_RELEASE(pCompiledShader);
		throw runtime_error("DirectRenderComponent::SetShader : failed.");

	}
	SAFE_RELEASE(pCompiledShader);

}

void DirectRenderComponent::TransformToMatrix()
{
	FTransform& tf = gameObject->Transform;
	WorldMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	/* 回転行列用メモ
	D3DXMATRIX rotx = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(), sin(), 0.0f,
		0.0f, -sin(), cos(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	*/
	/*
	D3DXMATRIX roty = {
	cos(), 0.0f, -sin(), 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	sin(), 0.0f, cos(), 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	};
	*/
	/*
	D3DXMATRIX rotz = {
	cos(), sin(), 0.0f, 0.0f,
	-sin(), cos(), 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	};
	*/

	// マトリックスの掛け算は処理量が多いので
	// 直接入力で済むところは直接入力で済ませる
	//	WorldMatrix = scale * rotz * roty * rotx * pos;		// 掛け算にした場合の計算式

	// 回転実装後に下記の計算式を非コメント状態にしてください。
	//	WorldMatrix = rotz * roty * rotx;
	int i;
	for (i = 0; i < 3; i++) {
		WorldMatrix.m[0][i] *= tf.Scale.x;
	}
	for (i = 0; i < 3; i++) {
		WorldMatrix.m[1][i] *= tf.Scale.y;
	}
	for (i = 0; i < 3; i++) {
		WorldMatrix.m[2][i] *= tf.Scale.z;
	}
	WorldMatrix.m[3][0] = tf.Position.x;
	WorldMatrix.m[3][1] = tf.Position.y;
	WorldMatrix.m[3][2] = tf.Position.z;
}

// EOF