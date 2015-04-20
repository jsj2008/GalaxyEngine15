#pragma once
#include "..\stdafx.h"
#include "math_3d.h"
#include <glm\gtc\matrix_transform.hpp>
#include <utility> 

#define ScreenWidth GlobalCustomVariables::Instance().GetScreenWidth()
#define ScreenHeight GlobalCustomVariables::Instance().GetScreenHeight()
#define ViewMatrix GlobalCustomVariables::Instance().GetViewMatrix()

class GlobalCustomVariables
{
public:
	static GlobalCustomVariables& Instance()
	{
		static GlobalCustomVariables singleton;
		return singleton;
	}

	static int GetScreenWidth();
	static int GetScreenHeight();
	static glm::mat4 GetViewMatrix(){ 
		return mat; 
	}

	static void SetScreenDims(int w, int h);
	static void SetViewMatrix(glm::mat4 _mat){
		mat = _mat;
	}

	static void SetCursorPos(double x, double y){
		mouseX = x; mouseY = y;
	};
	static Vector2f GetCursorPos(){
		return Vector2f((float)mouseX, (float)mouseY);
	};

private:
	GlobalCustomVariables() {};											 // Private constructor
	GlobalCustomVariables(const GlobalCustomVariables&);                 // Prevent copy-construction
	GlobalCustomVariables& operator=(const GlobalCustomVariables&);      // Prevent assignment

	static int sw, sh;
	static glm::mat4 mat;
	static double mouseX, mouseY;
};