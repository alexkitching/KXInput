#include "directInput.h"
#include "kxDebug.h"
#include "directInputPad.h"

bool DirectInput::CreateDirectInput(DirectInput * a_inputPtr)
{
	a_inputPtr = new DirectInput();

	return true;
}

DirectInput::~DirectInput()
{
	if(m_Input)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}

void DirectInput::UpdateDevices()
{
	for (auto& m_device : m_devices)
	{
		m_device->Update();
	}
}

DirectInput::DirectInput() :
m_Input(nullptr)
{
	bool result = false;
	const HINSTANCE instanceHandle = GetModuleHandle(nullptr);

	// Create Input Handle
	result = DirectInput8Create(instanceHandle, DIRECTINPUT_VERSION,
								IID_IDirectInput8,
								reinterpret_cast<void**>(&m_Input),
								nullptr);

	// Get our Window Handle
	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&m_hwnd));

	// Enum Devices
	m_Input->EnumDevices(DI_CONTROLLER, DeviceEnumCallback,
		static_cast<VOID*>(this), DIEDFL_ATTACHEDONLY);

}

BOOL DirectInput::DeviceEnumCallback(const DIDEVICEINSTANCE* a_instance,
									 void* a_context)
{
	DirectInput* input = static_cast<DirectInput*>(a_context);

	if(input)
	{
		if(a_instance->dwDevType == DI8DEVTYPE_GAMEPAD)
		{
			DirectInputPad* pad = new DirectInputPad(input->m_Input,
													 input->m_hwnd,
													 a_instance->guidInstance );
			input->m_devices.emplace_back(pad);
		}
	}

	return DI_ENUM_STOP;
}

BOOL DirectInput::EnumWindowsProc(HWND a_hwnd, LPARAM a_param)
{
	HWND& dInputHwnd = reinterpret_cast<HWND&>(a_param);

	const DWORD currentProcessID = GetCurrentProcessId();

	DWORD windowProcessID;
	GetWindowThreadProcessId(a_hwnd, &windowProcessID);

	if(windowProcessID == currentProcessID)
	{
		dInputHwnd = a_hwnd;
		return FALSE;
	}
	return TRUE;
}
