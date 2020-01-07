#include "Camera.h"


GCamera::GCamera()
{
	BackgroundColor = { 0.0 , 0.0f, 0.2f };
}


GCamera::~GCamera()
{
}

void GCamera::Initialize()
{
	MoveSpeed = 0.0f;
}

void GCamera::Update(const float deltaTime_)
{
	GameObject::Update(deltaTime_);
	UpdateTargetPos(deltaTime_);

}

void GCamera::ShiftMove(FVector add_)
{
	Transform.Position += add_;
	TargetPos += add_;
}

void GCamera::SetTargetPos(FVector pos_)
{
	ToTargetPos = pos_;
}

void GCamera::SetMoveSpeed(float spd_)
{
	MoveSpeed = abs(spd_);
}

void GCamera::UpdateTargetPos(const float deltaTime_)
{
	FVector add = ToTargetPos - TargetPos;
	if (MoveSpeed == 0 || add.length() == 0) {
		return;
	}
	
	float len = min(MoveSpeed * deltaTime_, add.length());
	TargetPos += add.normalized() * len;
}