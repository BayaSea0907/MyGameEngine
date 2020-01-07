#pragma once
class FQuaternion
{
public:
	//ƒƒ“ƒo•Ï”
	float x;
	float y;
	float z;

public:
	FQuaternion(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f)
		: x(x_), y(y_), z(z_) {};
	~FQuaternion();
};

