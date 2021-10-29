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
    Button[] settingsButtons;
    
    // Start is called before the first frame update
    void Start()
    {
        buttonText = transform.GetComponentInChildren<TMP_Text>();
        button = GetComponent<Button>();
        keys = (KeyCode[]) System.Enum.GetValues(typeof(KeyCode));

        settingsButtons = transform.parent.parent.parent.GetComponentsInChildren<Button>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!checkForKey && !button.interactable && Input.GetKeyUp(KeyCode.Mouse0))
        {
            button.interactable = true;

            foreach (Button otherButton in settingsButtons)
                otherButton.interactable = true;
        }

        if (checkForKey && Input.anyKey)
        {
            foreach(KeyCode key in keys)
            {
                if (Input.GetKeyDown(key))
                {
                    SetKey(key);

                    buttonText.text = ConvertToString(key);

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

        foreach (Button otherButton in settingsButtons)
            otherButton.interactable = false;
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

    string ConvertToString(KeyCode key)
    {
        switch (key)
        {
            case KeyCode.Keypad0:
            case KeyCode.Alpha0:
                return "0";
            case KeyCode.Keypad1:
            case KeyCode.Alpha1:
                return "1";
            case KeyCode.Keypad2:
            case KeyCode.Alpha2:
                return "2";
            case KeyCode.Keypad3:
            case KeyCode.Alpha3:
                return "3";
            case KeyCode.Keypad4:
            case KeyCode.Alpha4:
                return "4";
            case KeyCode.Keypad5:
            case KeyCode.Alpha5:
                return "5";
            case KeyCode.Keypad6:
            case KeyCode.Alpha6:
                return "6";
            case KeyCode.Keypad7:
            case KeyCode.Alpha7:
                return "7";
            case KeyCode.Keypad8:
            case KeyCode.Alpha8:
                return "8";
            case KeyCode.Keypad9:
            case KeyCode.Alpha9:
                return "9";
            case KeyCode.KeypadPeriod:
            case KeyCode.Period:
                return ".";
            case KeyCode.KeypadDivide:
            case KeyCode.Slash:
                return "/";
            case KeyCode.KeypadMultiply:
            case KeyCode.Asterisk:
                return "*";
            case KeyCode.KeypadMinus:
            case KeyCode.Minus:
                return "-";
            case KeyCode.KeypadPlus:
            case KeyCode.Plus:
                return "+";
            case KeyCode.KeypadEnter:
                return "Return";
            case KeyCode.KeypadEquals:
            case KeyCode.Equals:
                return "=";
            case KeyCode.UpArrow:
                return "Up Arrow";
            case KeyCode.DownArrow:
                return "Down Arrow";
            case KeyCode.RightArrow:
                return "Right Arrow";
            case KeyCode.LeftArrow:
                return "Left Arrow";
            case KeyCode.PageUp:
                return "Page Up";
            case KeyCode.PageDown:
                return "Page Down";
            case KeyCode.Exclaim:
                return "!";
            case KeyCode.DoubleQuote:
                return "\"";
            case KeyCode.Hash:
                return "#";
            case KeyCode.Dollar:
                return "$";
            case KeyCode.Percent:
                return "%";
            case KeyCode.Ampersand:
                return "&";
            case KeyCode.Quote:
                return "'";
            case KeyCode.LeftParen:
                return "(";
            case KeyCode.RightParen:
                return ")";
            case KeyCode.Comma:
                return ",";
            case KeyCode.Colon:
                return ":";
            case KeyCode.Semicolon:
                return ";";
            case KeyCode.Less:
                return "<";
            case KeyCode.Greater:
                return ">";
            case KeyCode.Question:
                return "?";
            case KeyCode.At:
                return "@";
            case KeyCode.LeftBracket:
                return "[";
            case KeyCode.Backslash:
                return "\\";
            case KeyCode.RightBracket:
                return "]";
            case KeyCode.Caret:
                return "^";
            case KeyCode.Underscore:
                return "_";
            case KeyCode.BackQuote:
                return "`";
            case KeyCode.LeftCurlyBracket:
                return "{";
            case KeyCode.Pipe:
                return "|";
            case KeyCode.RightCurlyBracket:
                return "}";
            case KeyCode.Tilde:
                return "~";
            case KeyCode.RightShift:
                return "Right Shift";
            case KeyCode.LeftShift:
                return "Left Shift";
            case KeyCode.RightControl:
                return "Right Control";
            case KeyCode.LeftControl:
                return "Left Control";
            case KeyCode.RightAlt:
                return "Right Alt";
            case KeyCode.LeftAlt:
                return "Left Alt";
            case KeyCode.LeftCommand:
                return "Left Command";
            case KeyCode.RightCommand:
                return "Right Command";
            case KeyCode.Mouse0:
                return "Left Mouse Button";
            case KeyCode.Mouse1:
                return "Right Mouse button";
            case KeyCode.Mouse2:
                return "Middle Mouse Button";
            default:
                return key.ToString();
        }
    }
}
