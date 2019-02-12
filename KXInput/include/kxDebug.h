#ifndef __KXDEBUG_H__
#define __KXDEBUG_H__

typedef void(*KXLogMessageClbk)(const char* msg);
static KXLogMessageClbk _KXLogger;

#endif