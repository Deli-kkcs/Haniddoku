using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MyGrid : MonoBehaviour
{
    public List<GameObject> list_temp_num; 

    public GameObject selected;
    public Text text_num;
    public int index_seen_in_map;
    public int x_in_map;
    public int y_in_map;
    public bool isSetIn;
    public void SelectGrid()
    {
        if(MapManager.instance.lastSelectedGrid)
        {
            MapManager.instance.lastSelectedGrid.selected.SetActive(false);
        }
        MapManager.instance.lastSelectedGrid = gameObject.GetComponent<MyGrid>();
        MapManager.instance.lastSelectedGrid.selected.SetActive(true);
    }
}
