//
// Created by vjgti on 5/3/2024.
//

#include "commands.h"

#include <cstring>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <fstream>

#include "keyTracker.h"
#include "miscFunctions.h"
#include "configInfo.h"
#include "terminalCommands.h"



void displayError(const std::string &message) {
    xy wd = detectSize();
    sendData(message, {0, wd.y-1});
}


void changeDir(const std::string &command) {
    std::string subCommand = command.substr(command.find(' ') + 1);
    struct stat sb;
    std::string temp = path_dir;
    if (subCommand[1] == ':') {
        if (subCommand.back() != '\\') {
            subCommand += '\\';
        }
        path_dir = subCommand;

    } else if (subCommand.substr(0, 2) == "..") {
        char full[_MAX_PATH];
        if (_fullpath(full, (path_dir + "\\" + subCommand).c_str(), _MAX_PATH) != NULL) {
            path_dir = full;
            path_dir += '\\';
        } else {
            displayError("Change Dir Failed");
        }

    } else {
        path_dir = path_dir + "\\" + subCommand + "\\";
    }

    if (stat(path_dir.c_str(), &sb) != 0) {
        displayError("Invalid directory");
        path_dir = temp;
        return;
    }

    changeDir(fileInformation, path_dir);
}

void displayHelp(const std::string &command) {
    std::string subCommand = command.substr(command.find(' ') + 1);
    debugOutput(subCommand + " aouthn", -14);
    std::ifstream openFile("./helpInfo/" + subCommand + ".txt");
    if (openFile.is_open()) {
        debugOutput(subCommand + " 11111", -14);
        std::string fileData;
        clearScreen();
        // setCursorPosition(0, 0);
        sendData("Command: " + command.substr(command.find(' ')) + "\n", {0,0});
        while (openFile) {
            fileData = openFile.get();
            sendData(fileData);
        }
        sendData<std::string>("Press 'q' to quit");
    } else {
        displayError("Command does not exist or no help file");
        return;
    }
    while (true) {
        const int key = key_press();
        if (key == 'q') {
            maintainStateRefresh(fileInformation);
            break;
        }
    }
}


void launchNVim(const std::string& command) {
    if (command.length() == 4) {
        if (fileInformation[fileSelectionPointer].extention != "<DIR>") {
            system(("nvim " + path_dir + "\\" + fileInformation[fileSelectionPointer].name).c_str());
        }
        else {system("nvim");}
     }
    else {
        std::string fileName = command.substr(command.find(' ')+1);
        system(("nvim " + path_dir + "\\" + fileName).c_str());
    }
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    toggleVT(true);
    maintainStateRefresh(fileInformation);
}

void refreshConfig() {
    readUserConfig();
    maintainStateRefresh(fileInformation);
}

void createDir(std::string& command) {
    std::vector<std::string> tokens = tokenizeInput(command);
    std::string Fname = tokens[1];

    if (_mkdir((path_dir +"\\" +Fname).c_str()) == 0) {
    } else {
        displayError("Error Creating folder: " + command.substr(command.find(' ') +1));
    }
    researchDir();
    return;
}

void createFile(std::string& command) {
    std::vector<std::string> tokens = tokenizeInput(command);
    std::string Fname;
    Fname = tokens[1];
    std::string path = path_dir + '\\' + Fname;
    HANDLE h = CreateFileA(path.c_str(),    // name of the file
                      GENERIC_WRITE, // open for writing
                      0,             // sharing mode, none in this case
                      nullptr,             // use default security descriptor
                      CREATE_NEW, // dont overwrite if exists - could add option
                      FILE_ATTRIBUTE_NORMAL,
                      nullptr);

    if (h) {
        CloseHandle(h);
    } else { //TODO: doesnt work
        displayError(std::to_string(GetLastError()));
    }
    researchDir();
    return;
}

extern std::vector<std::string> saveOutData;

void debug(std::string& command) {
    std::vector<std::string> tokens = tokenizeInput(command);

    if (tokens[1] == "clearBuffer") {
        saveOutData.clear();
    }
    else if (tokens[1] == "writeBuffer") {

        auto t1 = std::chrono::system_clock::now();
        std::time_t t2 = std::chrono::system_clock::to_time_t(t1);
        char* o = ctime(&t2);
        std::string s((LPCTSTR)o); //contvert from c string to std::string
        for (int i = 0; i < s.length(); i++) {
            if (s.at(i) == ':' || s.at(i) == ' ' || s.at(i) == '\n') {
                s.at(i) = '-';
            }
        }
        std::string fname = "debugData_" + s + ".txt";

        std::ofstream file(fname);
        for(auto t : saveOutData) {
            file << t << std::endl;
        }
        file.close();
    }

    else if (tokens[1] == "addToBuffer") {
        saveOutData.push_back(tokens[2] + "\n");
    }
}

void deleteFile(std::string& command) {
    std::vector<std::string> tokens = tokenizeInput(command);
    std::string fName;
    std::string fNameFull;
    if (tokens.size() == 1) {
        displayError("Add Arugment - read help page");
        return;
    }
    if (tokens[1] == "-c") {
        fName = fileInformation[fileSelectionPointer].name;
        fNameFull = path_dir + '\\' + fName;
    }
    else if (tokens[1] == "-n") {
        fName = tokens[2];
        fNameFull = path_dir + '\\' + fName;
    }
    else {
        displayError("Wrong argument");
        return;
    }
    DeleteFile(fNameFull.c_str());
    researchDir();
    return;
}

void deleteDir(std::string& command) { //TODO: currently only deletes empty dirs
    //https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shfileoperationa
    std::vector<std::string> tokens = tokenizeInput(command);
    std::string fName = tokens[1];
    std::string fNameFull = path_dir + '\\'  +fName;
    RemoveDirectoryA(fNameFull.c_str());

    researchDir();
    return;
}