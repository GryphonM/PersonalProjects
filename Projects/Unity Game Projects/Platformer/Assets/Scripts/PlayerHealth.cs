using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHealth : MonoBehaviour
{
    [SerializeField] int maxStructureShield = 6;
    [SerializeField] int maxBlobHealth = 3;
    int shield;
    int health;

    PlayerController myPC;

    // Start is called before the first frame update
    void Start()
    {
        shield = maxStructureShield;
        health = maxBlobHealth;

        myPC = GetComponent<PlayerController>();
    }

    public void DamagePlayer(int damage)
    {
        if (PlayerManager.CurrentState == PlayerManager.State.Solid)
            shield -= damage;
        else if (PlayerManager.CurrentState == PlayerManager.State.Ooze)
            health -= damage;

        if (shield <= 0)
            myPC.SetState(PlayerManager.State.Ooze);
        
        if (health <= 0)
            PlayerManager.GameOver(gameObject);
    }
}
