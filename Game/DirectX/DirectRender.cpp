#include "../Engine/GameEngine.h"
#include "DirectRender.h"

#pragma warning (disable:4005)
#pragma warning (disable:4838)
#pragma warning (disable:4238)

DirectRender::DirectRender()
{
}


DirectRender::~DirectRender()
{
}

void DirectRender::Initialize(HWND _hWnd) {
	CRenderEngine::Initialize(_hWnd);


	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &FeatureLevel, 1,
        D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, pFeatureLevel, &pDeviceContext))) {
		return;
	}

	//�����_�[�^�[�Q�b�g�r���[�̍쐬
	ID3D11Texture2D * pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	pBackBuffer->Release();
    SAFE_RELEASE(pBackBuffer);
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);


	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width	= WINDOW_WIDTH;
	vp.Height	= WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pDeviceContext->RSSetViewports(1, &vp);
	/*
	pPolygon = new CPolygon();
	pPolygon->init(_hWnd, pDevice, pDeviceContext, pSwapChain, pRenderTargetView);
	*/

	/***********************************/

	
}

void DirectRender::Rendering(HWND _hWnd) {
    

	// �C���^���N�e�B�u�ȓ��͂Ɋ�Â��āA�܂��͏���̃p�X�ɏ]����
	// �J�����ϊ����X�V����
	UpdateCamera();

	// �V�[�����̔C�ӂ̓��I�v�f�̈ʒu�A�p���A
	// ���̑��̊֘A�������o��Ԃ��X�V����B
	UpdateSceneElements();

	// �����t���[�����A�I�t�X�N���[���́u�o�b�N�o�b�t�@�v�Ƃ���
	// �t���[���o�b�t�@�Ƀ����_�����O����B
	RenderScene();

	// �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɓ���ւ��āi�X���b�v�j�A�Ō�Ƀ����_�����O���ꂽ
	// �摜����ʏ�ɏo���i�܂��́A�E�B���h�E�\�����[�h�ł́A
	// �o�b�N�o�b�t�@�̃R���e���c���t�����g�o�b�t�@�ɃR�s�[����B�j
	SwapBuffers();

}


void DirectRender::Release() {
	
	SAFE_RELEASE(pSwapChain);
	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pDeviceContext);
	SAFE_RELEASE(pDevice);
	
}

void DirectRender::InitRenderComp(CComponent* comp_)
{
	dynamic_cast<DirectRenderComponent*>(comp_)->Initialize(pDevice, pDeviceContext);
}

void DirectRender::UpdateCamera()
{
	if (Camera == NULL) {
		throw invalid_argument("DirectRender::UpdateCamera() : Camera is not found.");
	}

	// �J�����i���_�j�ʒu
	FVector& c_pos = Camera->Transform.Position;

	D3DXVECTOR3 eye(c_pos.x, c_pos.y, c_pos.z);

	// �����ʒu
	FVector& c_tar = Camera->TargetPos;
	D3DXVECTOR3 at(c_tar.x, c_tar.y, c_tar.z);

	// ����ʒu
	// Transform��Quaternion����������ݒ肷��B
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	// �J�����ϊ�
	D3DXMatrixLookAtLH(&ViewMatrix, &eye, &at, &up);
}

void DirectRender::UpdateSceneElements()
{

}

void DirectRender::RenderScene()
{
	TransformMatrix();
	ClearRenderView();
		
	vector<CComponent*> component;
	auto& oList = ObjectList::GetInstance().objectList;
	for (auto obj : oList)
	{
		obj->GetComponent<DirectRenderComponent>(component);
		for (auto comp : component)
			dynamic_cast<DirectRenderComponent*>(comp)->Rendering(pDeviceContext, ViewMatrix, ProjMatrix);
	}
}

void DirectRender::SwapBuffers()
{
	pSwapChain->Present(0, 0);
}

void DirectRender::ClearRenderView()
{
	float bColor[4] = { Camera->BackgroundColor.red,
		Camera->BackgroundColor.green,
		Camera->BackgroundColor.blue,
		Camera->BackgroundColor.alpha };
	pDeviceContext->ClearRenderTargetView(pRenderTargetView, bColor);
}

void DirectRender::TransformMatrix()
{
	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	D3DXMatrixRotationY(&WorldMatrix, 0.0f);

	//�v���W�F�N�g�g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMatrixPerspectiveFovLH(&ProjMatrix, (FLOAT)D3DX_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, Camera->nearDistance, Camera->farDistance);
}

// EOF