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
void changeDir(const std::string& command) {
        std::string subCommand = command.substr(command.find(' ') +1);
        struct stat sb;
        if (stat(subCommand.c_str(), &sb) != 0) {
                return;
        }
        if (subCommand.back() != '\\') {
                subCommand += '\\';
        }
        path_dir = subCommand;
        backOneDir(fileInformation, path_dir);

}


void displayHelp(const std::string& command) {
    std::string subCommand = command.substr(command.find(' ') + 1);
    debugOutput(subCommand + " aouthn", -14);
    std::ifstream openFile ("./helpInfo/" + subCommand + ".txt");
    if (openFile.is_open()) {
            debugOutput(subCommand + " 11111", -14);
            std::string fileData;
            clearScreen();
            setCursorPosition(0,0);
            while (openFile) {
                    fileData = openFile.get();
                    std::cout << fileData;
            }
    }
        while(true) {
                const int key = key_press();
                if (key == 'q') {
                        maintainStateRefresh(fileInformation);
                        break;
                }
        }
}