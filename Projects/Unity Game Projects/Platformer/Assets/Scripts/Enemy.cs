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
    [Tooltip("Tags the enemy can attack\n" +
        "These game objects must have PlayerHealth.cs or Health.cs attached\n" +
        "Script will prioritize Health.cs if collision has both scripts")]
    [SerializeField] string[] Tags;
    [SerializeField] float lungeSpeed = 15f;
    [SerializeField] float lungeDistance = 3f;
    [SerializeField] float lungePause = 2f;
    [SerializeField] int damage = 1;
    [Tooltip("The speed the enemy stops lunging at")]
    [SerializeField] float lungeEndSpeed = .5f;
    [SerializeField] Vector2 lungeKnockBack;
    [SerializeField] float knockBackTime = 0.5f;
    [SerializeField] float timeBetweenLunges;

    bool facingRight = true;
    SpriteRenderer mySR;
    bool countingUp = true;
    int nextPatrolPoint = 0;
    int maxPatrolPoints;
    Rigidbody2D myRB;

    public bool waitingToLunge = false;
    public bool lunging = false;
    public bool canLunge = true;
    public bool knockBack = false;
    public float lungePauseTimer;
    public float lungeWaitTimer;
    public float knockBackTimer;
    
    // Start is called before the first frame update
    void Start()
    {
        maxPatrolPoints = patrolPoints.Length - 1;
        mySR = GetComponent<SpriteRenderer>();
        myRB = GetComponent<Rigidbody2D>();
        lungePauseTimer = lungePause;
        lungeWaitTimer = timeBetweenLunges;
        knockBackTimer = knockBackTime;
    }

    // Update is called once per frame
    void Update()
    {
        Vector2 targetDir = new Vector2(target.transform.position.x - transform.position.x, 
            target.transform.position.y - transform.position.y);

        bool targetClose = targetDir.magnitude < lungeDistance &&
            ((facingRight && target.transform.position.x > transform.position.x) || 
            (!facingRight && target.transform.position.x < transform.position.x));
        
        if (!targetClose && !waitingToLunge && !lunging && !knockBack)
        {
            if ((transform.position.x <= patrolPoints[nextPatrolPoint].x + patrolCloseEnough && 
                transform.position.x >= patrolPoints[nextPatrolPoint].x - patrolCloseEnough) &&
                (!canFly || 
                (transform.position.y <= patrolPoints[nextPatrolPoint].y + patrolCloseEnough &&
                transform.position.y >= patrolPoints[nextPatrolPoint].y - patrolCloseEnough)))
            {
                if (nextPatrolPoint == maxPatrolPoints || (!resetToStart && nextPatrolPoint == 0 && !countingUp))
                {
                    if (resetToStart)
                        nextPatrolPoint = 0;
                    else
                    {
                        countingUp = !countingUp;
                        if (countingUp)
                        nextPatrolPoint++;
                    else
                        nextPatrolPoint--;
                    }
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
                Vector2 newVel = new Vector2(patrolPoints[nextPatrolPoint].x - transform.position.x,
                    patrolPoints[nextPatrolPoint].y - transform.position.y);

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
            if (!waitingToLunge && !lunging && canLunge)
            {
                waitingToLunge = true;
                myRB.velocity = Vector2.zero;
                //myRB.bodyType = RigidbodyType2D.Kinematic;
            }
            
            if (waitingToLunge && !lunging && canLunge)
            {
                if (lungePauseTimer <= 0)
                {
                    waitingToLunge = false;
                    lunging = true;
                    lungePauseTimer = lungePause;

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
                    myRB.velocity = newVel;
                }
                else
                    lungePauseTimer -= Time.deltaTime;
            }

            if (lunging && canLunge)
            {
                if ((myRB.velocity.x > 0 && myRB.velocity.x > lungeEndSpeed) || 
                    (myRB.velocity.x < 0 && myRB.velocity.x < lungeEndSpeed) || 
                    (canFly && myRB.velocity.y > lungeEndSpeed))
                {
                    if (canFly)
                    {
                        Vector2 newVel = myRB.velocity.normalized;
                        newVel *= myRB.velocity.magnitude - Time.deltaTime;
                        myRB.velocity = newVel;
                    }
                    else
                    {
                        Vector2 newVel = myRB.velocity;
                        newVel.x -= Time.deltaTime;
                        myRB.velocity = newVel;
                    }
                }
                else
                {
                    canLunge = false;
                    lunging = false;
                    myRB.velocity = Vector2.zero;
                }
            }

            if (!canLunge && !knockBack)
            {
                if (lungeWaitTimer <= 0)
                {
                    canLunge = true;
                    lungeWaitTimer = timeBetweenLunges;
                }
                else
                    lungeWaitTimer -= Time.deltaTime;
            }

            if (knockBack)
            {
                if (knockBackTimer <= 0)
                {
                    knockBack = false;
                    knockBackTimer = knockBackTime;
                }
                else
                    knockBackTimer -= Time.deltaTime;
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        foreach(string tag in Tags)
        {
            if (collision.gameObject.CompareTag(tag))
            {
                Health colHealth = collision.gameObject.GetComponent<Health>();
                PlayerHealth colPlayHealth = collision.gameObject.GetComponent<PlayerHealth>();

                if (colHealth != null)
                    colHealth.DamageObject(damage);
                else if (colPlayHealth != null)
                    colPlayHealth.DamagePlayer(damage);

                if (lunging && !waitingToLunge)
                {
                    if (facingRight)
                        myRB.velocity = -lungeKnockBack;
                    else
                        myRB.velocity = lungeKnockBack;

                    lunging = false;
                    canLunge = false;
                    knockBack = true;
                }
            }
        }
    }
}
