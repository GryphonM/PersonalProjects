using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    public int damage = 1;
    
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(DelayStart());
    }

    private void Update()
    {
        if (Input.GetKeyDown("space"))
        {
            if (transform.position.y > FindObjectOfType<Paddle>().transform.position.y)
            {
                FindObjectOfType<LevelController>().RespawnPlayer();
                Destroy(gameObject);
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        LevelController lc = FindObjectOfType<LevelController>();

        if (collision.CompareTag("Out Of Bounds"))
        {
            lc.RespawnPlayer();
            Destroy(gameObject);
        }
        else if (collision.CompareTag("Powerup"))
        {
            // Do Nothing, Just Catch This Case So Player Doesn't Die
        }
        else
        {
            lc.DecreaseLives();
            Destroy(gameObject);
        }
    }

    IEnumerator DelayStart()
    {
        yield return new WaitForSeconds(2);
        GetComponent<Rigidbody2D>().AddForce(new Vector2(250f, 250f));
    }

    public void DamagePowerup(float length, int originalDamage)
    {
        StartCoroutine(Damage(length, originalDamage));
    }
    
    IEnumerator Damage(float length, int originalDamage)
    {
        yield return new WaitForSeconds(length);
        damage = originalDamage;
    }
}
