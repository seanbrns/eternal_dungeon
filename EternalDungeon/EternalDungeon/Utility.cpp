#include "stdafx.h"
#include "Utility.h"
#include <sstream>
#include <Windows.h>
#include <random>
#include <thread>
#include <chrono>

/******************************************************************************
* Print
*
******************************************************************************/
void WaitForUser()
{
    Print("", color_gray, false);
    std::cin.ignore(10000, '\n');
}

void Print(std::string str, size_t colorNum, bool endLine)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, static_cast<WORD>(colorNum));

    for (char c : str)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        std::cout << c << std::flush;
    }
    if (endLine)
    {
        std::cout << std::endl;
    }

    SetConsoleTextAttribute(hConsole, color_default);
}