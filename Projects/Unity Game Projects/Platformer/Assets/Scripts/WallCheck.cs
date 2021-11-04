using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallCheck : MonoBehaviour
{
    [Tooltip("All Tags that the player can climb up")]
    [SerializeField] string[] Tags;

    PlayerController myPC;

    // Start is called before the first frame update
    void Start()
    {
        myPC = transform.parent.gameObject.GetComponent<PlayerController>();

        if (!GetComponent<CapsuleCollider2D>().IsTouchingLayers())
            myPC.SetTouchingWall(false);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        foreach (string tag in Tags)
        {
            if (collision.gameObject.CompareTag(tag))
                myPC.SetTouchingWall(true);
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        foreach (string tag in Tags)
        {
            if (collision.gameObject.CompareTag(tag))
                myPC.SetTouchingWall(false);
        }
    }
}
