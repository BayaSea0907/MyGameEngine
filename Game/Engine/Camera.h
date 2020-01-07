/***************************************************
--- 履歴 ---
17/04/25 ファイル/クラス作成
17/04/30 CColorRGBAクラス作成

****************************************************/

#pragma once
#include "GameObject.h"

// 色クラス
// 数値範囲(0.0f - 1.0f)
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
	// 注視座標
	FVector TargetPos;

	// 背景カラー
	CColorRGBA BackgroundColor;

	// 最も近い表示する距離
	float nearDistance = 1.0f;

	// 最も遠い表示する距離
	float farDistance = 1000.0f;
	
public:
	virtual void Initialize()override;
	virtual void Update(const float deltaTime_) override;
	void ShiftMove(FVector add_);
	// 注視位置を設定。
	void SetTargetPos(FVector pos_);
	void SetMoveSpeed(float spd_);

	void DoActiveCamera();

protected:
	void UpdateTargetPos(const float deltaTime_);

public:
	GCamera();
	virtual ~GCamera();
};
