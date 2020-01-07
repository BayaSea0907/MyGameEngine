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
	// ������
	void Initialize(HWND _hWnd) override;

	// �`��
	void Rendering(HWND _hWnd) override;
	
	// ���
	void Release(void) override;

	// �R���|�[�l���g�̏�����
	// �����_�[�G���W������K�v�Ȓl��n��
	virtual void InitRenderComp(CComponent* comp_) override;

protected:
	// �J�������X�V
	virtual void UpdateCamera() override;

	// �C�ӂ̓��I�v�f�̎��o��Ԃ��X�V
	virtual void UpdateSceneElements() override;

	// �o�b�N�o�b�t�@�Ƀ����_�����O
	virtual void RenderScene() override;

	// �o�b�N/�X���b�v�o�b�t�@�����ւ�
	virtual void SwapBuffers() override;

	// ��ʃN���A
	virtual void ClearRenderView() override;

	// ���W�ϊ�
	virtual void TransformMatrix() override;

public :
	// �R���X�g���N�^
	DirectRender();

	// �f�X�g���N�^
	~DirectRender();

};

