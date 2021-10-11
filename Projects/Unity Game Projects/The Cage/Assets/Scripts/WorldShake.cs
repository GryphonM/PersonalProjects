using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WorldShake : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown("space"))
        {
            Shake();
        }
    }

    private void Shake()
    {
        float randomX = Random.Range(-500f, 500f);
        float randomY = Random.Range(-500f, 500f);

        Ball[] balls = FindObjectsOfType<Ball>();
        foreach(Ball ball in balls)
        {
            ball.GetComponent<Rigidbody2D>().AddForce(new Vector2(randomX, randomY));
        }
    }
}
