#include <windows.h>
#include "SystemClass.h"

int WINAPI WinMain( HINSTANCE hInstance,  HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
{
	
	SystemClass* System;
	bool result;

	System = new SystemClass();
	if (!System)
	{
		return 0;
	}

	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	System->Shutdown();

	delete System;
	System = nullptr;

	return 0;
}