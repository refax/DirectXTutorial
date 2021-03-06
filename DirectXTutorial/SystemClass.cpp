#include "SystemClass.h"

#include "InputClass.h"
#include "GraphicClass.h"

SystemClass::SystemClass()
	: m_Input(nullptr),
	m_Graphics(nullptr)
{
	
}
SystemClass::SystemClass(const SystemClass&)
{

}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth = 0;
	int screenHeight = 0;
	bool result = false;

	//Initialize windows api
	InitializeWindows(screenWidth, screenHeight);

	m_Input = new InputClass();
	if (!m_Input)
	{
		return false;
	}

	m_Input->Initialize();

	m_Graphics = new GraphicClass();
	if (!m_Graphics)
	{
		return false;
	}

	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);

	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	//Release graphics object
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = nullptr;
	}

	//Release input object
	if (m_Input)
	{
		delete m_Input;
		m_Input = nullptr;
	}

	//Shutdown the windows
	ShutdownWindows();
}

void SystemClass::Run()
{
	bool done = false;
	bool result = false;
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (!done)
	{
		//Handle the windows messages
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			//Do the frame processing
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
}

/************************************************************************/
/* Redirect Keyboard Input                                              */
/************************************************************************/
LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
	{
		m_Input->KeyDown(static_cast<unsigned int>(wparam));
		return 0;
	}
	case WM_KEYUP:
	{
		m_Input->KeyUp(static_cast<unsigned int>(wparam));
		return 0;
	}
	default:
	{
		//redirect other message to default handler
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}

	return 0;
}


bool SystemClass::Frame()
{

	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	bool result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}


	return true;
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.
	ApplicationHandle = this;

	// Get the instance of this application.
	m_Hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_ApplicationName = "Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_Hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_ApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	//m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName,
		//WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		//posX, posY, screenWidth, screenHeight, NULL, NULL, m_Hinstance, NULL);

	m_hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		m_ApplicationName,
		m_ApplicationName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,
		NULL, NULL, m_Hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);

}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_ApplicationName, m_Hinstance);
	m_Hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;
}


static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}