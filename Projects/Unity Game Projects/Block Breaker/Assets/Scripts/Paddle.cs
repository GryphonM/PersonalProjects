//------------------------------------------------------------------------------
//
// File Name:	Paddle.cs
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

public class Paddle : MonoBehaviour
{
    // Movement Variables
    public float speed;
    public float leftLimit = -5.5f;
    public float rightLimit = 5.5f;

    // The Level Controller in the scene
    LevelController lc;
    
    // Start is called before the first frame update
    void Start()
    {
        transform.position = new Vector2(0f, -4.5f);
        lc = FindObjectOfType<LevelController>();
    }

    // Update is called once per frame
    void Update()
    {
        // Movement
        if (Input.GetKey("left") && transform.position.x >= leftLimit)
            GetComponent<Rigidbody2D>().velocity = new Vector2(-speed, 0f);
        else if (Input.GetKey("right") && transform.position.x <= rightLimit)
            GetComponent<Rigidbody2D>().velocity = new Vector2(speed, 0f);
        else
            GetComponent<Rigidbody2D>().velocity = new Vector2(0f, 0f);
    }

    // Starts the Speed Powerup coroutine, which increases the speed of the paddle
    // Params:
    //   length = the amount of time the powerup is active
    //   originalSpeed = the base speed that the paddle had
    public void SpeedPowerup(float length, float originalSpeed)
    {
        StartCoroutine(Speed(length, originalSpeed));
    }

    // Starts the Size Powerup coroutine, which increases the size of the paddle
    // Params:
    //   length = the amount of time the powerup is active
    //   originalSize = the base size that the paddle was
    //   originalLowerLimit = the furthest left the paddle could originally move
    //   originalUpperLimit = the furthest right the paddle could originally mvoe
    public void SizePowerup(float length, float originalSize, float originalLowerLimit, float originalUpperLimit)
    {
        StartCoroutine(Size(length, originalSize, originalLowerLimit, originalUpperLimit));
    }

    // Turns the paddle's speed back to normal after the speed legnth
    // Params:
    //   length = the amount of time the powerup is active
    //   originalSpeed = the base damage that the ball had
    IEnumerator Speed(float length, float originalSpeed)
    {
        yield return new WaitForSeconds(length);

        // Reset Values
        speed = originalSpeed;
        lc.updatePowerupText(Color.white);
    }

    // Turns the paddle back to normal after the size legnth
    // Params:
    //   length = the amount of time the powerup is active
    //   originalSize = the base damage that the ball had
    //   originalLowerLimit = the furthest left the paddle could originally move
    //   originalUpperLimit = the furthest right the paddle could originally move
    IEnumerator Size(float length, float originalSize, float originalLowerLimit, float originalUpperLimit)
    {
        yield return new WaitForSeconds(length);

        // Reset Values
        transform.localScale = new Vector3(originalSize, transform.localScale.y, transform.localScale.z);
        leftLimit = originalLowerLimit;
        rightLimit = originalUpperLimit;
        lc.updatePowerupText(Color.white);
    }
}
