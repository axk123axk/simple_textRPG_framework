#ifndef INITIALIZECONSOLE_H  // Include-Guard, um doppelte Einbindung zu verhindern
#define INITIALIZECONSOLE_H

void InitializeConsole()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_MAXIMIZE);
    LONG style = GetWindowLong(hWnd, GWL_STYLE);
    style &= ~WS_BORDER;
    style &= ~WS_CAPTION;
    SetWindowLong(hWnd, GWL_STYLE, style);
    SetWindowPos(hWnd, HWND_TOP, -7, -7, GetSystemMetrics(SM_CXSCREEN) + 14, GetSystemMetrics(SM_CYSCREEN) + 14, SWP_NOZORDER | SWP_FRAMECHANGED);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD newSize;
    newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newSize);

    }

void SetCursorPosition(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, coord);
}

#endif