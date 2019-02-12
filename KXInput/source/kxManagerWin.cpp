#include "kxManagerWin.h"
#include "kxDebug.h"

KXManagerWin::KXManagerWin(bool a_test): m_dInput(nullptr)
{
}

bool KXManagerWin::Init()
{
	_KXLogger("KXManagerWin::Init - Creating Direct Input");
	DirectInput::CreateDirectInput(m_dInput);
	return true;
}

void KXManagerWin::Update()
{
	// Update Devices Here
	m_dInput->UpdateDevices();
}

