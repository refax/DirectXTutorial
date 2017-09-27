#pragma once
#include <windows.h>
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
class D3DClass;

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
class GraphicClass
{
public:
	GraphicClass();
	GraphicClass(const GraphicClass&);
	~GraphicClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;

};

