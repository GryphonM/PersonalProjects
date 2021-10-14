using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PaddleController : MonoBehaviour
{
    [SerializeField] KeyCode paddleMoveKey;
    [SerializeField] Vector3 initialRotation;
    [SerializeField] Vector3 finalRotation;
    [SerializeField] float speed;
    private enum rotateMethods { rotateTowards, sLerp};
    [SerializeField] rotateMethods rotateMethod = rotateMethods.sLerp;

    private bool movePaddle = false;

    // Start is called before the first frame update
    void Start()
    {
        transform.SetPositionAndRotation(transform.position, Quaternion.Euler(initialRotation));
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(paddleMoveKey))
        {
            if (rotateMethod == rotateMethods.rotateTowards)
            {
                transform.rotation = Quaternion.RotateTowards(transform.rotation, Quaternion.Euler(finalRotation), speed * Time.deltaTime);
            }
            else if (rotateMethod == rotateMethods.sLerp)
            {
                transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.Euler(finalRotation), speed * Time.deltaTime);
            }
        }
        else
        {
            if (rotateMethod == rotateMethods.rotateTowards)
            {
                transform.rotation = Quaternion.RotateTowards(transform.rotation, Quaternion.Euler(initialRotation), speed * Time.deltaTime);
            }
            else if (rotateMethod == rotateMethods.sLerp)
            {
                transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.Euler(initialRotation), speed * Time.deltaTime);
            }
        }
    }
}
