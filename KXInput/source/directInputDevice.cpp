#include "directInputDevice.h"
#include "kxDebug.h"
#include "directInput.h"

DirectInputDevice::DirectInputDevice() :
m_input(nullptr),
m_device(nullptr)
{
}

DirectInputDevice::DirectInputDevice(IDirectInput8W* a_input, HWND a_hWnd, const GUID& a_guid) :
	m_input(a_input),
	m_device(nullptr),
	m_guid(a_guid)
{

}

void DirectInputDevice::Init()
{
	if (m_device == nullptr) // Not Initialised
	{
		const bool success = m_input->CreateDevice(m_guid, &m_device, nullptr);

		// Create DInput Property DWord to set buffer size
		DIPROPDWORD prop;
		prop.diph.dwHeaderSize = sizeof(prop.diph);
		prop.diph.dwSize = sizeof(prop);
		prop.diph.dwHow = DI_PH_DEVICE;
		prop.diph.dwObj = 0;
		prop.dwData = 256; // Buffer up to 256 events
		m_device->SetProperty(DI_PROP_BUFFERSIZE, &prop.diph);

		// Enum Objects
		m_device->EnumObjects(EnumObjectsCallback, this, DI_DFT_ALL);
	}
}

DirectInputDevice::~DirectInputDevice()
{
	if(m_device != nullptr)
	{
		m_device->Unacquire();
		m_device->Release();
		m_device = nullptr;
	}
}

BOOL DirectInputDevice::EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* a_instance, void* a_context)
{
	DirectInputDevice* device = reinterpret_cast<DirectInputDevice*>(a_context);
	device->EnumerateObject(a_instance);
	return DIENUM_CONTINUE;
}
