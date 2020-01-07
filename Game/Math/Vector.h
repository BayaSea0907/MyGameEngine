//3次元ベクトルクラス
#pragma once
#include <math.h>

struct FVector
{
public:
	// メンバ変数
	float x;
	float y;
	float z;

public:
	// コンストラクタ
	constexpr FVector(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f)
		: x(x_), y(y_), z(z_) {};
	~FVector();

public:
	// メンバ関数

	float length()const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	FVector normalized()const
	{
		float len = length();
		return{ x / len, y / len, z / len };
	}

	float dot(const FVector& other)const
	{
		return{ x * other.x + y * other.y + z * other.z };
	}

	FVector cross(const FVector& other)const
	{
		return{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}

public:
	// オペレータ
	FVector& operator= (const FVector& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	FVector operator+() const
	{
		return *this;
	}

	FVector operator-()const {
		return{ -x, -y, -z };
	}

	FVector operator+ (const FVector& other)const
	{
		return{ x + other.x, y + other.y, z + other.z };
	}

	FVector operator- (const FVector& other)const
	{
		return{ x - other.x, y - other.y, z - other.z };
	}

	FVector operator* (const float& value)const
	{
		return{ x * value, y * value, z * value };
	}

	FVector operator/ (const float& value)const
	{
		return{ x / value, y / value, z / value };
	}

	FVector& operator+= (const FVector& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	FVector& operator-= (const FVector& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	FVector& operator*= (const FVector& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	FVector& operator/= (const FVector& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	
	bool operator==(const FVector& other)const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const FVector& other)const
	{
		return x != other.x && y != other.y && z != other.z;
	}

};


