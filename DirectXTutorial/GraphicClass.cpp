#include "GraphicClass.h"



GraphicClass::GraphicClass()
{
}


GraphicClass::~GraphicClass()
{
}


GraphicClass::GraphicClass(const GraphicClass&)
{

}


bool GraphicClass::Initialize(int, int, HWND)
{
	return true;
}

void GraphicClass::Shutdown()
{

}

bool GraphicClass::Frame()
{
	return true;
}


bool GraphicClass::Render()
{
	return true;
}
