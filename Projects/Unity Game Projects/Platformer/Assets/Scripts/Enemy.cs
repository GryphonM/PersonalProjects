using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    [SerializeField] GameObject target;
    [Space(20)]
    [SerializeField] Vector2[] patrolPoints;
    [Tooltip("How close the enemy can get to the patrol point before it moves on to the next one")]
    [SerializeField] float patrolCloseEnough = 0.1f;
    [Tooltip("Whether the enemy should go up then down the patrol points or reset to the starting patrol point when it reaches the last one")]
    [SerializeField] bool resetToStart;
    [SerializeField] float patrolSpeed = 5f;
    [SerializeField] bool canFly = false;
    [Space(20)]
    [SerializeField] float lungeSpeed = 15f;
    [SerializeField] float lungeDistance = 3f;
    [SerializeField] float lungeWait = 2f;
    [SerializeField] Vector2 lungeKnockBack;

    bool facingRight = true;
    SpriteRenderer mySR;
    bool countingUp = true;
    int nextPatrolPoint = 0;
    int maxPatrolPoints;
    Rigidbody2D myRB;

    bool waitingToLunge = false;
    bool lunging = false;
    float lungeWaitTimer;
    
    // Start is called before the first frame update
    void Start()
    {
        maxPatrolPoints = patrolPoints.Length - 1;
        mySR = GetComponent<SpriteRenderer>();
        myRB = GetComponent<Rigidbody2D>();
        lungeWaitTimer = lungeWait;
    }

    // Update is called once per frame
    void Update()
    {
        Vector2 targetDir = new Vector2(transform.position.x - target.transform.position.x, 
            transform.position.y - target.transform.position.y);
        
        if (targetDir.magnitude > lungeDistance && !waitingToLunge && !lunging)
        {
            if ((transform.position.x <= patrolPoints[nextPatrolPoint].x + patrolCloseEnough && 
                transform.position.x >= patrolPoints[nextPatrolPoint].x - patrolCloseEnough) &&
                (!canFly || 
                (transform.position.y <= patrolPoints[nextPatrolPoint].y + patrolCloseEnough &&
                transform.position.y >= patrolPoints[nextPatrolPoint].y - patrolCloseEnough)))
            {
                if (nextPatrolPoint == maxPatrolPoints || (!resetToStart && nextPatrolPoint == 0))
                {
                    if (resetToStart)
                        nextPatrolPoint = 0;
                    else
                        countingUp = !countingUp;
                }
                else
                {
                    if (countingUp)
                        nextPatrolPoint++;
                    else
                        nextPatrolPoint--;
                }

                if (patrolPoints[nextPatrolPoint].x < transform.position.x && facingRight)
                {
                    mySR.flipX = facingRight = false;
                }
                else if (patrolPoints[nextPatrolPoint].x > transform.position.x && !facingRight)
                {
                    mySR.flipX = facingRight = true;
                }
            }
            else
            {
                Vector2 newVel = new Vector2(transform.position.x - patrolPoints[nextPatrolPoint].x,
                    transform.position.y - patrolPoints[nextPatrolPoint].y);

                newVel.Normalize();

                if (canFly)
                {
                    newVel *= patrolSpeed;
                }
                else
                {
                    newVel.x *= patrolSpeed;
                    newVel.y = 0;
                }

                myRB.velocity = newVel;
            }
        }
        else
        {
            if (!waitingToLunge && !lunging)
            {
                waitingToLunge = true;
                myRB.velocity = Vector2.zero;
                myRB.bodyType = RigidbodyType2D.Kinematic;
            }
            
            if (waitingToLunge && !lunging)
            {
                if (lungeWaitTimer <= 0)
                {
                    waitingToLunge = false;
                    lunging = true;
                    lungeWaitTimer = lungeWait;

                    Vector2 newVel = targetDir.normalized;
                    if (canFly)
                    {
                        newVel *= lungeSpeed;
                    }
                    else
                    {
                        newVel.x *= lungeSpeed;
                        newVel.y = 0;
                    }
                }
                else
                    lungeWaitTimer -= Time.deltaTime;
            }

            if (lunging)
            {
                // TO DO: Decrease lunge velocity
            }
        }
    }

    // TO DO: End Lunge Behaviour
}
