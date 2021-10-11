using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimeKeeper : MonoBehaviour
{
    float time = 60;
    
    // Start is called before the first frame update
    void Start()
    {
        GetComponent<Text>().text = time.ToString("F0");
    }

    // Update is called once per frame
    void Update()
    {
        if (time <= 0)
        {
            DestroyBalls();
        }
        else
        {
            time -= Time.deltaTime;
            GetComponent<Text>().text = time.ToString("F0");
        }
    }

    private void DestroyBalls()
    {
        Ball[] balls = FindObjectsOfType<Ball>();
        foreach (Ball ball in balls)
        {
            ball.KillBall();
        }
    }
}
