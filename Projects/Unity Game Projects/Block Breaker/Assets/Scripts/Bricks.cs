using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bricks : MonoBehaviour
{
    [SerializeField] int health = 1;
    [SerializeField] Color startColor;
    [SerializeField] Color hurtColor;
    
    // Start is called before the first frame update
    void Start()
    {
        GetComponent<SpriteRenderer>().color = startColor;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        FindObjectOfType<LevelController>().IncreaseScore();
        DecreaseHealth(collision.gameObject.GetComponent<Ball>().damage);
    }

    private void DecreaseHealth(int damage)
    {
        health -= damage;
        if (health <= 0)
        {
            FindObjectOfType<LevelLoader>().DeductBrick();
            Destroy(gameObject);
        }
        else
            GetComponent<SpriteRenderer>().color = hurtColor;
    }
}
