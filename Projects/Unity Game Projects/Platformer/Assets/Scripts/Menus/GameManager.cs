using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public struct Keys
    {
        public Keys(KeyCode left, KeyCode right, KeyCode jump, KeyCode attack, KeyCode pause)
        {
            MoveLeft = left;
            MoveRight = right;
            Jump = jump;
            Attack = attack;
            Pause = pause;
        }

        public KeyCode MoveLeft;
        public KeyCode MoveRight;
        public KeyCode Jump;
        public KeyCode Attack;
        public KeyCode Pause;
    }

    public static Keys Controls = new Keys(KeyCode.A, KeyCode.D, KeyCode.Space, KeyCode.Mouse1, KeyCode.Escape);

    public static bool Paused = false;
}
