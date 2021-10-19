using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class LevelController : MonoBehaviour
{
    int score = 0;
    [SerializeField] int lives = 3;
    [SerializeField] Text scoreText;
    [SerializeField] Text livesText;
    [SerializeField] Text powerupText;
    [SerializeField] GameObject ballPrefab;
    Color defaultTextColor = Color.white;
    
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

    public void RespawnPlayer()
    {
        Vector3 respawnPos = new Vector3(0, -2, 0);
        Instantiate(ballPrefab, respawnPos, Quaternion.identity);
    }

    public void IncreaseScore()
    {
        score++;
        scoreText.text = score.ToString();
    }

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
