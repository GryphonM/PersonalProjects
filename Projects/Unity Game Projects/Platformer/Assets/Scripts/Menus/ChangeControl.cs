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

                    switch (key)
                    {
                        case KeyCode.Keypad0:
                        case KeyCode.Alpha0:
                            buttonText.text = "0";
                            break;
                        case KeyCode.Keypad1:
                        case KeyCode.Alpha1:
                            buttonText.text = "1";
                            break;
                        case KeyCode.Keypad2:
                        case KeyCode.Alpha2:
                            buttonText.text = "2";
                            break;
                        case KeyCode.Keypad3:
                        case KeyCode.Alpha3:
                            buttonText.text = "3";
                            break;
                        case KeyCode.Keypad4:
                        case KeyCode.Alpha4:
                            buttonText.text = "4";
                            break;
                        case KeyCode.Keypad5:
                        case KeyCode.Alpha5:
                            buttonText.text = "5";
                            break;
                        case KeyCode.Keypad6:
                        case KeyCode.Alpha6:
                            buttonText.text = "6";
                            break;
                        case KeyCode.Keypad7:
                        case KeyCode.Alpha7:
                            buttonText.text = "7";
                            break;
                        case KeyCode.Keypad8:
                        case KeyCode.Alpha8:
                            buttonText.text = "8";
                            break;
                        case KeyCode.Keypad9:
                        case KeyCode.Alpha9:
                            buttonText.text = "9";
                            break;
                        case KeyCode.KeypadPeriod:
                            buttonText.text = ".";
                            break;
                        case KeyCode.KeypadDivide:
                            buttonText.text = "/";
                            break;
                        case KeyCode.KeypadMultiply:
                        case KeyCode.Asterisk:
                            buttonText.text = "*";
                            break;
                        case KeyCode.KeypadMinus:
                        case KeyCode.Minus:
                            buttonText.text = "-";
                            break;
                        case KeyCode.KeypadPlus:
                        case KeyCode.Plus:
                            buttonText.text = "+";
                            break;
                        case KeyCode.KeypadEnter:
                            buttonText.text = "Return";
                            break;
                        case KeyCode.KeypadEquals:
                            buttonText.text = "=";
                            break;
                        case KeyCode.UpArrow:
                            buttonText.text = "Up Arrow";
                            break;
                        case KeyCode.DownArrow:
                            buttonText.text = "Down Arrow";
                            break;
                        case KeyCode.RightArrow:
                            buttonText.text = "Right Arrow";
                            break;
                        case KeyCode.LeftArrow:
                            buttonText.text = "Left Arrow";
                            break;
                        case KeyCode.PageUp:
                            buttonText.text = "Page Up";
                            break;
                        case KeyCode.PageDown:
                            buttonText.text = "Page Down";
                            break;
                        case KeyCode.Exclaim:
                            buttonText.text = "!";
                            break;
                        case KeyCode.DoubleQuote:
                            buttonText.text = "\"";
                            break;
                        case KeyCode.Hash:
                            buttonText.text = "#";
                            break;
                        case KeyCode.Dollar:
                            buttonText.text = "$";
                            break;
                        case KeyCode.Percent:
                            buttonText.text = "%";
                            break;
                        case KeyCode.Ampersand:
                            buttonText.text = "&";
                            break;
                        case KeyCode.Quote:
                            buttonText.text = "'";
                            break;
                        case KeyCode.LeftParen:
                            buttonText.text = "(";
                            break;
                        case KeyCode.RightParen:
                            buttonText.text = ")";
                            break;
                        case KeyCode.Comma:
                            buttonText.text = ",";
                            break;
                    }
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
