//------------------------------------------------------------------------------
//
// File Name:	LevelController.cs
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	GAM 5.1.2 Assignment - Cage and Breaker Challenges
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class LevelController : MonoBehaviour
{
    // Score Variables
    int score = 0;
    [SerializeField] Text scoreText;

    // Lives Variables
    [SerializeField] int lives = 3;
    [SerializeField] Text livesText;

    // Powerup Variables
    [SerializeField] Text powerupText;
    Color defaultTextColor = Color.white;

    [SerializeField] GameObject ballPrefab;
    
    // Start is called before the first frame update
    void Start()
    {
        livesText.text = lives.ToString();
        scoreText.text = score.ToString();
    }

    private void Awake()
    {
        LevelController[] objs = FindObjectsOfType<LevelController>();

        if (objs.Length > 1)
            Destroy(gameObject);

        DontDestroyOnLoad(gameObject);
    }

    // Manages the player losing a life (i.e. they drop the ball)
    public void DecreaseLives()
    {
        lives--;
        livesText.text = lives.ToString();

        if (lives > 0)
        {
            RespawnPlayer();
        }
        else
        {
            SceneManager.LoadScene("End Screen");
        }
    }

    // Replaces the player at the starting position
    public void RespawnPlayer()
    {
        Vector3 respawnPos = new Vector3(0, -2, 0);
        Instantiate(ballPrefab, respawnPos, Quaternion.identity);
    }

    // Increases the score variable and updates the text
    public void IncreaseScore()
    {
        score++;
        scoreText.text = score.ToString();
    }

    // Changes teh powerup text to display the current powerup
    // as well as a color cooresponding to the powerup
    public void updatePowerupText(Color color, int state = -1)
    {
        switch(state)
        {
            case 0:
                powerupText.text = "Speed";
                break;
            case 1:
                powerupText.text = "Size";
                break;
            case 2:
                powerupText.text = "Damage";
                break;
            default:
                powerupText.text = "None";
                break;
        }

        powerupText.color = color;
    }
}
