#pragma once
#include "../Math.h"

class FTransform
{
public:
	//ÉÅÉìÉoïœêî
	FVector Position;
	FQuaternion Rotation;
	FVector Scale;

	FTransform* parent;
	/*
	FVector LocalPosition;
	FQuaternion LocalRotation;
	FVector LocalScale;
	*/

public:
	FTransform(	FVector pos_ = { 0.0f, 0.0f, 0.0f },
		FQuaternion rot_ = { 0.0f, 0.0f, 0.0f },
		FVector scale_ = { 1.0f, 1.0f, 1.0 } )
		: Position(pos_), Rotation(rot_), Scale(scale_) {};
	~FTransform();
};

