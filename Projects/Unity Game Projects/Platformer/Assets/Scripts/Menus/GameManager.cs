using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public struct Keys
    {
        public Keys(KeyCode left, 
            KeyCode right, 
            KeyCode jump, 
            KeyCode attack, 
            KeyCode pause, 
            KeyCode toOoze, 
            KeyCode toSolid, 
            KeyCode climbUp, 
            KeyCode climbDown)
        {
            MoveLeft = left;
            MoveRight = right;
            Jump = jump;
            Attack = attack;
            Pause = pause;
            ToOoze = toOoze;
            ToSolid = toSolid;
            ClimbUp = climbUp;
            ClimbDown = climbDown;
        }

        public KeyCode MoveLeft;
        public KeyCode MoveRight;
        public KeyCode Jump;
        public KeyCode Attack;
        public KeyCode Pause;
        public KeyCode ToOoze;
        public KeyCode ToSolid;
        public KeyCode ClimbUp;
        public KeyCode ClimbDown;
    }

    public static Keys Controls = new Keys(KeyCode.A, 
                                            KeyCode.D, 
                                            KeyCode.Space, 
                                            KeyCode.Mouse1, 
                                            KeyCode.Escape, 
                                            KeyCode.Q, 
                                            KeyCode.E, 
                                            KeyCode.W, 
                                            KeyCode.S);

    public static bool Paused = false;
}
