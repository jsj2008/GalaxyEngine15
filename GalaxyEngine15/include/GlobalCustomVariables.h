#pragma once
#include "..\stdafx.h"
#include <utility> 

#define ScreenWidth GlobalCustomVariables::Instance().GetScreenWidth()
#define ScreenHeight GlobalCustomVariables::Instance().GetScreenHeight()

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

	static void SetScreenDims(int w, int h);

private:
	GlobalCustomVariables() {};											 // Private constructor
	GlobalCustomVariables(const GlobalCustomVariables&);                 // Prevent copy-construction
	GlobalCustomVariables& operator=(const GlobalCustomVariables&);      // Prevent assignment

	static int sw, sh;
};

	
