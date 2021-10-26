using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sword : MonoBehaviour
{
    [SerializeField] int damage = 1;
    [Tooltip("How much the player is pushed back when it hits something.")]
    [SerializeField] float pushBack = 2.5f;

    [HideInInspector] public bool canDamage = true;
    private PlayerController myPC;

    private void Start()
    {
        myPC = transform.parent.gameObject.GetComponent<PlayerController>();
    }

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
                myPC.PushBack(pushBack);
            }
        }
        else if (collision.CompareTag("Wall"))
        {
            myPC.PushBack(pushBack);
        }
    }
}
