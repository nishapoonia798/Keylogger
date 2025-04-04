                                                🖥️ Keylogger in C++

📌 Description
A lightweight C++ keylogger that captures keystrokes on a Windows machine and logs them to a file. The program uses GetAsyncKeyState() and handles both regular and special keys, including shift-modified characters.

⚙️ Features - Captures all keyboard inputs.

    2. Handles:

        A.  Letters (uppercase/lowercase)

        B.  Numbers and symbols with SHIFT

        C.  Special characters (~, :, *, etc.)

        D.  Special keys like [ENTER], [TAB], etc.

    3. Logs output to keylog.txt

    4. Stops logging when [ESC] is pressed

🧾 Requirements - Windows OS

    1. C++ compiler (e.g., MinGW or Visual Studio)

    2. Run in administrator mode (for full key capture)

🛠️ How to Run

    ✅ Step 1: Compile the code 
        g++ keylogger.cpp -o keylogger.exe
    ✅ Step 2: Run
        keylogger.exes
    ✅ Step 3: Do Normal Typing (Open Notepad, browser, or any app)
    ✅ Step 4: Press ESC key to stop logging.
    ✅ Step 5: View Output(Open keylog.txt to check your output)

🛡️ Disclaimer
🚨 This project is for educational purposes only.
