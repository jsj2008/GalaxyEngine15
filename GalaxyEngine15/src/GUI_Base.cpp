#include "..\include\GUI_Base.h"


GUI_Base::GUI_Base() :
height(0), width(0), left(0), top(0),
origin(0, 0), position(0,0)
{
}

GUI_Base::~GUI_Base()
{
}

void GUI_Base::SetSize(float _width, float _height)
{
	height = _height; width = _width;
	UpdateDims();
}

void GUI_Base::UpdateDims()
{
	left = position.x - origin.x;
	top = position.y - origin.y;
}

void GUI_Base::SetPosition(Vector2f new_position)
{
	position = new_position;
	UpdateDims();
}

void GUI_Base::SetOrigin(Vector2f new_origin)
{
	origin = new_origin;
	quad.SetOrigin(new_origin.x, new_origin.y);
	UpdateDims();
}
