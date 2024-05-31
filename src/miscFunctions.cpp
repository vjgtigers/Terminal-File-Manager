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
#include <cmath>

#include "miscFunctions.h"
#include "drawLayout.h"
#include "keyTracker.h"
#include "terminalCommands.h"

#define CSI "\x1b["

namespace fs = std::filesystem;

void sleep(const double t) {
    if(t>0.0) std::this_thread::sleep_for(std::chrono::milliseconds((int)(1E3*t+0.5)));
}

xy detectSize() {
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
    return {sbInfo.dwSize.X, sbInfo.dwSize.Y};

}

void debugOutput(const std::string& s, const int offset) {
    if(advancedCodes.debugModeScreenDisplay == true) {
        xy wd = detectSize();
        sendData(std::string(30, ' '), {wd.x-30,wd.y-(wd.y-20)+offset});
        sendData(s.substr(0,30), {wd.x-30,wd.y-(wd.y-20)+offset});
    }
}

void cursorToggle(bool enable) {
    if (enable == true) {
        sendData<std::string>(CSI "?25h");
    } else {
        sendData<std::string>(CSI "?25l");
    }
}


tmb_template tmbDeterminator() {
    xy wd = detectSize();
    int usableY = wd.y - 5;
    if (usableY % 2 == 0) {
        return {usableY / 2 - 1, usableY / 2 + 1, usableY / 2};
    } else {
        return {(usableY - 1) / 2, (usableY - 1) / 2 + 2, (usableY - 1) / 2};
    }
}


int globalState;




void updateCursorandPointerSync(const std::vector<fileInfoStruct>& fileNames) {
    xy wd = detectSize();
    tmb_template tmb = tmbDeterminator();
    debugOutput("file:" + fileNames[fileSelectionPointer].name, 4);
    debugOutput(std::to_string(fileSelectionPointer), 1);

    if (globalState == 3) {
        drawSelectionPointer({0, fileSelectionPointer+2});
    }

    else if (fileSelectionPointer < tmb.top_length) {
        drawSelectionPointer({0, fileSelectionPointer+2});
        if (globalState != 0) {
            globalState = 0;
        }
    }
    else if (fileSelectionPointer >= fileNames.size()-tmb.bottom_length) {
        int y = wd.y-3 - (fileNames.size()-fileSelectionPointer);
        drawSelectionPointer({0,y});
        if (globalState != 2) {
            globalState = 2;
        }

    }
    else {
        if (globalState != 1) {
            globalState = 1;
            drawSelectionPointer({0, tmb.middle_pos});
        }
    }
displayFileInfo(fileNames);
}




void globalStateCalculator() {
    globalState = 0;
    tmb_template tmb = tmbDeterminator();
    if (tmb.bottom_length + tmb.top_length + 1 >= fileInformation.size()) {
        globalState = 3;
    }
    else if (fileSelectionPointer < tmb.top_length) {
            globalState = 0;
    }
    else if (fileSelectionPointer >= fileInformation.size()-tmb.bottom_length) {
            globalState = 2;
    }
    else {
            globalState = 1;
    }
}



temp_size calcSize(std::uintmax_t size) {
    int o{};
    std::string test2 = "";
    double mantissa = size;
    for (; mantissa >= 1024.; mantissa /= 1024., ++o);
    if (std::ceil(mantissa * 10.) / 10. == 0){return {0, ' '};}
    return {std::ceil(mantissa * 10.) / 10., "BKMGTPE"[o]};
}


void fileInput(std::vector<fileInfoStruct>& fileNames, const std::string& pathDir) {
    struct stat sb;
    int temp_dec;
    int temp_zero;
    fileNames.clear();
    temp_size temp;
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
            fileNames.push_back({outfilename_str.substr(chopLen),"","oaeu", "aoeu", "ooeu"});
            outfilename_str.length() >= outfilename_str.find('.')
                ? (fileNames.back().extention = outfilename_str.substr(outfilename_str.find('.')))
                : "true";

            temp = calcSize(fs::file_size(fileName));
            temp_dec = std::to_string(temp.size).find('.');
            temp_zero = std::to_string(temp.size).find('0', temp_dec);
            if (temp_dec +1 == temp_zero) {temp_zero-1;}
            if (temp.suffix != 'B') {
                fileNames.back().size = std::to_string(temp.size).substr(0,temp_zero) + temp.suffix + 'B';
            }
            else {
                fileNames.back().size = std::to_string(temp.size).substr(0,temp_zero) + temp.suffix;
            }
            if (temp.size == 0) {fileNames.back().size = "0B";}
        }
        else {
            fileNames.push_back({outfilename_str.substr(chopLen),"<DIR>","", "aoeu", "ooeu"});
        }
    }

    std::vector<fileInfoStruct> fileNames2(fileNames.size());
    int p = 0;
    for(fileInfoStruct data: fileNames) {
        if (data.extention == "<DIR>") {
            fileNames2[p] = data;
            p += 1;
        }
    }
    for(fileInfoStruct data: fileNames) {
        if (data.extention != "<DIR>") {
            fileNames2[p] = data;
            p += 1;
        }
    }
    p = 0;
    for(fileInfoStruct data : fileNames2) {
        fileNames[p] = data;
        p +=1;
    }
    globalStateCalculator();
}

void changeDir(std::vector<fileInfoStruct>& fileNames, std::string& pathDir) {
    for (int i = pathDir.length()-1; i >= 0; --i) {
        if(pathDir[i]== '\\') {
            if(!(i <3)) {
                pathDir = pathDir.substr(0,i);
                break;
            } else {
                pathDir = pathDir.substr(0, i+1);
            }
        }
    }
    fileInput(fileNames, pathDir);
    dirBackRefresh(fileNames);
}


void researchDir() {
    fileInput(fileInformation, path_dir);
    dirBackRefresh(fileInformation);
}


std::vector<std::string> tokenizeInput(std::string init) {
    int currentPos = 0;
    std::vector<std::string> tokens;
    int end;
    if (init.ends_with(' ') == false && init.ends_with('"') == false) {
        init += " ";
    }
    while (true) {
        if (init.find('"',currentPos) == std::string::npos && init.find(' ', currentPos) == std::string::npos) {
            break;
        }
        if (init.find('"', currentPos) < init.find(' ', currentPos)) {
            end = init.find('"', currentPos+1);
            tokens.push_back(init.substr(currentPos +1, end-currentPos -1));
            if (end+1 == 0) {
                break;
            }
            currentPos = end+2;
        } else {
            end = init.find(' ', currentPos + 1);
            tokens.push_back(init.substr(currentPos, end -currentPos));
            if (end+1 == 0) {
                break;
            }
            currentPos = end+1;
        }
    }
    return tokens;
}


void openGithubDraw() {
    clearScreen();
    sendData<std::string>("To open github page press 1 \n", {0,0});
    sendData<std::string>("To report a bug press 2 \n");
    sendData<std::string>("To request a feature press 3 \n");
    sendData<std::string>("To open website press 4 (not very good) \n");
    sendData<std::string>("To return to program press 'q' \n");
}

void openGithub() {
    openGithubDraw();

    while(true) {
        const int key = key_press();
        if (char(key) == 'q') {
            maintainStateRefresh(fileInformation);
            return;
        }
        else if (char(key) == '1') {
            system("start https://github.com/vjgtigers/Terminal-File-Manager");
            openGithubDraw();
        }
        else if (char(key) == '2') {
            system("start https://github.com/vjgtigers/Terminal-File-Manager/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=");
            openGithubDraw();
        }
        else if (char(key) == '3') {
            system("start https://github.com/vjgtigers/Terminal-File-Manager/issues/new?assignees=&labels=&projects=&template=feature_request.md&title=");
            openGithubDraw();
        }
        else if (char(key) == '4') {
            system("start https://tfv.xerwai.com");
            openGithubDraw();
        }
    }
}