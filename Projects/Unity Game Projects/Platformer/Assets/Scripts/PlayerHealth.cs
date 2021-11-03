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

    // Update is called once per frame
    void Update()
    {
        
    }

    public void DamageObject(int damage)
    {
        if (PlayerManager.CurrentState == PlayerManager.State.Structure)
            structureHealth -= damage;
        else if (PlayerManager.CurrentState == PlayerManager.State.Blob)
            blobHealth -= damage;

        if (structureHealth <= 0)
            PlayerManager.ChangeState(PlayerManager.State.Blob);
        else if (blobHealth <= 0)
            PlayerManager.GameOver(gameObject);
    }
}
