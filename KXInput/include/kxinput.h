#ifndef __KXINPUT_H__
#define __KXINPUT_H__
#define KXINPUT_API __declspec(dllexport)

#include "kxDebug.h"

#if defined(_WIN32) // WINDOWS
#define KXWIN
#include "kxManagerWin.h"
typedef KXManagerWin Manager;
#endif // ~WINDOWS



static KXManagerWin* _KXManager;

extern "C"
{

#pragma region Examples
	// KXINPUT_API int TestFunc(int a_test)
	// {
	// 	return a_test;
	// }
	// 
	// 
	// KXINPUT_API void TestFuncRef(int* a_test)
	// {
	// 	const int value = *a_test;
	// 
	// 	*a_test = value * value;
	// }
	// 
	// KXINPUT_API void TestScaleArray(float* a_array, float a_constant, int a_size)
	// {
	// 	for(int i = 0; i < a_size; ++i)
	// 	{
	// 		a_array[i] *= a_constant;
	// 	}
	// }
	// 
	// KXINPUT_API struct myInputDevice
	// {
	// 	int handle;
	// 	int value;
	// };
	// 
	// static int currentInputDeviceNum = 0;
	// KXINPUT_API void InitInputDevice(myInputDevice* a_device)
	// {
	// 	a_device->handle = currentInputDeviceNum++;
	// 	a_device->value = 10;
	// }
	// 
#pragma endregion 

#pragma region Init/Cleanup

inline
KXINPUT_API bool InitKXInput(KXLogMessageClbk a_clbk)
	{
		Debug::SetLogCallback(a_clbk);
		_KXManager = new KXManagerWin();

		if(_KXManager == nullptr)
		{
			Debug::Log("KXManager Is null!");
			return false;
		}

		_KXManager->Init();
		return true;
	}

	KXINPUT_API void CleanupKXInput()
	{
		if(_KXManager != nullptr)
		{
			delete _KXManager;
			_KXManager = nullptr;
		}
	}

#pragma endregion 



	KXINPUT_API void KXInputUpdate()
	{
		_KXManager->Update();
		//Debug::Log("KXUpdate Called!");
	}

}

#endif
