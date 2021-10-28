using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public struct Keys
    {
        public Keys(KeyCode left, KeyCode right, KeyCode jump, KeyCode attack)
        {
            MoveLeft = left;
            MoveRight = right;
            Jump = jump;
            Attack = attack;
        }

        public KeyCode MoveLeft;
        public KeyCode MoveRight;
        public KeyCode Jump;
        public KeyCode Attack;
    }

    public static Keys Controls = new Keys(KeyCode.A, KeyCode.D, KeyCode.Space, KeyCode.Mouse1); 
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
