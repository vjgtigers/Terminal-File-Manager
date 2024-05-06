//
// Created by vjgti on 5/3/2024.
//

#include "commands.h"

#include <string>
#include <iostream>
#include <sys/stat.h>

#include <fstream>

#include "keyTracker.h"
#include "miscFunctions.h"
#include "terminalCommands.h"


//TODO: parser to accully handle ..\
//update dir


void displayError(const std::string &message) {
    xy wd = detectSize();
    setCursorPosition(0, wd.y - 1);
    std::cout << message;
}

void changeDir(const std::string &command) {
    std::string subCommand = command.substr(command.find(' ') + 1);
    struct stat sb;

    if (subCommand[1] == ':') {
        if (subCommand.back() != '\\') {
            subCommand += '\\';
        }
        path_dir = subCommand;

    } else if (subCommand.substr(0, 2) == "..") {
        char full[_MAX_PATH];
        if (_fullpath(full, (path_dir + "\\" + subCommand).c_str(), _MAX_PATH) != NULL) {
            path_dir = full;
        } else {
            displayError("Change Dir Failed");
        }

    } else {
        path_dir = path_dir + "\\" + subCommand + "\\";
    }

    if (stat(subCommand.c_str(), &sb) != 0) {
        displayError("Invalid directory");
        return;
    }

    backOneDir(fileInformation, path_dir);
}


void displayHelp(const std::string &command) {
    std::string subCommand = command.substr(command.find(' ') + 1);
    debugOutput(subCommand + " aouthn", -14);
    std::ifstream openFile("./helpInfo/" + subCommand + ".txt");
    if (openFile.is_open()) {
        debugOutput(subCommand + " 11111", -14);
        std::string fileData;
        clearScreen();
        setCursorPosition(0, 0);
        while (openFile) {
            fileData = openFile.get();
            std::cout << fileData;
        }
    } else {
        displayError("Command Does Not exist");
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
