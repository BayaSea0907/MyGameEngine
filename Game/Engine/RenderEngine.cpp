#include "RenderEngine.h"


CRenderEngine::CRenderEngine()
{
	Camera = NULL;
}


CRenderEngine::~CRenderEngine()
{
}

void CRenderEngine::Initialize(HWND hWnd_)
{
}

void CRenderEngine::Rendering(HWND hWnd_)
{
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

void CRenderEngine::Release()
{

}

void CRenderEngine::SetCamera(GCamera* sCamera_)
{
	if (sCamera_ == NULL) {
		throw invalid_argument("CRenderEngine::SetCamera() : This pointer in null.");
	}

	Camera = sCamera_;
}


void CRenderEngine::RenderScene()
{
	//�o�^���ꂽ�S�Ă�RenderComponent��`��
}


void CRenderEngine::InitRenderComp(CComponent* comp_)
{
	dynamic_cast<CRenderComponent*>(comp_)->Initialize();
}

/*
void CRenderEngine::PushRenderComp(CComponent* rComp_)
{
	PushRenderComp(dynamic_cast<CRenderComponent*>(rComp_));
}

void CRenderEngine::PushRenderComp(CRenderComponent* rComp_)
{
	RenderCompList.push_back(rComp_);
}
*/
// EOF