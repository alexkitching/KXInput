#ifndef __KXMANAGER_WIN_H__
#define __KXMANAGER_WIN_H__

#include "kxManager.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class KXManagerWin : public KXManager
{
public:
	KXManagerWin() = default;
	KXManagerWin(bool a_test);
	~KXManagerWin() = default;

	void Update() override;
private:

};

#endif