//------------------------------------------------------------------------------
//
// File Name:	LevelLoader.cs
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
using UnityEngine.SceneManagement;

public class LevelLoader : MonoBehaviour
{
    int brickCount;
    
    // Start is called before the first frame update
    void Start()
    {
        CountAllBricks();
    }

    // Updates class level variable to determine how many bricks there are
    private void CountAllBricks()
    {
        Bricks[] allBricksInLevel = FindObjectsOfType<Bricks>();
        brickCount = allBricksInLevel.Length;
    }

    // Removes a brick from the count, letting us know when we've broken all of them
    public void DeductBrick()
    {
        brickCount--;

        if (brickCount <= 0)
            LoadNextLevel();
    }

    // Loads the next level in the build index
    private void LoadNextLevel()
    {
        int sceneIndex = SceneManager.GetActiveScene().buildIndex;
        SceneManager.LoadScene(sceneIndex + 1);
    }
}
