using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour
{
    public enum State { Structure, Blob};
    
    private static State currentState = State.Structure;

    public static State CurrentState
    {
        get { return currentState; }
    }

    public static void ChangeState(State newState)
    {
        currentState = newState;
    }

    public static void GameOver(GameObject player)
    {
        Destroy(player);
    }
}
