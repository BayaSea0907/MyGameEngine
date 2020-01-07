/***************************************************

--- ���� ---
17/04/23 �t�@�C��/�N���X�쐬

****************************************************/


#pragma once

#include "RenderComponent.h"
#include "Camera.h"
#include "../stdafx.h"
#include <list>
using namespace std;

// �����_�����O�G���W��
class CRenderEngine
{
protected:
	//�\������I�u�W�F�N�g��RenderComponent���X�g
	//list<CRenderComponent *> RenderCompList;

	//���p����J�����̃|�C���^
	GCamera* Camera;
public:
	// ������
	virtual void Initialize(HWND hWnd_);

	// �`��
	virtual void Rendering(HWND hWnd_);

	// ���
	virtual void Release();

	// �J�������Z�b�g
	void SetCamera(GCamera* sCamera_);

	virtual void InitRenderComp(CComponent* comp_);
	/*
	// �R���|�[�l���g���X�g�ɒǉ�
	void PushRenderComp(CComponent* rComp_);
	void PushRenderComp(CRenderComponent* rComp_);
	*/
protected:
	// �J�������X�V
	virtual void UpdateCamera() = 0;

	// �C�ӂ̓��I�v�f�̎��o��Ԃ��X�V
	virtual void UpdateSceneElements() = 0;
	
	// �o�b�N�o�b�t�@�Ƀ����_�����O
	virtual void RenderScene();
	
	// �o�b�N/�X���b�v�o�b�t�@�����ւ�
	virtual void SwapBuffers() = 0;
	
	// ��ʃN���A
	virtual void ClearRenderView() = 0;

	// ���W�ϊ�
	virtual void TransformMatrix() = 0;
public :
	// �R���X�g���N�^
	CRenderEngine();

	// �f�X�g���N�^
	virtual ~CRenderEngine();
};

