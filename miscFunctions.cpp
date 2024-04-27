//
// Created by vjgti on 4/27/2024.
//

#include "miscFunctions.h"

#include <iostream>
#include <thread>
#include <Windows.h>


void println(const std::string& s) {
    std::cout << s << std::endl;
}

void sleep(const double t) {
    if(t>0.0) std::this_thread::sleep_for(std::chrono::milliseconds((int)(1E3*t+0.5)));
}

xy detectSize() {
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
    return {sbInfo.dwSize.X, sbInfo.dwSize.Y};

}