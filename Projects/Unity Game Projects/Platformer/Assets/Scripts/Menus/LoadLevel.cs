using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LoadLevel : MonoBehaviour
{
    [SerializeField] string levelToLoad;

    public void Load()
    {
        SceneManager.LoadScene(levelToLoad);
    }
}
