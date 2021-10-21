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
    [SerializeField] float attakTime;

    Rigidbody2D myRB;
    
    // Start is called before the first frame update
    void Start()
    {
        myRB = GetComponent<Rigidbody2D>();
        heightIncrease = heightIncreaseTimer;
    }

    // Update is called once per frame
    void Update()
    {
        // Movement
        if (Input.GetKey(moveLeft))
        {
            Vector3 newPos = new Vector2(walkSpeed * Time.deltaTime, 0);
            transform.position -= newPos;
        }
        
        if (Input.GetKey(moveRight))
        {
            Vector3 newPos = new Vector2(walkSpeed * Time.deltaTime, 0);
            transform.position += newPos;
        }

        // Jumping
        if (Input.GetKey(jump))
        {
            if (grounded)
            {
                Vector2 jumpVel = new Vector2(0, jumpSpeed);
                myRB.velocity = jumpVel;
            }
            else if (heightIncrease > 0)
            {
                Vector2 jumpVel = new Vector2(0, jumpSpeed);
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
        if (Input.GetKeyDown(attack))
        {
            sword.SetActive(true);
        }

        if (Input.GetKeyUp(attack))
        {
            sword.SetActive(false);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Ground"))
        {
            grounded = true;
            heightIncrease = heightIncreaseTimer;
        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Ground"))
            grounded = false;
    }
}
