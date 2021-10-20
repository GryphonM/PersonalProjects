//------------------------------------------------------------------------------
//
// File Name:	Ball.cs
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

public class Ball : MonoBehaviour
{
    // The damage the ball does to the bricks
    public int damage = 1;

    // Whether or not the extra damage powerup is active
    bool extraDamage;

    // The level controller in the scene
    LevelController lc;
    
    // Start is called before the first frame update
    void Start()
    {
        lc = FindObjectOfType<LevelController>();
        StartCoroutine(DelayStart());
    }

    // Update is called once per frame
    private void Update()
    {
        // Allow player to reset the ball if it softlocks without losing a life
        if (Input.GetKeyDown("space"))
        {
            if (transform.position.y > FindObjectOfType<Paddle>().transform.position.y)
            {
                if (extraDamage)
                    lc.updatePowerupText(Color.white);

                FindObjectOfType<LevelController>().RespawnPlayer();
                Destroy(gameObject);
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        // Catch if the ball accidentally left the cage
        if (collision.CompareTag("Out Of Bounds"))
        {
            if (extraDamage)
                lc.updatePowerupText(Color.white);

            lc.RespawnPlayer();
            Destroy(gameObject);
        }
        else if (collision.CompareTag("Powerup"))
        {
            // Do Nothing, Just Catch This Case So Player Doesn't Die
        }
        else
        {
            if (extraDamage)
                lc.updatePowerupText(Color.white);

            lc.DecreaseLives();
            Destroy(gameObject);
        }
    }

    // Pauses the ball for 2 seconds
    IEnumerator DelayStart()
    {
        yield return new WaitForSeconds(2);
        GetComponent<Rigidbody2D>().AddForce(new Vector2(250f, 250f));
    }

    // Starts the Damage Powerup coroutine, which increases the damage of the ball
    // Params:
    //   length = the amount of time the powerup is active
    //   originalDamage = the base damage that the ball had
    public void DamagePowerup(float length, int originalDamage)
    {
        extraDamage = true;
        StartCoroutine(Damage(length, originalDamage));
    }

    // Turns the ball back to normal after the damage legnth
    // Params:
    //   length = the amount of time the powerup is active
    //   originalDamage = the base damage that the ball had
    IEnumerator Damage(float length, int originalDamage)
    {
        yield return new WaitForSeconds(length);

        // Reset values
        damage = originalDamage;
        extraDamage = false;
        lc.updatePowerupText(Color.white);
    }
}
