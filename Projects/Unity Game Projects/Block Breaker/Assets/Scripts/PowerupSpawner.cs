//------------------------------------------------------------------------------
//
// File Name:	PowerupSpawner.cs
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

public class PowerupSpawner : MonoBehaviour
{
    // Determine where the powerups can be spawned
    [SerializeField] Vector2 lowerLeftSpawnArea;
    [SerializeField] Vector2 upperRightSpawnArea;

    // Randomize length between powerup spawns
    [SerializeField] float minTimerLength;
    [SerializeField] float maxTimerLength;
    float powerupTimer;

    // Game objects
    [SerializeField] GameObject powerupObject;
    Powerup powerupController;

    // Color to indicate what kind of powerup
    [Tooltip("The color of the powerup.\n0 Index = Speed\n1 Index = Size\n2 Index = Damge")]
    [SerializeField] Color[] powerupColors;
    
    // Start is called before the first frame update
    void Start()
    {
        powerupTimer = Random.Range(minTimerLength, maxTimerLength);
    }

    // Update is called once per frame
    void Update()
    {
        if (powerupTimer <= 0 && FindObjectOfType<Ball>() != null)
        {
            GameObject currentPowerup = Instantiate(powerupObject);
            powerupController = currentPowerup.GetComponent<Powerup>();

            // Determine powerup type
            int powerupIndex = Random.Range(0, 3);
            powerupController.powerupType = (Powerup.powerupTypes)powerupIndex;
            currentPowerup.GetComponent<SpriteRenderer>().color = powerupColors[powerupIndex];

            // Determine spawn location
            float xSpawn = Random.Range(lowerLeftSpawnArea.x, upperRightSpawnArea.x);
            float ySpawn = Random.Range(lowerLeftSpawnArea.y, upperRightSpawnArea.y);
            currentPowerup.transform.position = new Vector2(xSpawn, ySpawn);

            // Reset timer
            powerupTimer = Random.Range(minTimerLength, maxTimerLength);
        }

        // Only start timer if there are no other powerups active
        if (FindObjectOfType<Powerup>() == null)
        {
            powerupTimer -= Time.deltaTime;
        }
    }
}
