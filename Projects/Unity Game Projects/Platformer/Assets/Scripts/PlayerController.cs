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

    [Space(20)]

    [SerializeField] GameObject oozeWallCheck;
    [SerializeField] GameObject solidWallCheck;
    [Space(5)]
    [SerializeField] float climbSpeed;
    [SerializeField] Vector2 climbJumpSpeed;
    [Space(5)]
    [Tooltip("If You climb to bottom of wall, how much you are pushed away from the wall")]
    [SerializeField] float wallReleaseSpeed = 0.3f;
    [Tooltip("How long you are pushed away from the wall if you climb to the bottom")]
    [SerializeField] float wallReleaseLength = 0.2f;
    [Tooltip("How high are you pushed when you climb to the top")]
    [SerializeField] float wallPopUpForce = 2.5f;
    float wallReleaseTimer;
    bool wallRelease;
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
        wallReleaseTimer = wallReleaseLength;
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
                if (!pushedBack && !climbing && !wallRelease && (!touchingWall || grounded))
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
                if (!wallRelease)
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
            }

            // Attacking
            {
                if (!wallRelease)
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
            }

            // Flip Sword and Wall Checks
            {
                if (Input.GetKeyDown(GameManager.Controls.MoveLeft) && sword.transform.localPosition.x > 0)
                {
                    sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
                    sword.GetComponent<SpriteRenderer>().flipX = !facingRight;
                    oozeWallCheck.transform.localPosition = new Vector2(-oozeWallCheck.transform.localPosition.x, oozeWallCheck.transform.localPosition.y);
                    solidWallCheck.transform.localPosition = oozeWallCheck.transform.localPosition;
                }

                if (Input.GetKeyDown(GameManager.Controls.MoveRight) && sword.transform.localPosition.x < 0)
                {
                    sword.transform.localPosition = new Vector2(-sword.transform.localPosition.x, sword.transform.localPosition.y);
                    sword.GetComponent<SpriteRenderer>().flipX = !facingRight;
                    oozeWallCheck.transform.localPosition = new Vector2(-oozeWallCheck.transform.localPosition.x, oozeWallCheck.transform.localPosition.y);
                    solidWallCheck.transform.localPosition = oozeWallCheck.transform.localPosition;
                }
            }

            // Swap State
            {
                if (!wallRelease && grounded)
                {
                    if (Input.GetKeyDown(GameManager.Controls.ToOoze))
                    {
                        SetState(PlayerManager.State.Ooze);
                        heightIncrease = heightIncreaseTimer;
                        attackTimer = attackTime;
                        attackHold = attackSeparation;
                        jumpsLeft = extraJumps;
                    }
                    else if (Input.GetKeyDown(GameManager.Controls.ToSolid))
                    {
                        SetState(PlayerManager.State.Solid);
                        heightIncrease = heightIncreaseTimer;
                        attackTimer = attackTime;
                        attackHold = attackSeparation;
                        jumpsLeft = extraJumps;
                    }
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
                            wallRelease = true;
                            myRB.gravityScale = ogGravity;
                        }
                        else
                        {
                            newVel.x = 0;
                            newVel.y = -climbSpeed;
                        }
                    }
                    myRB.velocity = newVel;
                }
                else if (!touchingWall && climbing && PlayerManager.CurrentState == PlayerManager.State.Ooze)
                {
                    climbing = false;
                    myRB.velocity = new Vector2(0, wallPopUpForce);
                    myRB.gravityScale = ogGravity;
                }

                if (wallRelease)
                {
                    if (wallReleaseTimer <= 0 || myRB.velocity.x <= 0)
                    {
                        myRB.velocity = Vector2.zero;
                        wallReleaseTimer = wallReleaseLength;
                        wallRelease = false;
                    }
                    else
                    {
                        wallReleaseTimer -= Time.deltaTime;
                        myRB.velocity = new Vector2(Mathf.Lerp(myRB.velocity.x, 0, Time.deltaTime * wallReleaseSpeed), myRB.velocity.y);
                    }
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
                walkSpeed = oozeWalkSpeed;
                jumpSpeed = oozeJumpSpeed;
                heightIncreaseTimer = oozeHeightIncreaseTimer;
                extraJumps = oozeExtraJumps;
                extraJumpSpeed = oozeExtraJumpSpeed;
                attackTime = oozeAttackTime;
                attackSeparation = oozeAttackSeperation;
                sword.GetComponent<Sword>().damage = oozeDamage;
                oozeWallCheck.SetActive(true);
                solidWallCheck.SetActive(false);
                myAnim.SetBool("IsSolid", false);
                break;
            case PlayerManager.State.Solid:
                PlayerManager.SetState(PlayerManager.State.Solid);
                walkSpeed = solidWalkSpeed;
                jumpSpeed = solidJumpSpeed;
                heightIncreaseTimer = solidHeightIncreaseTimer;
                extraJumps = solidExtraJumps;
                extraJumpSpeed = solidExtraJumpSpeed;
                attackTime = solidAttackTime;
                attackSeparation = solidAttackSeperation;
                sword.GetComponent<Sword>().damage = solidDamage;
                touchingWall = false;
                oozeWallCheck.SetActive(false);
                solidWallCheck.SetActive(true);
                myAnim.SetBool("IsSolid", true);
                break;
        }
    }
}
