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

    [SerializeField] GameObject Powerup;
    Powerup powerupController;
    
    // Start is called before the first frame update
    void Start()
    {
        powerupTimer = Random.Range(minTimerLength, maxTimerLength);
    }

    // Update is called once per frame
    void Update()
    {
        if (powerupTimer <= 0)
        {
            GameObject currentPowerup = Instantiate(Powerup);
            powerupController = currentPowerup.GetComponent<Powerup>();
            int powerupIndex = Random.Range(0, 2);
            powerupController.powerupType = (Powerup.powerUpTypes)powerupIndex;
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
