using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Powerup : MonoBehaviour
{
    public enum powerUpTypes { speedIncrease, sizeIncrease, damageIncrease};
    public powerUpTypes powerupType;

    [SerializeField] float increasedSpeed;
    [SerializeField] float increasedSize;
    [Tooltip("The negative X position the Paddle can be without clipping through the wall.")]
    [SerializeField] float leftMoveLimit;
    [Tooltip("The positive X position the Paddle can be without clipping through the wall.")]
    [SerializeField] float rightMoveLimit;
    [SerializeField] int increasedDamage;
    [SerializeField] float speedTimer;
    [SerializeField] float sizeTimer;
    [SerializeField] float damageTimer;

    private Paddle gamePaddle;
    private Ball gameBall;

    private void Start()
    {
        gamePaddle = FindObjectOfType<Paddle>();
        gameBall = FindObjectOfType<Ball>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (powerupType == powerUpTypes.speedIncrease)
        {
            float ogSpeed = gamePaddle.speed;
            gamePaddle.speed = increasedSpeed;

            gamePaddle.SpeedPowerup(speedTimer, ogSpeed);
        }
        else if (powerupType == powerUpTypes.sizeIncrease)
        {
            float ogSize = gamePaddle.transform.localScale.x;
            float ogLowLimit = gamePaddle.leftLimit;
            float ogUpLimit = gamePaddle.rightLimit;
            gamePaddle.transform.localScale = new Vector3(increasedSize, gamePaddle.transform.localScale.y, gamePaddle.transform.localScale.z);
            gamePaddle.leftLimit = leftMoveLimit;
            gamePaddle.rightLimit = rightMoveLimit;

            gamePaddle.SizePowerup(sizeTimer, ogSize, ogLowLimit, ogUpLimit);
        }
        else if (powerupType == powerUpTypes.damageIncrease)
        {
            int ogDamage = gameBall.damage;
            gameBall.damage = increasedDamage;

            gameBall.DamagePowerup(damageTimer, ogDamage);
        }

        Destroy(gameObject);
    }
}
