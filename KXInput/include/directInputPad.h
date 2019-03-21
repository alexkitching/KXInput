#ifndef __DIRECTINPUT_PAD_H__
#define __DIRECTINPUT_PAD_H__

#include "directInputDevice.h"

class DirectInputPad : public DirectInputDevice
{
public:

	struct PadData
	{
		char Buttons[128];
		float DPad[2];
		float LeftStick[2];
		float RightStick[2];
		float Triggers;
	};

	DirectInputPad(IDirectInput8W* a_input, HWND a_hWnd, const GUID& a_guid);
	~DirectInputPad() = default;
	
	void Init() override;
	void Update() override;
	PadData GetPadData() const {return m_data;}

	void EnumerateObject(const DIDEVICEOBJECTINSTANCE* a_instance) override;
private:
	

	DIJOYSTATE2 m_state;
	PadData m_data;
};

#endif