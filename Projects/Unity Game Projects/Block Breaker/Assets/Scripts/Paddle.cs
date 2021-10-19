using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Paddle : MonoBehaviour
{
    public float speed;
    public float leftLimit = -5.5f;
    public float rightLimit = 5.5f;

    LevelController lc;
    
    // Start is called before the first frame update
    void Start()
    {
        transform.position = new Vector2(0f, -4.5f);
        lc = FindObjectOfType<LevelController>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey("left") && transform.position.x >= leftLimit)
            GetComponent<Rigidbody2D>().velocity = new Vector2(-speed, 0f);
        else if (Input.GetKey("right") && transform.position.x <= rightLimit)
            GetComponent<Rigidbody2D>().velocity = new Vector2(speed, 0f);
        else
            GetComponent<Rigidbody2D>().velocity = new Vector2(0f, 0f);
    }

    public void SpeedPowerup(float length, float originalSpeed)
    {
        StartCoroutine(Speed(length, originalSpeed));
    }

    public void SizePowerup(float length, float originalSize, float originalLowerLimit, float originalUpperLimit)
    {
        StartCoroutine(Size(length, originalSize, originalLowerLimit, originalUpperLimit));
    }
    
    IEnumerator Speed(float length, float originalSpeed)
    {
        yield return new WaitForSeconds(length);
        speed = originalSpeed;
        lc.updatePowerupText(Color.white);
    }

    IEnumerator Size(float length, float originalSize, float originalLowerLimit, float originalUpperLimit)
    {
        yield return new WaitForSeconds(length);
        transform.localScale = new Vector3(originalSize, transform.localScale.y, transform.localScale.z);
        leftLimit = originalLowerLimit;
        rightLimit = originalUpperLimit;
        lc.updatePowerupText(Color.white);
    }
}
