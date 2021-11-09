using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerManager : MonoBehaviour
{
    public enum State { Solid, Ooze};
    
    static State currentState = State.Solid;

    public static State CurrentState
    {
        get { return currentState; }
    }

    public static void SetState(State newState)
    {
        currentState = newState;
    }

    public static void GameOver(GameObject player)
    {
        SceneManager.LoadScene("Game Over");
    }
}
