using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public GameObject SetTemp_OFF;
    public GameObject SetTemp_ON;

    public void ChangeSetTemp()
    {
        if(MapManager.instance.isSetTemp)
        {
            SetTemp_OFF.SetActive(true);
            SetTemp_ON.SetActive(false);
            MapManager.instance.isSetTemp = !MapManager.instance.isSetTemp;
            return;
        }
        SetTemp_OFF.SetActive(false);
        SetTemp_ON.SetActive(true);
        MapManager.instance.isSetTemp = !MapManager.instance.isSetTemp;
    }
    public void Update()
    {
        if(Input.GetKeyDown(KeyCode.KeypadDivide))
        {
            ChangeSetTemp();
        }
    }
}
