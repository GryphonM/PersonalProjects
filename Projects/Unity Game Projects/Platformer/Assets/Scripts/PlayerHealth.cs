using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHealth : MonoBehaviour
{
    [SerializeField] int maxStructureHealth = 8;
    [SerializeField] int maxBlobHealth = 4;
    int structureHealth;
    int blobHealth;

    // Start is called before the first frame update
    void Start()
    {
        structureHealth = maxStructureHealth;
        blobHealth = maxBlobHealth;
    }

    public void DamageObject(int damage)
    {
        if (PlayerManager.CurrentState == PlayerManager.State.Solid)
            structureHealth -= damage;
        else if (PlayerManager.CurrentState == PlayerManager.State.Ooze)
            blobHealth -= damage;

        if (structureHealth <= 0)
            PlayerManager.SetState(PlayerManager.State.Ooze);
        else if (blobHealth <= 0)
            PlayerManager.GameOver(gameObject);
    }
}
