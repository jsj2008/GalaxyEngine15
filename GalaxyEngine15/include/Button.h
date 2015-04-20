#pragma once
#include "TextureQuad.h"
#include "GUI_Interactable.h"
#include "GlobalCustomVariables.h"
#include <string>

class Button :
		public GUI_Interactable
{
public:
	Button();
	~Button();

	bool Draw();
	bool Init();

	bool Update();

	void SetPositionF(Vector2f pos);
	void SetPositionF(float x, float y);

	void SetOriginF(Vector2f pos);
	void SetOriginF(float x, float y);

private:
	bool lastOver;
	bool isOver;
	std::string buttonText;
	Material hover_mat;
};

