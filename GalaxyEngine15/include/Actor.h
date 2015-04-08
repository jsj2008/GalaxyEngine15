#pragma once
#include "math_3d.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

private: // Functions

	///////////////////////////////////
	//			Position             //
	///////////////////////////////////
	void SetPosition(Vector2f position);
	void SetPosition(float x, float y);

	Vector2f GetPosition();

private: // Member variables
	Vector2f m_worldPos;
};

