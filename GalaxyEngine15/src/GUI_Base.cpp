#include "..\include\GUI_Base.h"


GUI_Base::GUI_Base()
{
}

GUI_Base::~GUI_Base()
{
}

void GUI_Base::SetOrigin(Vector2f new_position)
{
	position = new_position;
}

void GUI_Base::SetPosition(Vector2f new_origin)
{
	origin = new_origin;
}
