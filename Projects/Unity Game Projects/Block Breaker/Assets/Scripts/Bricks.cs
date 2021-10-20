//------------------------------------------------------------------------------
//
// File Name:	Bricks.cs
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	GAM 5.1.2 Assignment - Cage and Breaker Challenges
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bricks : MonoBehaviour
{
    // How many hits the brick can take
    [SerializeField] int health = 1;

    // Color of the brick
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

    // Damages the brick and determines if it is destroyed
    // Params:
    //   damage = how much damage the brick took
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
