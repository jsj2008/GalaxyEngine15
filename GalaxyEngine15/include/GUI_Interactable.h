#pragma once
#include "GUI_Base.h"
class GUI_Interactable :
	public GUI_Base
{
public:
	GUI_Interactable();
	virtual ~GUI_Interactable();

	virtual bool Draw()=0;
	virtual bool Update()=0;

protected:
	bool IsMouseOver(Vector2f mpos);
	bool IsMouseOver(float x, float y);

};

