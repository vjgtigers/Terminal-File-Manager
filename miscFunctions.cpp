//
// Created by vjgti on 4/27/2024.
//
#include <filesystem>
#include <iostream>
#include <thread>
#include <Windows.h>
#include <bits/fs_path.h>
#include <string>
#include <sys/stat.h>


#include "miscFunctions.h"
#include "drawLayout.h"
#include "terminalCommands.h"

#define CSI "\x1b["

namespace fs = std::filesystem;

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

void debugOutput(const std::string& s, const int offset) {
    xy wd = detectSize();
    setCursorPosition(wd.x-30,wd.y-(wd.y-20)+offset);
    std::cout << std::string(30, ' ');
    setCursorPosition(wd.x-30,wd.y-(wd.y-20)+offset);
    std::cout << s.substr(0,30);
}


void cursorToggle(bool enable) {
    if (enable == true) {
        printf(CSI "?25h");
    } else {
        printf(CSI "?25l");
    }
}


tmb_tem tmbDeterminator() {
    xy wd = detectSize();
    int usableY = wd.y - 5;
    //std::cout << usableY/2-1 <<' '<< usableY/2 <<' '<<usableY/2;
    if (usableY % 2 == 0) {
        return {usableY / 2 - 1, usableY / 2 + 1, usableY / 2};
    } else {
        return {(usableY - 1) / 2, (usableY - 1) / 2 + 2, (usableY - 1) / 2};
    }
}


int globalState;




void updateCursorandPointerSync(const std::vector<fileInfoStruct>& fileNames) {
    xy wd = detectSize();
    tmb_tem tmb = tmbDeterminator();
    debugOutput("file:" + fileNames[fileSelectionPointer].name, 4);
    debugOutput(std::to_string(fileSelectionPointer), 1);

    if (globalState == 3) {
        drawSelectionPointer({0, fileSelectionPointer+2});
    }

    else if (fileSelectionPointer < tmb.top_length) {
        drawSelectionPointer({0, fileSelectionPointer+2});
        if (globalState != 0) {
            globalState = 0;
            displayFileInfo(fileNames);
        }
    }
    else if (fileSelectionPointer >= fileNames.size()-tmb.bottom_length) {
        int y = wd.y-3 - (fileNames.size()-fileSelectionPointer);
        drawSelectionPointer({0,y});
        if (globalState != 2) {
            globalState = 2;
            displayFileInfo(fileNames);
        }

    }
    else {
        if (globalState != 1) {
            globalState = 1;
            drawSelectionPointer({0, tmb.middle_pos});
        }
        displayFileInfo(fileNames);
    }

}




void globalStateCalculator() {
    globalState = 0;
    tmb_tem tmb = tmbDeterminator();
    if (tmb.bottom_length + tmb.top_length + 1 >= fileInformation.size()) {
        globalState = 3;
    } //TODO : update global state on size rechange/refresh - DONE?

}



void fileInput(std::vector<fileInfoStruct>& fileNames, const std::string& pathDir) {
    struct stat sb;

    //If the path is just the drive letter, the chopLen is off by one
    int chopLen = pathDir.length() +1;
    if (pathDir.length() <= 3) {chopLen -= 1;}

    for (const auto& fileName : fs::directory_iterator(pathDir)) {
        // Converting the path to const char * in the
        // subsequent lines
        std::filesystem::__cxx11::path outfilename = fileName.path();
        std::string outfilename_str = outfilename.string();
        // cout << "test "<< outfilename_str.substr(path1.length()+1) << endl;

        const char* path1 = outfilename_str.c_str();

        // Testing whether the path points to a
        // non-directory or not If it does, displays path
        if (stat(path1, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
            // cout << path << endl;
            fileNames.push_back({outfilename_str.substr(chopLen),"0","oaeu", "aoeu", "ooeu"});
        }
        else {
            fileNames.push_back({outfilename_str.substr(chopLen),"1","oaeu", "aoeu", "ooeu"});
        }
    }

    globalStateCalculator();
}

