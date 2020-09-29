#pragma once
#include<math.h>
#include<string.h>
#include<iostream>
#define _DllExport extern "C" __declspec(dllexport) //ʹ�ú궨����д��

//C++ Call C#
class Debug
{
public:
	static void(*Log)(const char* message, int iSize);
};

class UnManagedTestClass
{
public:
	UnManagedTestClass();
	~UnManagedTestClass();
	void PassInt(int value);
	void PassString(const char* value);
	const char* ReturnString();

private:

};

// C# call C++ ��̬����
_DllExport float  GetDistance(float x1, float y1, float x2, float y2);
//C#����C++ʵ������
_DllExport void DisposeUnmanaged(UnManagedTestClass* ptr);
_DllExport void CallPassInt(UnManagedTestClass* ptr, int value);

//����C#���ί�и�C++��C++���ɵ���C#����
_DllExport void  SetLogDelegate(void(*Log)(const char* message, int iSize));

//����C++���󣬷���ָ���C#
_DllExport UnManagedTestClass*  CreateUnmanagedInstance();

