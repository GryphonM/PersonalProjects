using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        float randomX = Random.Range(-500f, 500f);
        float randomY = Random.Range(-500f, 500f);
        
        GetComponent<Rigidbody2D>().AddForce(new Vector2(randomX, randomY));
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        FindObjectOfType<ScoreKeeper>().IncreaseScore();
        Destroy(gameObject);
    }

    public void KillBall()
    {
        Destroy(gameObject);
    }
}
