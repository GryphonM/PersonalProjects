//------------------------------------------------------------------------------
//
// File Name:	PlayerController.cs
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	GAM 5.1.3 CHALLENGE - Platformer
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [SerializeField] KeyCode moveLeft = KeyCode.A;
    [SerializeField] KeyCode moveRight = KeyCode.D;
    [SerializeField] KeyCode jump = KeyCode.Space;
    [SerializeField] KeyCode attack = KeyCode.Mouse1;

    [SerializeField] float walkSpeed = 5;

    [SerializeField] float jumpSpeed = 5;
    [Tooltip("How long the user can hold the jump button before they stop gaining height")]
    [SerializeField] float heightIncreaseTimer;
    float heightIncrease;
    bool grounded = false;

    [SerializeField] GameObject sword;
    [Tooltip("Time the Attack is visible")]
    [SerializeField] float attackTime;
    float attackTimer;
    [Tooltip("Time player must wait after attack finishes to attack again")]
    [SerializeField] float attackSeparation;
    float attackHold;
    bool attacking = false;
    bool canAttack = true;

    Rigidbody2D myRB;
    
    // Start is called before the first frame update
    void Start()
    {
        myRB = GetComponent<Rigidbody2D>();
        heightIncrease = heightIncreaseTimer;
        attackTimer = attackTime;
        attackHold = attackSeparation;
    }

    // Update is called once per frame
    void Update()
    {
        // Movement
        if ((Input.GetKey(moveRight) && Input.GetKey(moveLeft)) ||
            (Input.GetKeyUp(moveRight) || Input.GetKeyUp(moveLeft)))
        {
            Vector2 newVel = new Vector2(0, myRB.velocity.y);
            myRB.velocity = newVel;
        }
        else if (Input.GetKey(moveLeft))
        {
            Vector2 newVel = new Vector2(-walkSpeed, myRB.velocity.y);
            myRB.velocity = newVel;
        }
        else if (Input.GetKey(moveRight))
        {
            Vector2 newVel = new Vector2(walkSpeed, myRB.velocity.y);
            myRB.velocity = newVel;
        }

        // Jumping
        if (Input.GetKey(jump))
        {
            if (grounded)
            {
                Vector2 jumpVel = new Vector2(myRB.velocity.x, jumpSpeed);
                myRB.velocity = jumpVel;
            }
            else if (heightIncrease > 0)
            {
                Vector2 jumpVel = new Vector2(myRB.velocity.x, jumpSpeed);
                myRB.velocity = jumpVel;
                heightIncrease -= Time.deltaTime;
            }
        }

        if (Input.GetKeyUp(jump))
        {
            if (heightIncrease > 0)
                heightIncrease = 0;
        }

        // Attacking
        if (Input.GetKeyDown(attack) && !attacking && canAttack)
        {
            sword.SetActive(true);
            attacking = true;
            canAttack = false;
        }

        if (attacking)
        {
            if (attackTimer <= 0)
            {
                attacking = false;
                sword.SetActive(false);
                attackTimer = attackTime;
            }
            else
                attackTimer -= Time.deltaTime;
        }

        if (!attacking && !canAttack)
        {
            if (attackHold <= 0)
            {
                canAttack = true;
                sword.GetComponent<Sword>().canDamage = true;
                attackHold = attackSeparation;
            }
            else
                attackHold -= Time.deltaTime;
        }

        // Flip Sword
        if (Input.GetKeyDown(moveLeft) && sword.transform.localPosition.x > 0)
        {
            sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
        }

        if (Input.GetKeyDown(moveRight) && sword.transform.localPosition.x < 0)
        {
            sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
        }
    }

    public void SetGrounded(bool groundedState)
    {
        grounded = groundedState;

        if (groundedState)
            heightIncrease = heightIncreaseTimer;
    }
}
