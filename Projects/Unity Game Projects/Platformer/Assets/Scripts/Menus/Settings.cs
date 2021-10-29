using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Settings : MonoBehaviour
{
    [SerializeField] GameObject settingsMenu;
    [SerializeField] GameObject mainMenu;

    public void ActivateMenu(GameObject menu)
    {
        if (menu == settingsMenu)
        {
            settingsMenu.SetActive(true);
            mainMenu.SetActive(false);
        }
        else if (menu == mainMenu)
        {
            mainMenu.SetActive(true);
            settingsMenu.SetActive(false);
        }
    }
}
