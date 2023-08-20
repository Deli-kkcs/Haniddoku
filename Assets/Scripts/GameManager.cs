using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;
    //public static GameManager Instance
    //{
    //    get
    //    {
    //        if (instance == null)
    //        {
    //            instance = new GameManager();
    //        }
    //        return instance;
    //    }
    //}
    public int N = 9;
    void Awake()
    {
        instance = this;
    }

}
