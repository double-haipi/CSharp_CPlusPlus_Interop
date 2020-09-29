#pragma once
#include<math.h>
#include<string.h>
#include<iostream>
#define _DllExport extern "C" __declspec(dllexport) //使用宏定义缩写下

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

// C# call C++ 静态方法
_DllExport float  GetDistance(float x1, float y1, float x2, float y2);
//C#调用C++实例方法
_DllExport void DisposeUnmanaged(UnManagedTestClass* ptr);
_DllExport void CallPassInt(UnManagedTestClass* ptr, int value);

//设置C#层的委托给C++，C++即可调用C#方法
_DllExport void  SetLogDelegate(void(*Log)(const char* message, int iSize));

//创建C++对象，返回指针给C#
_DllExport UnManagedTestClass*  CreateUnmanagedInstance();

