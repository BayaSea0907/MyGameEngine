#pragma once
class FQuaternion
{
public:
	//�����o�ϐ�
	float x;
	float y;
	float z;

public:
	FQuaternion(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f)
		: x(x_), y(y_), z(z_) {};
	~FQuaternion();
};

