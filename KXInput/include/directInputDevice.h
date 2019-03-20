#ifndef __DIRECTINPUTDEVICE_H__
#define __DIRECTINPUTDEVICE_H__

#include <dinput.h>

class Event;



class DirectInputDevice
{
public:
	DirectInputDevice();
	DirectInputDevice(IDirectInput8W* a_input, HWND a_hWnd, const GUID& a_guid);
	virtual ~DirectInputDevice();
	virtual void Update() = 0;
	virtual void EnumerateObject(const DIDEVICEOBJECTINSTANCE* a_instance) = 0;
protected:
	IDirectInput8W* m_input;
	IDirectInputDevice8W* m_device;

	const unsigned int MaxEvents = 64;
	//std::queue<Event> m_events;

	
private:
	static BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* a_instance, VOID* a_context);
	

};

#endif