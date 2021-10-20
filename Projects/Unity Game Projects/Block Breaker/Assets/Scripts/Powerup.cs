//------------------------------------------------------------------------------
//
// File Name:	Powerup.cs
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

public class Powerup : MonoBehaviour
{
    // Powerup Typing
    public enum powerupTypes { speedIncrease, sizeIncrease, damageIncrease};
    public powerupTypes powerupType;

    // Speed Variables
    [SerializeField] float increasedSpeed;
    [SerializeField] float speedTimer;

    // Size Variables
    [SerializeField] float increasedSize;
    [Tooltip("The negative X position the Paddle can be without clipping through the wall.")]
    [SerializeField] float leftMoveLimit;
    [Tooltip("The positive X position the Paddle can be without clipping through the wall.")]
    [SerializeField] float rightMoveLimit;
    [SerializeField] float sizeTimer;

    // Damage Variables
    [SerializeField] int increasedDamage;
    [SerializeField] float damageTimer;

    // Game Objects
    private Paddle gamePaddle;
    private Ball gameBall;
    LevelController lc;

    // Start is called before the first frame update
    private void Start()
    {
        // We only need the paddle if the powerup accesses the paddle
        if (powerupType != powerupTypes.damageIncrease)
            gamePaddle = FindObjectOfType<Paddle>();

        lc = FindObjectOfType<LevelController>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (powerupType == powerupTypes.speedIncrease)
        {
            // Update speed
            float ogSpeed = gamePaddle.speed;
            gamePaddle.speed = increasedSpeed;

            lc.updatePowerupText(GetComponent<SpriteRenderer>().color, (int)powerupType);

            // Initiate the powerup on the paddle
            gamePaddle.SpeedPowerup(speedTimer, ogSpeed);
        }
        else if (powerupType == powerupTypes.sizeIncrease)
        {
            // Save original values
            float ogSize = gamePaddle.transform.localScale.x;
            float ogLowLimit = gamePaddle.leftLimit;
            float ogUpLimit = gamePaddle.rightLimit;

            // Update Size
            gamePaddle.transform.localScale = new Vector3(increasedSize, gamePaddle.transform.localScale.y, gamePaddle.transform.localScale.z);
            gamePaddle.leftLimit = leftMoveLimit;
            gamePaddle.rightLimit = rightMoveLimit;

            lc.updatePowerupText(GetComponent<SpriteRenderer>().color, (int)powerupType);

            // Initiate the powerup on the paddle
            gamePaddle.SizePowerup(sizeTimer, ogSize, ogLowLimit, ogUpLimit);
        }
        else if (powerupType == powerupTypes.damageIncrease)
        {
            // Find ball here so the powerup doesn't lose track of the ball (i.e. if it dies)
            gameBall = FindObjectOfType<Ball>();
            
            // Update damage
            int ogDamage = gameBall.damage;
            gameBall.damage = increasedDamage;

            lc.updatePowerupText(GetComponent<SpriteRenderer>().color, (int)powerupType);

            // Initiate the powerup on the ball
            gameBall.DamagePowerup(damageTimer, ogDamage);
        }

        Destroy(gameObject);
    }
}
