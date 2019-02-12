#include "directInputPad.h"
#include <array>
#include <kxMath.h>
#include <directInput.h>

DirectInputPad::DirectInputPad(IDirectInput8W* a_input, HWND a_hWnd, const GUID& a_guid) :
DirectInputDevice(a_input, a_hWnd, a_guid)
{
	m_device->SetDataFormat(&c_dfDIJoystick2);

	m_device->SetCooperativeLevel(a_hWnd, DI_CL_BACKGROUND | DI_CL_EXCLUSIVE);
	m_device->Acquire();
}

void DirectInputPad::Update()
{
	m_device->Poll();
	m_device->GetDeviceState(sizeof(m_state), &m_state);

	DWORD nItems = 20;
	std::array<DIDEVICEOBJECTDATA, 20> data;
	m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), data.data(), &nItems, 0); // NItems by Ptr (Returns Actual Number of Data Returned)
	for(unsigned int i = 0; i < nItems; ++i)
	{
		if(data[i].dwOfs >= offsetof(DIJOYSTATE2, rgbButtons[0]) &&
			data[i].dwOfs <= offsetof(DIJOYSTATE2, rgbButtons[127]))
		{
			// Is Button Data
			m_data.Buttons[data[i].dwOfs - offsetof(DIJOYSTATE2, rgbButtons[0])] = data[i].dwData & 0x80;
		}
		else if(data[i].dwOfs == offsetof(DIJOYSTATE2, rgbButtons[0])) // DPad
		{
			Vector2 pos;
			//float pos[2];
			switch(data[i].dwData) // Degrees e.g 4500 - 45 degrees
			{
			case 0:
				pos = {0.f, -1000.f};
			case 4500:
				pos = {1000.f, -1000.f};
			case 9000:
				pos = {1000.f, 0.f};
			case 13500:
				pos = {1000.f, 0.f};
			case 18000:
				pos = {0.f, 1000.f};
			case 22500:
				pos = {-1000.f, 1000.f};
			case 27000:
				pos = {-1000.f, 0.f};
			case 31500:
				pos = {-1000.f, -1000.f};
			default:
				pos = {0.f, 0.f};
			}
			m_data.DPad[0] = pos.x;
			m_data.DPad[1] = pos.y;
		}	// Check Left Pad
		else if(data[i].dwOfs == offsetof(DIJOYSTATE2, lX) || // Offset of (In Bytes) == Position in Struct of member
				data[i].dwOfs == offsetof(DIJOYSTATE2, lY))
		{
			m_data.LeftStick[0] = m_state.lX;
			m_data.LeftStick[1] = m_state.lY;
		}	// Check right pad
		else if(data[i].dwOfs == offsetof(DIJOYSTATE2, lRx) ||
				data[i].dwOfs == offsetof(DIJOYSTATE2, lRy))
		{
			m_data.RightStick[0] = m_state.lRx;
			m_data.RightStick[1] = m_state.lRy;
		}
		else if(data[i].dwOfs == offsetof(DIJOYSTATE2, lZ))
		{
			m_data.Triggers = data[i].dwData;
		}
	}
}

void DirectInputPad::EnumerateObject(const DIDEVICEOBJECTINSTANCE* a_instance)
{
	if(a_instance->dwType & DI_DFT_AXIS)
	{
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DI_PH_BYID;
		diprg.diph.dwObj = a_instance->dwType;
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		m_device->SetProperty(DI_PROP_RANGE, &diprg.diph);

		DIPROPDWORD didw;
		didw.diph.dwSize = sizeof(DIPROPDWORD);
		didw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		didw.diph.dwHow = DI_PH_BYID;
		didw.diph.dwObj = a_instance->dwType;
		didw.dwData = 100; // 10% deadzone

		m_device->SetProperty(DI_PROP_DEADZONE, &didw.diph);
	}
}
