#include "kxManagerWin.h"
#include "kxDebug.h"

KXManagerWin::KXManagerWin() : KXManager(), m_dInput(nullptr)
{
}

KXManagerWin::~KXManagerWin()
{
	DirectInput::DestroyDirectInput();
}

bool KXManagerWin::Init()
{
	Debug::Log("KXManagerWin::Init - Creating Direct Input");
	DirectInput::CreateDirectInput(m_dInput);
	return true;
}

void KXManagerWin::Update()
{
	// Update Devices Here
	if(m_dInput != nullptr)
	{
		m_dInput->UpdateDevices();
	}
	else
	{
		Debug::Log("Attempted to update direct input devices but direct input was null!");
	}
	
}

