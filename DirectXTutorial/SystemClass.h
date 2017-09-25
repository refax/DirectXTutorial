#pragma once
#include <windows.h>

class InputClass;
class GraphicClass;

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCTSTR m_ApplicationName;
	HINSTANCE m_Hinstance;
	HWND m_hwnd;
	InputClass* m_Input;
	GraphicClass* m_Graphics;
};

static SystemClass* ApplicationHandle = 0;
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

