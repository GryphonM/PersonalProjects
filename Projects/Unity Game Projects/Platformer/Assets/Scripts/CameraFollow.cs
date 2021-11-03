using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    [SerializeField] GameObject objectToFollow;

    // Update is called once per frame
    void Update()
    {
        Vector3 newPos = objectToFollow.transform.position;
        newPos.z = transform.position.z;
        transform.position = newPos;
    }
}
