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

	//���[���h�E�r���[�E�v���W�F�N�V�����s����V�F�[�_�[�ɓn��
	//�f�B�t���[�Y�J���[���V�F�[�_�[�ɓn��	
	_pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);//g_mWVP��Vertex�V�F�[�_�[�Ŏg�p����̂ŁA"VSSet"�@�iPSset�ł͂Ȃ��j
	_pDeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);//g_vDiffuse��Pixel�V�F�[�_�[�Ŏg�p����̂ŁA"PSSet"�@�iVSset�ł͂Ȃ��j

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
	
	// ���_�o�b�t�@��o�^
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	_pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	//�g�p����V�F�[�_�[�̓o�^�@�ieffect�́h�e�N�j�b�N�h�ɑ����j
	_pDeviceContext->VSSetShader(pVertexShader, NULL, 0);
	_pDeviceContext->PSSetShader(pPixelShader, NULL, 0);

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	_pDeviceContext->PSSetSamplers(0, 1, &pSampleLinear);
	_pDeviceContext->PSSetShaderResources(0, 1, &pTexture);

	_pDeviceContext->Draw(VerticsCount, 0);
}

void DirectRenderComponent::Initialize(ID3D11Device* pDevice_, ID3D11DeviceContext*	pDeviceContext_)
{
	// �V�F�[�_�[���Z�b�g
	SetShader(pDevice_, pDeviceContext_, L"Simple.hlsl");

	float vtx = 50.f;
	//�o�[�e�b�N�X�o�b�t�@�쐬
	SimpleVertex vertices[] = {
		D3DXVECTOR3(-vtx, -vtx, 0),	D3DXVECTOR2(0, 1),		//���_1
		D3DXVECTOR3(-vtx, vtx, 0),	D3DXVECTOR2(0, 0),		//���_2
		D3DXVECTOR3(vtx, -vtx, 0),	D3DXVECTOR2(1, 1),		//���_3
		D3DXVECTOR3(vtx, vtx, 0),		D3DXVECTOR2(1, 0)	//���_4
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


	//�o�[�e�b�N�X�o�b�t�@���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	pDeviceContext_->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	pDeviceContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	CreateBlendState(pDevice_, pDeviceContext_);
	CreateRasterizerState(pDevice_, pDeviceContext_);
	
	//�e�N�X�`���p�T���v���쐬
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

	//�R���X�^���g�o�b�t�@�쐬
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


// �u�����h�X�e�[�g�쐬
void DirectRenderComponent::CreateBlendState(ID3D11Device* pDevice_, ID3D11DeviceContext* pDeviceContext_)
{
	// �u�����h�X�e�[�g�̐ݒ�
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

// ���X�^���C�U�X�e�[�g�쐬
void DirectRenderComponent::CreateRasterizerState(ID3D11Device* pDevice_, ID3D11DeviceContext*	pDeviceContext_)
{
	//���X�^���C�Y�ݒ�
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


	//�u���u����p�[�e�b�N�X�V�F�[�_�[�쐬
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


	//���_�C���v�b�g���C�A�E�g��`
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(_pDevice->CreateInputLayout(layout, numElements,
		pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &pVertexLayout)))
		throw runtime_error("DirectRenderComponent::SetShader : error.");

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	_pDeviceContext->IASetInputLayout(pVertexLayout);

	//�u���u����s�N�Z���V�F�[�_�[���쐬
	if (FAILED(D3DX11CompileFromFile(_pFileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL,
		&pCompiledShader, &pErrors, NULL))) {
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
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
	/* ��]�s��p����
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

	// �}�g���b�N�X�̊|���Z�͏����ʂ������̂�
	// ���ړ��͂ōςނƂ���͒��ړ��͂ōς܂���
	//	WorldMatrix = scale * rotz * roty * rotx * pos;		// �|���Z�ɂ����ꍇ�̌v�Z��

	// ��]������ɉ��L�̌v�Z�����R�����g��Ԃɂ��Ă��������B
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