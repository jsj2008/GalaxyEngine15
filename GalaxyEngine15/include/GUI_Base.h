#pragma once
#include "math_3d.h"
#include "TextureQuad.h"

class GUI_Base
{
public:
	GUI_Base();
	virtual ~GUI_Base();

	virtual bool Draw()=0;

	bool  visible;			// Visibility of the element

	void UpdateDims();
	void SetSize(float width, float height);
	void SetOrigin(Vector2f new_origin);
	void SetPosition(Vector2f new_position);

protected:
	float height, width,	// Height and width of the element
		  left, top;		// Left and top coordinates of the element

	Vector2f origin;		// Origin of the UI element
	Vector2f position;		// Position around the origin

	TextureQuad quad;		// Visual objects
	Material mat, mat_hover;// materials

};

