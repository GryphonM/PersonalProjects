using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShowSettings : MonoBehaviour
{
    [SerializeField] KeyCode settingsKey = KeyCode.Escape;
    [SerializeField] bool freezeOnPause = true;

    GameObject settingsMenu;
    float defaultTimeScale;
    
    // Start is called before the first frame update
    void Start()
    {
        settingsMenu = transform.GetChild(0).gameObject;
        settingsMenu.SetActive(false);
        defaultTimeScale = Time.timeScale;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(settingsKey) && !settingsMenu.activeSelf)
        {
            settingsMenu.SetActive(true);
            GameManager.Paused = true;

            if (freezeOnPause)
                Time.timeScale = 0;
        }
    }

    public void closeSettings()
    {
        settingsMenu.SetActive(false);
        GameManager.Paused = false;

        if (freezeOnPause)
            Time.timeScale = defaultTimeScale;
    }
}
