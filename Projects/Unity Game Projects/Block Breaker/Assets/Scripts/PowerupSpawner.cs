using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PowerupSpawner : MonoBehaviour
{
    [SerializeField] Vector2 lowerLeftSpawnArea;
    [SerializeField] Vector2 upperRightSpawnArea;

    [SerializeField] float minTimerLength;
    [SerializeField] float maxTimerLength;
    float powerupTimer;

    [SerializeField] GameObject PowerupObject;
    Powerup powerupController;

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
            GameObject currentPowerup = Instantiate(PowerupObject);
            powerupController = currentPowerup.GetComponent<Powerup>();

            int powerupIndex = Random.Range(0, 3);
            powerupController.powerupType = (Powerup.powerUpTypes)powerupIndex;
            currentPowerup.GetComponent<SpriteRenderer>().color = powerupColors[powerupIndex];

            float xSpawn = Random.Range(lowerLeftSpawnArea.x, upperRightSpawnArea.x);
            float ySpawn = Random.Range(lowerLeftSpawnArea.y, upperRightSpawnArea.y);
            currentPowerup.transform.position = new Vector2(xSpawn, ySpawn);

            powerupTimer = Random.Range(minTimerLength, maxTimerLength);
        }

        if (FindObjectOfType<Powerup>() == null)
        {
            powerupTimer -= Time.deltaTime;
        }
    }
}
