using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class ChangeControl : MonoBehaviour
{
    enum ControlType { moveLeft, moveRight, jump, attack};
    [SerializeField] ControlType type;
    [SerializeField] string waitingString = "Please Press A Key";
    bool checkForKey = false;
    KeyCode[] keys;

    TMP_Text buttonText;
    Button button;
    
    // Start is called before the first frame update
    void Start()
    {
        buttonText = transform.GetComponentInChildren<TMP_Text>();
        button = GetComponent<Button>();
        keys = (KeyCode[]) System.Enum.GetValues(typeof(KeyCode));
    }

    // Update is called once per frame
    void Update()
    {
        if (!checkForKey && !button.interactable && Input.GetKeyUp(KeyCode.Mouse0))
            button.interactable = true;

        if (checkForKey && Input.anyKey)
        {
            foreach(KeyCode key in keys)
            {
                if (Input.GetKeyDown(key))
                {
                    SetKey(key);
                    if (key == KeyCode.Mouse0)
                        buttonText.text = "Left Mouse Button";
                    else if (key == KeyCode.Mouse1)
                        buttonText.text = "Right Mouse Button";
                    else
                        buttonText.text = key.ToString();

                    checkForKey = false;
                }
            }
        }
    }

    public void ChangeControls()
    {
        checkForKey = true;
        buttonText.text = waitingString;
        button.interactable = false;
    }

    void SetKey(KeyCode key)
    {
        switch (type)
        {
            case ControlType.moveLeft:
                GameManager.Controls.MoveLeft = key;
                break;
            case ControlType.moveRight:
                GameManager.Controls.MoveRight = key;
                break;
            case ControlType.jump:
                GameManager.Controls.Jump = key;
                break;
            case ControlType.attack:
                GameManager.Controls.Attack = key;
                break;
        }
    }
}
