#include "..\include\GUI_Interactable.h"


GUI_Interactable::GUI_Interactable()
{
}


GUI_Interactable::~GUI_Interactable()
{
}

bool GUI_Interactable::Draw()
{
	return false;
}

bool GUI_Interactable::IsMouseOver(float x, float y)
{
	// 0------ X+    Window scheme used for this calculation
	// |
	// |
	// Y+		    
	
	if (x > left + width || x < left) return false;
	if (y > top + height || y < top)  return false;

	return true;
}
