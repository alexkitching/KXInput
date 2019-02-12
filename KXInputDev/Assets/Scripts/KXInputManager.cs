using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class KXInputManager : MonoBehaviour
{
    [DllImport("KXInput", EntryPoint = "InitKXInput")]
    private static extern bool InitKXInput();
    [DllImport("KXInput", EntryPoint = "CleanupKXInput")]
    private static extern void CleanupKXInput();

    private delegate void KXLogger(string a_message);
    [DllImport("KXInput", EntryPoint = "SetLoggerClbk")]
    private static extern void SetLoggerClbk(KXLogger a_logger);

    [DllImport("KXInput")]
    private static extern void KXInputUpdate();

    private bool _initialised = false;

    void Awake()
    {
        _initialised = InitKXInput();

        if (_initialised)
        {
            SetLoggerClbk(KXLog);
        }
        else
        {
            Debug.LogError("KXInput Initialisation Failed");
        }
    }

    void KXLog(string a_message)
    {
        Debug.Log(a_message);
    }

    void Update()
    {
        if (_initialised)
        {
            KXInputUpdate();
        }
    }


    void OnDestroy()
    {
        CleanupKXInput();
    }

}
