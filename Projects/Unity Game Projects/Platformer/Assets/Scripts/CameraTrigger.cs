using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraTrigger : MonoBehaviour
{
    [SerializeField] Vector2 newCameraLocation;
    [SerializeField] bool changeSize;
    [SerializeField] float newSize;
    [SerializeField] GameObject cameraObject;
    [SerializeField] Camera camera;

    Vector3 newCamLoc;

    private void Start()
    {
        newCamLoc = newCameraLocation;
        newCamLoc.z = cameraObject.transform.position.z;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        cameraObject.transform.position = newCamLoc;

        if (changeSize)
            camera.orthographicSize = newSize;
    }
}
