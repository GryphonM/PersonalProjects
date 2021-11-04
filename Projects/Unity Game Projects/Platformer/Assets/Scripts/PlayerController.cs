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
    public PlayerManager.State currState;
    [Space(5)]
    [SerializeField] float oozeWalkSpeed;
    [SerializeField] float solidWalkSpeed;
    float walkSpeed;

    [Space(20)]

    [SerializeField] float oozeJumpSpeed;
    [SerializeField] float solidJumpSpeed;
    float jumpSpeed;
    [Space(5)]
    [Tooltip("While in ooze form, how long the user can hold the jump button before they stop gaining height")]
    [SerializeField] float oozeHeightIncreaseTimer;
    [Tooltip("While in solid form, how long the user can hold the jump button before they stop gaining height")]
    [SerializeField] float solidHeightIncreaseTimer;
    float heightIncreaseTimer;
    [Space(5)]
    [SerializeField] int oozeExtraJumps;
    [SerializeField] int solidExtraJumps;
    int extraJumps;
    [Space(5)]
    [SerializeField] float oozeExtraJumpSpeed;
    [SerializeField] float solidExtraJumpSpeed;
    float extraJumpSpeed = 10;

    int jumpsLeft;
    float heightIncrease;
    bool grounded = false;

    [Space(20)]

    [SerializeField] GameObject sword;
    [Space(5)]
    [Tooltip("Time the Ooze Attack is active")]
    [SerializeField] float oozeAttackTime;
    [Tooltip("Time the Solid Attack is active")]
    [SerializeField] float solidAttackTime;
    float attackTime;
    float attackTimer;
    [Space(5)]
    [Tooltip("Time player must wait after attack finishes to attack again when they are in ooze form")]
    [SerializeField] float oozeAttackSeperation;
    [Tooltip("Time player must wait after attack finishes to attack again when they are in solid form")]
    [SerializeField] float solidAttackSeperation;
    float attackSeparation;
    float attackHold;
    [Space(5)]
    [SerializeField] int oozeDamage;
    [SerializeField] int solidDamage;

    bool attacking = false;
    bool canAttack = true;
    bool pushedBack = false;

    [SerializeField] GameObject wallCheck;
    [SerializeField] float climbSpeed;
    [SerializeField] Vector2 climbJumpSpeed;
    [Tooltip("If You climb to bottom of wall, how far are you pushed away from the wall?")]
    [SerializeField] float wallReleaseSpeed = 0.3f;
    bool touchingWall;
    bool climbing;
    bool climbJumping;

    
    Rigidbody2D myRB;
    Animator myAnim;
    SpriteRenderer mySR;
    bool facingRight = true;
    float ogGravity;
    
    // Start is called before the first frame update
    void Start()
    {
        myRB = GetComponent<Rigidbody2D>();
        myAnim = GetComponent<Animator>();
        mySR = GetComponent<SpriteRenderer>();

        SetState(PlayerManager.State.Solid);

        heightIncrease = heightIncreaseTimer;
        attackTimer = attackTime;
        attackHold = attackSeparation;
        jumpsLeft = extraJumps;
        ogGravity = myRB.gravityScale;
    }

    // Update is called once per frame
    void Update()
    {
        if (!GameManager.Paused)
        {
            // Movement
            {
                if (!pushedBack && !climbing)
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
                        if (facingRight)
                        {
                            facingRight = !facingRight;
                        }
                        mySR.flipX = !facingRight;
                    }
                    else if (Input.GetKey(GameManager.Controls.MoveRight))
                    {
                        Vector2 newVel = new Vector2(walkSpeed, myRB.velocity.y);
                        myRB.velocity = newVel;

                        myAnim.SetBool("Walking", true);
                        if (!facingRight)
                        {
                            facingRight = !facingRight;
                        }
                        mySR.flipX = !facingRight;
                    }
                }
            }

            // Jumping
            {
                if (climbing && Input.GetKeyDown(GameManager.Controls.Jump))
                {
                    climbing = false;
                    climbJumping = true;
                    myRB.gravityScale = ogGravity;

                    Vector2 jumpVel = climbJumpSpeed;
                    if (facingRight)
                        jumpVel.x = -jumpVel.x;
                    myRB.velocity = jumpVel;
                }
                else
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
                        jumpVel.y = extraJumpSpeed;
                        myRB.velocity = jumpVel;
                        jumpsLeft--;
                    }
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

            // Flip Sword and Wall Check
            {
                if (Input.GetKeyDown(GameManager.Controls.MoveLeft) && sword.transform.localPosition.x > 0)
                {
                    sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
                    sword.GetComponent<SpriteRenderer>().flipX = !facingRight;
                    wallCheck.transform.localPosition = new Vector2(-wallCheck.transform.localPosition.x, wallCheck.transform.localPosition.y);
                }

                if (Input.GetKeyDown(GameManager.Controls.MoveRight) && sword.transform.localPosition.x < 0)
                {
                    sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
                    sword.GetComponent<SpriteRenderer>().flipX = !facingRight;
                    wallCheck.transform.localPosition = new Vector2(-wallCheck.transform.localPosition.x, wallCheck.transform.localPosition.y);
                }
            }

            // Swap State
            {
                if (grounded && Input.GetKeyDown(GameManager.Controls.ToOoze))
                {
                    SetState(PlayerManager.State.Ooze);
                    heightIncrease = heightIncreaseTimer;
                    attackTimer = attackTime;
                    attackHold = attackSeparation;
                    jumpsLeft = extraJumps;
                }
                else if (grounded && Input.GetKeyDown(GameManager.Controls.ToSolid))
                {
                    SetState(PlayerManager.State.Solid);
                    heightIncrease = heightIncreaseTimer;
                    attackTimer = attackTime;
                    attackHold = attackSeparation;
                    jumpsLeft = extraJumps;
                }
            }

            // Wall Climb
            {
                if (climbJumping)
                {
                    climbJumping = false;
                }
                else if (touchingWall && PlayerManager.CurrentState == PlayerManager.State.Ooze)
                {
                    climbing = true;
                    myRB.gravityScale = 0;
                    myRB.velocity = Vector2.zero;

                    Vector2 newVel = myRB.velocity;
                    if (Input.GetKeyUp(GameManager.Controls.ClimbDown) || Input.GetKeyUp(GameManager.Controls.ClimbUp) ||
                        (Input.GetKeyDown(GameManager.Controls.ClimbUp) && Input.GetKeyDown(GameManager.Controls.ClimbDown)))
                    {
                        newVel = Vector2.zero;
                    }
                    else if (Input.GetKey(GameManager.Controls.ClimbUp))
                    {
                        newVel.x = 0;
                        newVel.y = climbSpeed;
                    }
                    else if (Input.GetKey(GameManager.Controls.ClimbDown))
                    {
                        if (grounded)
                        {
                            if (facingRight)
                                newVel.x = -wallReleaseSpeed;
                            else
                                newVel.x = wallReleaseSpeed;

                            newVel.y = 0;
                            climbing = false;
                        }
                        else
                        {
                            newVel.x = 0;
                            newVel.y = -climbSpeed;
                        }
                    }
                    myRB.velocity = newVel;
                }

                if (!climbing && Input.GetKeyUp(GameManager.Controls.ClimbDown))
                {
                    // TO DO: Add timer for length of time to be pushed away from wall
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

    public void SetTouchingWall(bool touchingState)
    {
        touchingWall = touchingState;
    }

    public void PushBack(float force)
    {
        pushedBack = true;
        Vector2 pushVel = myRB.velocity;

        if (facingRight)
            pushVel.x = -force;
        else
            pushVel.x = force;

        myRB.velocity = pushVel;
    }

    void SetState(PlayerManager.State newState)
    {
        switch (newState)
        {
            case PlayerManager.State.Ooze:
                PlayerManager.SetState(PlayerManager.State.Ooze);
                currState = PlayerManager.State.Ooze;
                walkSpeed = oozeWalkSpeed;
                jumpSpeed = oozeJumpSpeed;
                heightIncreaseTimer = oozeHeightIncreaseTimer;
                extraJumps = oozeExtraJumps;
                extraJumpSpeed = oozeExtraJumpSpeed;
                attackTime = oozeAttackTime;
                attackSeparation = oozeAttackSeperation;
                sword.GetComponent<Sword>().damage = oozeDamage;
                wallCheck.SetActive(true);
                break;
            case PlayerManager.State.Solid:
                PlayerManager.SetState(PlayerManager.State.Solid);
                currState = PlayerManager.State.Solid;
                walkSpeed = solidWalkSpeed;
                jumpSpeed = solidJumpSpeed;
                heightIncreaseTimer = solidHeightIncreaseTimer;
                extraJumps = solidExtraJumps;
                extraJumpSpeed = solidExtraJumpSpeed;
                attackTime = solidAttackTime;
                attackSeparation = solidAttackSeperation;
                sword.GetComponent<Sword>().damage = solidDamage;
                touchingWall = false;
                wallCheck.SetActive(false);
                break;
        }
    }
}
