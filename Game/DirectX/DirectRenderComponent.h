#pragma once
#include "../stdafx.h"
#include "../Engine/RenderComponent.h"

//�V�F�[�_�[�ɓn���l
struct SHADER_GLOBAL
{
	D3DXMATRIX	mWVP;	//���[���h����ˉe�܂ł̕ϊ��s��
	D3DXVECTOR4 vDiffuse;	//�f���t���[�Y�F
};

//���_�̍\����
struct SimpleVertex
{
	D3DXVECTOR3 Pos;	// �ʒu
	D3DXVECTOR2 cTex;	// �e�N�X�`���摜
};

class DirectRenderComponent : public CRenderComponent
{
protected:
	ID3D11InputLayout*	pVertexLayout = NULL;
	ID3D11Buffer*		pVertexBuffer = NULL;

	ID3D11VertexShader*	pVertexShader = NULL;		// effect�ł͂Ȃ��A�ʂɃo�[�e�b�N�X�V�F�[�_�[
	ID3D11PixelShader*	pPixelShader = NULL;		// effext�ł͂Ȃ��A�ʂɃs�N�Z���V�F�[�_�[

	ID3D11Buffer*		pConstantBuffer = NULL;	//�A�v�������V�F�[�_�[�˂����@�f�B�t���[�Y��n���ׂ̃R���X�^���ƃo�b�t�@
	D3DXVECTOR3			Color;					//(1, 0, 1);	//���F

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

