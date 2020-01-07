#include "SceneEngine.h"

CSceneEngine::CSceneEngine()
{
}

CSceneEngine::~CSceneEngine()
{
}

void CSceneEngine::Initialize()
{
	m_pCurrentScene = NULL;
	m_pNextScene = NULL;
	m_pLoadScene = NULL;
	loadWaitFrame = 0;
}

// �������K�p�������V�[�����Z�b�g	���[�h��ʂ����܂Ȃ��ł������Ȃ�g���Ă悵
void CSceneEngine::SetCurrentScene(CBaseScene* next_)
{
	if (m_pCurrentScene == NULL)
	{
		m_pCurrentScene = next_;
	}
	// else if (0);
}

// ���ɓK�p�������V�[�����Z�b�g
void CSceneEngine::SetNextScene(CBaseScene* next_)
{
	if (m_pNextScene == NULL)
	{
		m_pNextScene = next_;
	} 
	// else if ();
}

// �V�[���ړ����ɖ���Ăяo���V�[�����Z�b�g
void CSceneEngine::SetLoadScene(CBaseScene* scene_)
{
	if (m_pLoadScene == NULL)
	{
		m_pLoadScene = scene_;
	}
	// else if (0);
}

// �I�u�W�F�N�g���X�g�ɃV�[���������Ă�I�u�W�F�N�g��n��
void CSceneEngine::SetGameObjectToWorld(CBaseScene* scene_)
{
	// �����ŃI�u�W�F�N�g���X�g�ɃI�u�W�F�N�g���Z�b�g
	// SetGameObject(scene_->GetGameObject());
}

// �X�V
void CSceneEngine::Update()
{
	if (m_pCurrentScene != NULL)
	{
		// m_pCurrentScene->Update();
	} 	
	else	
	{
		Loading();
	}
}

// �V�[�����ړ����邲�ƂɁA���b�Ԏʂ�
void CSceneEngine::Loading()
{
	if (loadWaitFrame < 180 && m_pLoadScene != NULL)
	{
		m_pLoadScene->Update();
	}
	else
	{
		SetCurrentScene(m_pNextScene);
		SAFE_RELEASE(m_pNextScene)
	}
}

void CSceneEngine::Release()
{
	SAFE_DELETE(m_pCurrentScene);
	SAFE_DELETE(m_pNextScene);
	SAFE_DELETE(m_pLoadScene);
}