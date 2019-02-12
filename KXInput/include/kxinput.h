#ifndef __KXINPUT_H__
#define __KXINPUT_H__
#define KXINPUT_API __declspec(dllexport)

#include "kxDebug.h"

#if defined(_WIN32) // WINDOWS
#define KXWIN
#include "kxManagerWin.h"
typedef KXManagerWin Manager;
#endif // ~WINDOWS



static Manager* _KXManager;



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
	// typedef void(*logMSG_t)(const char* msg);
	// static logMSG_t logMsg;
	// 
	// static void LogMessageTest()
	// {
	// 	logMsg("Test Message!");
	// }
	// 
	// KXINPUT_API void SetLogCallback(logMSG_t logMsgCallback)
	// {
	// 	logMsg = logMsgCallback;
	// 	LogMessageTest();
	// }
#pragma endregion 

#pragma region Init/Cleanup

	KXINPUT_API bool InitKXInput()
	{
		_KXManager = new Manager(true);
		_KXManager->Init();
		return true;
	}

	KXINPUT_API void CleanupKXInput()
	{
	}

	KXINPUT_API void SetLoggerClbk(KXLogMessageClbk a_clbk)
	{
		_KXLogger = a_clbk;
	}

#pragma endregion 



	KXINPUT_API void KXInputUpdate()
	{
		_KXManager->Update();
		_KXLogger("KXUpdate Called!");
	}

}

#endif
