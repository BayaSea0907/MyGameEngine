/***************************************************
�t�@�C����	�FInputPack.h
���e			�F���̓R�[�h

--- ���� ---
17/04/29 �t�@�C���쐬
****************************************************/

#pragma once
#include "../stdafx.h"

enum MyKeyboardCode
{
	ESCAPE = 0x01,
	�P,
	�Q,
	�R,
	�S,
	�T,
	�U,
	�V,
	�W,
	�X,
	�P�O,
	Q = 0x10,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A = 0x1E,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	BACKSLASH = 0x2B,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	RSHIFT = 0x36,
	SPACE = 0x39,
	f1 = 0x3B,
	f2,
	f3,
	f4,
	f5,
	f6,
	f7,
	f8,
	f9,
	f10,
	f12,
	f13,
	UP = 0xC8,
	LEFT = 0xCB,
	RIGHT = 0xCD,
	END = 0xCF,
	DOWN = 0xD0,
	NEXT = 0xD1,
	INSERT = 0xD2,
};

enum MyMouseCode
{
	L_CRICK = 0,
	R_CRICK,
	WHEEL_BUTTON,
	SIDE_BUTTON1,
	SIDE_BUTTON2,
};


enum MyPadCode
{
	//--------------------------------------------------
	// �G���R��
	//--------------------------------------------------
	ELECOM_X   = 0,
	ELECOM_A,
	ELECOM_B,
	ELECOM_Y,
	ELECOM_L1,
	ELECOM_R1,
	ELECOM_L2,
	ELECOM_R2,
	ELECOM_BACK,
	ELECOM_START,
	ELECOM_UP  = 100,
	ELECOM_DOWN,
	ELECOM_RIGHT,
	ELECOM_LEFT,
	ELECOM_R_STICK,
	ELECOM_L_STICK,

	// �V�����f�o�C�X��ǉ�����ꍇ�͉��L�̂悤�ɒǉ�
	//--------------------------------------------------
	// Xbox
	//--------------------------------------------------
	XBOX_X = 0,
	XBOX_Y,
};