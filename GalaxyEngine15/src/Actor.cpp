#include "actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
	// Virtual destructor
}

void Actor::SetPosition(Vector2f position)
{
	m_worldPos = position;
}

void  Actor::SetPosition(float x, float y)
{
	m_worldPos.x = x;
	m_worldPos.y = y;
}

Vector2f Actor::GetPosition()
{
	return m_worldPos;
}