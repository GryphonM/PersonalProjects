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

    [Space(15)]

    [SerializeField] float walkSpeed = 5;

    [Space(15)]

    [SerializeField] float jumpSpeed = 5;
    [Tooltip("How long the user can hold the jump button before they stop gaining height")]
    [SerializeField] float heightIncreaseTimer;
    [SerializeField] int extraJumps;
    [SerializeField] float doubleJumpSpeed = 10;
    int jumpsLeft;
    float heightIncrease;
    bool grounded = false;

    [Space(15)]

    [SerializeField] GameObject sword;
    [Tooltip("Time the Attack is active")]
    [SerializeField] float attackTime;
    float attackTimer;
    [Tooltip("Time player must wait after attack finishes to attack again")]
    [SerializeField] float attackSeparation;
    float attackHold;
    bool attacking = false;
    bool canAttack = true;

    Rigidbody2D myRB;
    Animator myAnim;
    SpriteRenderer mySR;
    bool facingRight = true;
    
    // Start is called before the first frame update
    void Start()
    {
        myRB = GetComponent<Rigidbody2D>();
        myAnim = GetComponent<Animator>();
        mySR = GetComponent<SpriteRenderer>();

        heightIncrease = heightIncreaseTimer;
        attackTimer = attackTime;
        attackHold = attackSeparation;
        jumpsLeft = extraJumps;
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
            myAnim.SetBool("Walking", false);
        }
        else if (Input.GetKey(moveLeft))
        {
            Vector2 newVel = new Vector2(-walkSpeed, myRB.velocity.y);
            myRB.velocity = newVel;

            myAnim.SetBool("Walking", true);
            if (!facingRight)
            {
                facingRight = !facingRight;
            }
            mySR.flipX = facingRight;
        }
        else if (Input.GetKey(moveRight))
        {
            Vector2 newVel = new Vector2(walkSpeed, myRB.velocity.y);
            myRB.velocity = newVel;

            myAnim.SetBool("Walking", true);
            if (facingRight)
            {
                facingRight = !facingRight;
            }
            mySR.flipX = facingRight;
        }

        // Jumping
        {
            Vector2 jumpVel = new Vector2(myRB.velocity.x, jumpSpeed);

            if (Input.GetKey(jump))
            {
                if (grounded)
                {
                    myRB.velocity = jumpVel;
                }
                else if (heightIncrease > 0)
                {
                    myRB.velocity = jumpVel;
                    heightIncrease -= Time.deltaTime;
                }
            }

            if (Input.GetKeyUp(jump))
            {
                if (heightIncrease > 0)
                    heightIncrease = 0;
            }

            if (Input.GetKeyDown(jump) && !grounded && jumpsLeft > 0)
            {
                jumpVel.y = doubleJumpSpeed;
                myRB.velocity = jumpVel;
                jumpsLeft--;
            }
        }

        // Attacking
        if (Input.GetKeyDown(attack) && !attacking && canAttack)
        {
            sword.SetActive(true);
            myAnim.SetBool("Attacking", true);
            attacking = true;
            canAttack = false;
        }

        if (attacking)
        {
            if (attackTimer <= 0)
            {
                attacking = false;
                sword.SetActive(false);
                myAnim.SetBool("Attacking", false);
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
        myAnim.SetBool("Grounded", grounded);

        if (grounded)
        {
            heightIncrease = heightIncreaseTimer;
            jumpsLeft = extraJumps;
        }
    }
}
