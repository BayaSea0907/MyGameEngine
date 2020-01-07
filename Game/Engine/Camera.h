/***************************************************
--- ���� ---
17/04/25 �t�@�C��/�N���X�쐬
17/04/30 CColorRGBA�N���X�쐬

****************************************************/

#pragma once
#include "GameObject.h"

// �F�N���X
// ���l�͈�(0.0f - 1.0f)
struct CColorRGBA
{
	float red;
	float green;
	float blue;
	float alpha;

	constexpr CColorRGBA(float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, float a_ = 1.0f)
		: red(r_), green(g_), blue(b_), alpha(a_) {};

	CColorRGBA& operator= (const CColorRGBA& other) {
		red = other.red;
		green = other.green;
		blue = other.blue;
		alpha = other.alpha;
		return *this;
	}
};

class GCamera : public GameObject
{
	float MoveSpeed = 0.0f;
	FVector ToTargetPos;
public:
	// �������W
	FVector TargetPos;

	// �w�i�J���[
	CColorRGBA BackgroundColor;

	// �ł��߂��\�����鋗��
	float nearDistance = 1.0f;

	// �ł������\�����鋗��
	float farDistance = 1000.0f;
	
public:
	virtual void Initialize()override;
	virtual void Update(const float deltaTime_) override;
	void ShiftMove(FVector add_);
	// �����ʒu��ݒ�B
	void SetTargetPos(FVector pos_);
	void SetMoveSpeed(float spd_);

	void DoActiveCamera();

protected:
	void UpdateTargetPos(const float deltaTime_);

public:
	GCamera();
	virtual ~GCamera();
};
