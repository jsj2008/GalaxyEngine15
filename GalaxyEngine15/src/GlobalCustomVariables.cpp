#include "..\include\GlobalCustomVariables.h"

int GlobalCustomVariables::sh;
int GlobalCustomVariables::sw;
double GlobalCustomVariables::mouseX;
double GlobalCustomVariables::mouseY;
glm::mat4 GlobalCustomVariables::mat;

int GlobalCustomVariables::GetScreenWidth()
{
	return sw;
}

int GlobalCustomVariables::GetScreenHeight()
{
	return sh;
}

void GlobalCustomVariables::SetScreenDims(int w, int h)
{
	sw = w; sh = h;
}
