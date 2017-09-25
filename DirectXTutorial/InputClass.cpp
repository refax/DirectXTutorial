#include "InputClass.h"



InputClass::InputClass()
{
}


InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	// Initialize all the keys to being released and not pressed.
	for (int i = 0; i < 256; ++i)
	{
		m_Keys[i] = false;
	}
}

void InputClass::KeyDown(unsigned int input)
{
	if (input < 256)
	{
		m_Keys[input] = true;
	}
}

void InputClass::KeyUp(unsigned int input )
{
	if (input < 256)
	{
		m_Keys[input] = false;
	}
}

bool InputClass::IsKeyDown(unsigned int key)
{
	return m_Keys[key];
}
