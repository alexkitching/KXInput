#ifndef __KXDEBUG_H__
#define __KXDEBUG_H__

typedef void(*KXLogMessageClbk)(const char* msg);
namespace Debug
{
	static KXLogMessageClbk _KXLogger;

	static void SetLogCallback(KXLogMessageClbk a_clbk)
	{
		_KXLogger = a_clbk;
	}

	static void Log(const char* a_str)
	{
		if(_KXLogger != nullptr)
		{
			_KXLogger(a_str);
		}
	}	
}

#endif