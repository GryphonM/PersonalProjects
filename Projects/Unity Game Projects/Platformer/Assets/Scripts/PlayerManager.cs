using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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
        Destroy(player);
    }
}
