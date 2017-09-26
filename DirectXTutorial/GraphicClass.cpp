#include "GraphicClass.h"

#include "D3DClass.h"

GraphicClass::GraphicClass()
	: m_D3D(nullptr)
{
}


GraphicClass::~GraphicClass()
{
}


GraphicClass::GraphicClass(const GraphicClass&)
{

}


bool GraphicClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	//Create
	m_D3D = new D3DClass();
	if (!m_D3D)
	{
		return false;
	}

	bool result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicClass::Shutdown()
{
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = nullptr;
	}
}

bool GraphicClass::Frame()
{
	bool result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicClass::Render()
{
	//Clear the buffer to begin the scene
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 0.5f); //passing a color (grey)


	//Draw scene to the screen
	m_D3D->EndScene();

	return true;
}
