using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sword : MonoBehaviour
{
    [SerializeField] int damage = 1;
    [HideInInspector] public bool canDamage = true;

    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.CompareTag("Enemy"))
        {
            if (canDamage)
            {
                Health attackHealth = collision.gameObject.GetComponent<Health>();
                if (attackHealth != null)
                {
                    attackHealth.DamageObject(damage);

                }
                canDamage = false;
            }
        }
    }
}
