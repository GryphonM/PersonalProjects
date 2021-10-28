using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LoadLevel : MonoBehaviour
{
    [SerializeField] string levelToLoad;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Load()
    {
        SceneManager.LoadScene(levelToLoad);
    }
}
