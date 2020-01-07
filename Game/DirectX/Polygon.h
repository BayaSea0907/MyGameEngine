#pragma once
#include "../stdafx.h"

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

class CPolygon
{
private:
	ID3D11InputLayout*	m_pVertexLayout = NULL;
	ID3D11Buffer*		m_pVertexBuffer = NULL;

	ID3D11VertexShader*	m_pVertexShader = NULL;		// effect�ł͂Ȃ��A�ʂɃo�[�e�b�N�X�V�F�[�_�[
	ID3D11PixelShader*	m_pPixelShader  = NULL;		// effext�ł͂Ȃ��A�ʂɃs�N�Z���V�F�[�_�[

	ID3D11Buffer*		m_pConstantBuffer = NULL;	//�A�v�������V�F�[�_�[�˂����@�f�B�t���[�Y��n���ׂ̃R���X�^���ƃo�b�t�@
	D3DXVECTOR3			m_vColor;					//(1, 0, 1);	//���F

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

