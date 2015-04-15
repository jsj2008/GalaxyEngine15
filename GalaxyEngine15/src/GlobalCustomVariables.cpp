#include "..\include\GlobalCustomVariables.h"

int GlobalCustomVariables::sh;
int GlobalCustomVariables::sw;

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
