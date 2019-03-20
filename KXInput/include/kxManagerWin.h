#ifndef __KXMANAGER_WIN_H__
#define __KXMANAGER_WIN_H__

#include "kxManager.h"
#include "directInput.h"

class KXManagerWin : public KXManager
{
public:
	KXManagerWin();
	~KXManagerWin();

	bool Init() override;
	void Update() override;
private:
	DirectInput* m_dInput;
};

#endif