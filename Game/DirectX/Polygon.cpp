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
	
	// �V�F�[�_�[���Z�b�g
	SetShader(_pDevice, _pDeviceContext, L"Simple.hlsl");

	float vtx = 0.5f;
	//�o�[�e�b�N�X�o�b�t�@�쐬
	SimpleVertex vertices[] = {
		D3DXVECTOR3(-vtx, -vtx, 0),	D3DXVECTOR2(0, 1),		//���_1
		D3DXVECTOR3(-vtx, vtx, 0),	D3DXVECTOR2(0, 0),		//���_2
		D3DXVECTOR3(vtx, -vtx, 0),	D3DXVECTOR2(1, 1),		//���_3
		D3DXVECTOR3(vtx, vtx, 0),	D3DXVECTOR2(1, 0)		//���_4
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

	//�o�[�e�b�N�X�o�b�t�@���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* pIr = NULL;
	_pDevice->CreateRasterizerState(&rdc, &pIr);
	_pDeviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);

	
	//�e�N�X�`���p�T���v���쐬
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
	//�R���X�^���g�o�b�t�@�쐬 �����ł̓f�B�t���[�Y�F��n��
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

	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	D3DXMatrixRotationY(&mWorld, 0.0f);
	
	//�r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -2.0f);		//�J�����i���_�j�ʒu
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	//�����ʒu
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);
	
	//�v���W�F�N�g�g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMatrixPerspectiveFovLH(&mProj, (FLOAT)D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);


	//���[���h�E�r���[�E�v���W�F�N�V�����s����V�F�[�_�[�ɓn��
	_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);	//g_mWVP��Vertex�V�F�[�_
	_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);	//g_mWVP��Vertex�V�F�[�_

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

	//�p����V�F�[�_�[�̓o�^	(effect��"�e�N�j�b�N"�ɑ���
	_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	
	_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�v���~�e�B�u�������_�����O
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


	//�u���u����p�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader))) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}


	//���_�C���v�b�g���C�A�E�g��`
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(_pDevice->CreateInputLayout(layout, numElements,
		pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
		return E_FAIL;

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	_pDeviceContext->IASetInputLayout(m_pVertexLayout);

	//�u���u����s�N�Z���V�F�[�_�[���쐬
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader))) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	return S_OK;
}