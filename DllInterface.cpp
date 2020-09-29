#include "DllInterface.h"
#include <stdlib.h>

//静态变量需在cpp中先定义
void(*Debug::Log)(const char* message, int iSize);

void UnityLog(const char* message)
{
	Debug::Log(message, strlen(message));
}

float GetDistance(float x1, float y1, float x2, float y2)
{
	UnityLog("calculate distance");
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

UnManagedTestClass * CreateUnmanagedInstance()
{
	UnityLog("create unmanaged instance");
	return new UnManagedTestClass();
}

void DisposeUnmanaged(UnManagedTestClass * ptr)
{
	if (ptr != NULL)
	{
		UnityLog("delete unmanaged instance");
		delete ptr;
		ptr = NULL;
	}
}

void CallPassInt(UnManagedTestClass * ptr, int value)
{
	if (ptr!=NULL)
	{
		ptr->PassInt(value);
	}
}

void SetLogDelegate(void(*Log)(const char* message, int iSize))
{
	Debug::Log = Log;
	UnityLog("set unity log delegate");
}

UnManagedTestClass::UnManagedTestClass()
{
}

UnManagedTestClass::~UnManagedTestClass()
{
}

void UnManagedTestClass::PassInt(int value)
{
	char buffer[20];
	_itoa_s(value, buffer, 10);
	UnityLog("PassInt value:");
	UnityLog(buffer);
}

void UnManagedTestClass::PassString(const char * value)
{
	UnityLog("PassString value:");
	UnityLog(value);
}

const char * UnManagedTestClass::ReturnString()
{
	return "unmanaged return string";
}
