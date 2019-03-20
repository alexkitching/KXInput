#include "directInput.h"
#include "kxDebug.h"
#include "directInputPad.h"

static DirectInput* instance = nullptr;

bool DirectInput::CreateDirectInput(DirectInput * a_inputPtr)
{
	if(instance == nullptr)
	{
		a_inputPtr = instance = new DirectInput();
	}
	
	return true;
}

void DirectInput::DestroyDirectInput()
{
	if(instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
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

		const BYTE type = GET_DIDEVICE_TYPE(a_instance->dwDevType);
		const BYTE subType = GET_DIDEVICE_SUBTYPE(a_instance->dwDevType);

		switch (type)
		{
		case DI8DEVTYPE_MOUSE:
			Debug::Log("Mouse Device Found on Enumeration");
			break;
		case DI8DEVTYPE_KEYBOARD:
			Debug::Log("Keyboard Device Found on Enumeration");
			break;
		case DI8DEVTYPE_JOYSTICK:
			Debug::Log("Joystick Device Found on Enumeration");
			break;
		case DI8DEVTYPE_GAMEPAD:
			Debug::Log("Gamepad Device Found on Enumeration");
			input->CreateGamePadDevice(a_instance->guidInstance);
			break;
		case DI8DEVTYPE_DRIVING:
			Debug::Log("Driving Device Found on Enumeration");
			break;

		default:
			Debug::Log("Unknown Device Skipped on Enumeration");
			break;
		}
	}

	return DI_ENUM_CONTINUE;	
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

void DirectInput::CreateGamePadDevice(GUID a_guid)
{
	DirectInputPad* pad = new DirectInputPad(m_Input,
											 m_hwnd,
											 a_guid);
	m_devices.emplace_back(pad);
}
