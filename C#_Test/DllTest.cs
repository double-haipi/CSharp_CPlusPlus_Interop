using System;
using System.Net.Mime;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using AOT;
using System.Runtime.InteropServices;
public class DllTest : MonoBehaviour
{
    private GameObject cube1;
    private GameObject cube2;

    // Use this for initialization
    void Start()
    {
        cube1 = GameObject.Find("Cube1");
        cube2 = GameObject.Find("Cube2");
        DllInterface.SetLogDelegate(DllInterface.LogMessageFromCpp);
        PrintDistanceViaUnity();
        IntPtr unmanagedInstance = DllInterface.CreateUnmanagedInstance();
        Debug.Log("unmanaged ptr:" + unmanagedInstance);
        DllInterface.CallPassInt(unmanagedInstance, 10);
        DllInterface.CallPassInt(DllInterface.CreateUnmanagedInstance(), 20);
        DllInterface.DisposeUnmanaged(unmanagedInstance);
        unmanagedInstance = IntPtr.Zero;

        XhrTest();
    }

    void XhrTest()
    {
        DllInterface.SetCreateManagedXhrDelegate(DllInterface.CreateManagedXhr);
        DllInterface.SetSendDelegate(DllInterface.Send);
        DllInterface.CreateXHRTest();
        DllInterface.AbortCallBackToUnmanaged(DllInterface.instancePtr,404,"custom closed");
    }

    void PrintDistanceViaUnity()
    {
        var pos1 = cube1.transform.position;
        var pos2 = cube2.transform.position;
        Debug.Log("This is a log from Unity");
        Debug.Log("Distance:" + DllInterface.GetDistance(pos1.x, pos1.y, pos2.x, pos2.y));
    }
}
