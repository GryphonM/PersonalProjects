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
    bool pushedBack = false;

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
        if (!GameManager.Paused)
        {

            // Movement
            {
                if (!pushedBack)
                {
                    if ((Input.GetKey(GameManager.Controls.MoveRight) && Input.GetKey(GameManager.Controls.MoveLeft)) ||
                        (Input.GetKeyUp(GameManager.Controls.MoveRight) || Input.GetKeyUp(GameManager.Controls.MoveLeft)))
                    {
                        Vector2 newVel = new Vector2(0, myRB.velocity.y);
                        myRB.velocity = newVel;
                        myAnim.SetBool("Walking", false);
                    }
                    else if (Input.GetKey(GameManager.Controls.MoveLeft))
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
                    else if (Input.GetKey(GameManager.Controls.MoveRight))
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
                }
            }

            // Jumping
            {
                Vector2 jumpVel = new Vector2(myRB.velocity.x, jumpSpeed);

                if (Input.GetKey(GameManager.Controls.Jump))
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

                if (Input.GetKeyUp(GameManager.Controls.Jump))
                {
                    if (heightIncrease > 0)
                        heightIncrease = 0;
                }

                if (Input.GetKeyDown(GameManager.Controls.Jump) && !grounded && jumpsLeft > 0)
                {
                    jumpVel.y = doubleJumpSpeed;
                    myRB.velocity = jumpVel;
                    jumpsLeft--;
                }
            }

            // Attacking
            {
                if (Input.GetKeyDown(GameManager.Controls.Attack) && !attacking && canAttack)
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
                        pushedBack = false;
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
            }

            // Flip Sword
            {
                if (Input.GetKeyDown(GameManager.Controls.MoveLeft) && sword.transform.localPosition.x > 0)
                {
                    sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
                    sword.GetComponent<SpriteRenderer>().flipX = facingRight;
                }

                if (Input.GetKeyDown(GameManager.Controls.MoveRight) && sword.transform.localPosition.x < 0)
                {
                    sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
                    sword.GetComponent<SpriteRenderer>().flipX = facingRight;
                }
            }
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

    public void PushBack(float force)
    {
        pushedBack = true;
        Vector2 pushVel = myRB.velocity;

        if (facingRight)
            pushVel.x = force;
        else
            pushVel.x = -force;

        myRB.velocity = pushVel;
    }
}
