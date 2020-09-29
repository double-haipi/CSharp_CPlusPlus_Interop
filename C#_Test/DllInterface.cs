using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Runtime.InteropServices;
using AOT;
using size_t = System.UIntPtr;

public class DllInterface
{
    [DllImport("DLLTest")]
    public static extern float GetDistance(float x1, float y1, float x2, float y2);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LogDelegate(IntPtr message, int iSize);

    [DllImport("DLLTest")]
    public static extern void SetLogDelegate(LogDelegate log);

    //C# Function for C++'s call
    [MonoPInvokeCallback(typeof(LogDelegate))]
    public static void LogMessageFromCpp(IntPtr message, int iSize)
    {
        Debug.Log(Marshal.PtrToStringAnsi(message, iSize));
    }

    [DllImport("DLLTest")]
    public static extern IntPtr CreateUnmanagedInstance();

    [DllImport("DLLTest")]
    public static extern void DisposeUnmanaged(IntPtr ptr);

    [DllImport("DLLTest", CallingConvention = CallingConvention.ThisCall)]
    public static extern void CallPassInt(IntPtr ptr, int value);



    //定义委托类型
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void CreateManagedXhrDelegate(IntPtr ptr);

    public static IntPtr instancePtr;
    [MonoPInvokeCallback(typeof(CreateManagedXhrDelegate))]
    public static void CreateManagedXhr(IntPtr ptr)
    {
        Debug.Log("unmanaged instance ptr:" + ptr);
        instancePtr = ptr;
    }

    [DllImport("DLLTest")]
    public static extern void SetCreateManagedXhrDelegate(CreateManagedXhrDelegate createDelegate);

    [DllImport("DLLTest")]
    public static extern void CreateXHRTest();

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void SendDelegate(IntPtr ptr, IntPtr data, int dataSize);

    [MonoPInvokeCallback(typeof(SendDelegate))]
    public static void Send(IntPtr ptr, IntPtr data, int dataSize)
    {
        Debug.Log("send func, instance ptr:" + ptr);
        Debug.Log("data:" + Marshal.PtrToStringAnsi(data, dataSize));
    }

    [DllImport("DLLTest")]
    public static extern void SetSendDelegate(SendDelegate sendDelegate);

    [DllImport("DLLTest")]
    public static extern void AbortCallBackToUnmanaged(IntPtr ptr, int code, string reason);
}
