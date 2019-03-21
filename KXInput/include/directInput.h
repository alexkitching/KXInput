#ifndef __DIRECTINPUT_H__
#define __DIRECTINPUT_H__


#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <vector>
#include "directInputDevice.h"


// DI Device Classes
#define DI_ALLDEVICE	DI8DEVCLASS_ALL
#define DI_CONTROLLER	DI8DEVCLASS_GAMECTRL
#define DI_KEYBOARD		DI8DEVCLASS_KEYBOARD
#define DI_MOUSE		DI8DEVCLASS_POINTER

// DI Enum Scope Flags
#define DI_ENUM_ALLDEVICES	DIEDFL_ALLDEVICES // All installed devices are enumerated.
#define DI_ENUM_ATTACHED	DIEDFL_ATTACHEDONLY // Only attached and installed devices.
#define DI_ENUM_FEEDBACK	DIEDFL_FORCEFEEDBACK // Only devices that support force feedback.
#define DI_ENUM_ALIASES		DIEDFL_INCLUDEALIASES // Include devices that are aliases for other devices.
#define DI_ENUM_HIDDEN		DIEDFL_INCLUDEHIDDEN // Include hidden devices.
#define DI_ENUM_PHANTOM		DIEDFL_INCLUDEPHANTOMS // Include phantom (placeholder) devices.

// DI Enum Return Values
#define DI_ENUM_CONTINUE	DIENUM_CONTINUE // Continues Enumeration
#define DI_ENUM_STOP		DIENUM_STOP // Stops Enumeration

// DI Device CooperativeLevel Flags
#define DI_CL_BACKGROUND	DISCL_BACKGROUND	// The application requires background access.
//////////////////////////////////////////////////////////////////////////////
//	If background access is granted, the device can be acquired at any time,
//	even when the associated window is not the active window.
//////////////////////////////////////////////////////////////////////////////
#define DI_CL_EXCLUSIVE		DISCL_EXCLUSIVE		// The application requires exclusive access.
//////////////////////////////////////////////////////////////////////////////
//	If exclusive access is granted, no other instance of the device can obtain
//  exclusive access to the device while it is acquired.
//  However, nonexclusive access to the device is always permitted,
//  even if another application has obtained exclusive access.
//  An application that acquires the mouse or keyboard device in exclusive mode
//  should always unacquire the devices when it receives WM_ENTERSIZEMOVE and
//  WM_ENTERMENULOOP messages. Otherwise, the user cannot manipulate the menu
//  or move and resize the window.
//////////////////////////////////////////////////////////////////////////////
#define DI_CL_FOREGROUND	DISCL_FOREGROUND	// The application requires foreground access.
//////////////////////////////////////////////////////////////////////////////
//	If background access is granted, the device can be acquired at any time,
//	even when the associated window is not the active window.
//////////////////////////////////////////////////////////////////////////////
#define DI_CL_NONEXCLUSIVE	DISCL_NONEXCLUSIVE	// The application requires nonexclusive access.
//////////////////////////////////////////////////////////////////////////////
//	If background access is granted, the device can be acquired at any time,
//	even when the associated window is not the active window.
//////////////////////////////////////////////////////////////////////////////
#define DI_CL_NOWINKEY		DISCL_NOWINKEY		// Disable the Windows logo key.
//////////////////////////////////////////////////////////////////////////////
//	If background access is granted, the device can be acquired at any time,
//	even when the associated window is not the active window.
//////////////////////////////////////////////////////////////////////////////

// DI Property Headers
#define DI_PH_DEVICE		DIPH_DEVICE
#define DI_PH_BYID			DIPH_BYID // Identifier for object whose setting is being altered/retrieved

#define DI_PROP_BUFFERSIZE	DIPROP_BUFFERSIZE
#define DI_PROP_RANGE		DIPROP_RANGE
#define DI_PROP_DEADZONE	DIPROP_DEADZONE

// DI Device Obj Enum Scope Flags
#define DI_DFT_ALL					DIDFT_ALL // All Objects

#define DI_DFT_AXIS					DIDFT_AXIS // An axis, either absolute or relative.
#define DI_DFT_RELAXIS				DIDFT_RELAXIS
#define DI_DFT_ABSAXIS				DIDFT_ABSAXIS // Absolute Axis

#define DI_DFT_BUTTON				DIDFT_BUTTON // A push button or a toggle button.
#define DI_DFT_PSHBUTTON			DIDFT_PSHBUTTON // A push button. A push button is reported as down when the user presses it, and as up when the user releases it.
#define DI_DFT_TGLBUTTON			DIDFT_TGLBUTTON // A toggle button. A toggle button is reported as down when the user presses it and remains so until the user presses the button a second time.

#define DI_DFT_COLLECTION			DIDFT_COLLECTION // A HID link collection. HID link collections do not generate data of their own.
#define DI_DFT_NOCOLLECTION			DIDFT_NOCOLLECTION // An object that does not belong to any HID link collection
#define DI_DFT_ENUMCOLLECTION		DIDFT_ENUMCOLLECTION // An object that belongs to HID link collection number n.

#define DI_DFT_FF_ACTUATOR			DIDFT_FFACTUATOR // An object that contains a force-feedback actuator. In other words, forces can be applied to this object.
#define DI_DFT_FF_EFFECTTRIGGER		DIDFT_FFEFFECTTRIGGER // An object that can be used to trigger force-feedback effects.

#define DI_DFT_ALIAS				DIDFT_ALIAS //Controls identified by a Human Interface Device (HID) usage alias.
#define DI_DFT_NODATA				DIDFT_NODATA // An object that does not generate data.
#define DI_DFT_OUTPUT				DIDFT_OUTPUT // An object that supports output. 
#define DI_DFT_POV					DIDFT_POV // A point-of-view controller.
#define DI_DFT_VENDORDEFINED		DIDFT_VENDORDEFINED // An object of a type defined by the manufacturer.


class DirectInputKeyboard;
class DirectInputMouse;

class DirectInput
{
public:
	static bool CreateDirectInput(DirectInput* a_inputPtr);
	static void DestroyDirectInput();
	~DirectInput();

	void UpdateDevices();
private:
	DirectInput();
	bool Init();
	static BOOL CALLBACK DeviceEnumCallback(const DIDEVICEINSTANCE* a_instance,
											VOID* a_context);
	static BOOL CALLBACK EnumWindowsProc(_In_ HWND a_hwnd, _In_ LPARAM a_param);

	void CreateGamePadDevice(GUID a_guid);

	bool m_bInitialised;

	// Handle to Window
	HWND m_hwnd;
	// DirectInput Interface
	IDirectInput8W* m_Input;

	std::vector<DirectInputDevice*> m_devices;

	
};

#endif