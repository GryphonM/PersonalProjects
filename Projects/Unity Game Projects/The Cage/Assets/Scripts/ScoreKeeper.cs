using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreKeeper : MonoBehaviour
{
    int score = 0;
    
    // Start is called before the first frame update
    void Start()
    {
        GetComponent<Text>().text = score.ToString();
    }

    public void IncreaseScore()
    {
        score++;
        GetComponent<Text>().text = score.ToString();
    }
}
