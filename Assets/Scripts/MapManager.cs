using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using static System.Runtime.CompilerServices.RuntimeHelpers;

public class MapManager : MonoBehaviour
{
    public static MapManager instance;

    public GameObject map;
    public MyGrid prefab_grid;
    [HideInInspector]
    public MyGrid lastSelectedGrid;

    public List<MyGrid> list_grid;
    //TODO   public List<int> list_index_emptyGrid;
    int[,,] usedNum;
    private List<KeyCode> list_keyCode_num = new List<KeyCode>() 
    {
        KeyCode.Keypad0,
        KeyCode.Keypad1,
        KeyCode.Keypad2,
        KeyCode.Keypad3,
        KeyCode.Keypad4,
        KeyCode.Keypad5,
        KeyCode.Keypad6,
        KeyCode.Keypad7,
        KeyCode.Keypad8,
        KeyCode.Keypad9,

        KeyCode.Alpha0,
        KeyCode.Alpha1,
        KeyCode.Alpha2,
        KeyCode.Alpha3,
        KeyCode.Alpha4,
        KeyCode.Alpha5,
        KeyCode.Alpha6,
        KeyCode.Alpha7,
        KeyCode.Alpha8,
        KeyCode.Alpha9,

        
    };
    private int count_solution;
    private float delta_x = 86.6025f;
    private float delta_y = 75f;
    public bool isSetTemp;
    void Awake()
    {
        instance = this;
    }
    void Start()
    {
        instance.usedNum = new int[3,(int)(GameManager.instance.N * 1.5) + 1,10];//三个方向上使用过的数字 0:斜率为0的方向 1:斜率为负根号3的方向 2:斜率为正根号3的方向

        CreateFullGrid();
        ProduceFullSodokuByText();
    }
    public void Update()
    {
        TryInputNum();
    }
    public void Initialize_before_produce()
    {
        for (int direction = 0; direction < 3; direction++)
        {
            for (int line = 1; line < (int)(GameManager.instance.N * 1.5) + 1; line++)
            {
                for (int num = 1; num <= 9; num++)
                {
                    instance.usedNum[direction,line,num] = 0;//0:在第direction个方向上的第line行未使用过num
                }
            }
        }
        //TODO    instance.list_index_emptyGrid.Clear();
        for (int i = 0; i < instance.list_grid.Count; i++)
        {
            instance.list_grid[i].text_num.text = string.Empty;
            //TODO    instance.list_index_emptyGrid.Add(i+1);
        }
        instance.count_solution = 0;
    }
    public void CreateFullGrid()
    {
        int shortest = GameManager.instance.N / 2 + 1;//最短边的长度 N = 9  =>  shortest = 5
        for (int line = 1; line <= GameManager.instance.N; line++)
        {
            int column = 1;
            if (line <= shortest)
            {
                column = shortest - line + 1;
                for (; column <= GameManager.instance.N; column++)
                {
                    CreateOneGrid(line, column);
                }
                continue;
            }
            for (; column <= GameManager.instance.N - (line - shortest); column++)
            {
                CreateOneGrid(line, column);
            }
        }
    }
    
    public void CreateOneGrid(int line , int column)
    {
        GameObject t = Instantiate(instance.prefab_grid.gameObject, Vector3.zero, instance.prefab_grid.gameObject.transform.rotation, instance.map.transform);
        t.GetComponent<RectTransform>().localPosition = new Vector3(0 + line * instance.delta_x + (column - 1) * instance.delta_x / 2, 0 - column * instance.delta_y, 0);
        t.GetComponent<MyGrid>().index_seen_in_map = instance.list_grid.Count;
        t.GetComponent<MyGrid>().x_in_map = line;
        t.GetComponent<MyGrid>().y_in_map = column;
        instance.list_grid.Add(t.GetComponent<MyGrid>());
    }

    public void ProduceFullSodokuByText()
    {
        Initialize_before_produce();
        //0000000000000000000000000000000000000000000000000000000000000
        //string seed = "3070600001202000006000002000000000550009000000005000001000000";//online 8.20
        //string seed = "6453741625353274863278164526319587451487236456238762154334765";//hard 1.1
        
        //string seed = "0004000700000000002000000000000000000000000000800250420070530";//easy 5
        //string seed = "5634248765335124762769853464273918535892476436875251426376534";//easy 5.1
        string seed = "5634248765335124762769853464973182535892476436875251426376534";//easy 5.2
        
        for (int i=0; i<instance.list_grid.Count;i++)
        {
            if (seed[i] == '0') continue;
            instance.list_grid[i].isSetIn = true;
            instance.list_grid[i].text_num.text = seed[i].ToString();
            CanSetNum(instance.list_grid[i].x_in_map, instance.list_grid[i].y_in_map, instance.list_grid[i].index_seen_in_map, true);
        }
    }
    //public void ProduceFullSodoku()
    //{
    //    Initialize_before_produce();
    //    int count_random = 10;
    //    for(int randomed = 0;randomed< count_random;randomed++)
    //    {
    //        int randomIndex_grid = UnityEngine.Random.Range(0, instance.list_index_emptyGrid.Count);
    //        int randomNum = UnityEngine.Random.Range(0, 9);

    //    }
    //}

    bool CanSetNum(int x, int y, int index_gird, bool isProducingSodoku)//判断三个方向是否有重复数字,能放置则放且返回TRUE,or不放且返回FALSE
    {
        int[] direction = new int[3] { x, y, x + y - 1 };//将map中的坐标x,y 转换为三个方向上的行序号
        if (isProducingSodoku)
        {
            for (int dir = 0; dir < 3; dir++)
            {
                if (instance.usedNum[dir, direction[dir], int.Parse(instance.list_grid[index_gird].text_num.text)] == 1)
                {
                    return false;
                }
            }
            for (int dir = 0; dir < 3; dir++)
            {
                instance.usedNum[dir, direction[dir], int.Parse(instance.list_grid[index_gird].text_num.text)] = 1;
            }
            return true;
        }
        return false;
    }

    public void TryInputNum()
    {
        if (!instance.lastSelectedGrid)
        {
            return;
        }
        if(instance.lastSelectedGrid.isSetIn)
        {
            return;
        }
        KeyCode t = getKeyDownCode();
        
        if (!instance.list_keyCode_num.Contains(t))
        {
            return;
        }
        string t2 = Change_keyCode_to_num(t.ToString());
        if(t2 == "0")
        {
            instance.lastSelectedGrid.text_num.text = string.Empty;
            return;
        }
        if(instance.isSetTemp)
        {
            instance.lastSelectedGrid.list_temp_num[int.Parse(t2)].SetActive(!instance.lastSelectedGrid.list_temp_num[int.Parse(t2)].activeSelf);
            return;
        }
        instance.lastSelectedGrid.text_num.text = t2;
        instance.lastSelectedGrid.text_num.color = Color.white;
    }
    public string Change_keyCode_to_num(string a)
    {
        if (a[0] == 'A')
        {
            a = a.Substring(5, 1);
            return a;
        }
        a = a.Substring(6, 1);
        return a;
    }
    public KeyCode getKeyDownCode()
    {
        if (!Input.anyKeyDown)
            return KeyCode.None;
        foreach (KeyCode keyCode in Enum.GetValues(typeof(KeyCode)))
        {
            if (Input.GetKeyDown(keyCode))
            {
                return keyCode;
            }
        }
        return KeyCode.None;
    }
}
