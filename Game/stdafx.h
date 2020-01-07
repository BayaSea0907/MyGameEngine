// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������

#include <algorithm>
#include <memory>

#pragma warning (disable:4005)
#pragma warning (disable:4838)
#pragma warning (disable:4238)

#include <mmsystem.h>

//DirectX 11�̏���
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

//�����N�̏��� .lib������
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

//�萔�̒�`
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1280


//�}�N���̒�`
#define SAFE_RELEASE(p)     { if((p)!=NULL){ (p)->Release();	(p)=NULL; } }
#define SAFE_DELETE(x)	    { if((x)!=NULL){ delete (x);		(x)=0; } }
#define SAFE_DELETE_ARRAY(x){ if(x)        { delete[] (x);        (x)=0}}


//EOF