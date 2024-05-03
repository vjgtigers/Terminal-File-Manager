//
// Created by vjgti on 5/3/2024.
//

#include "commands.h"

#include <string>
#include <iostream>
#include <sys/stat.h>
#include "miscFunctions.h"


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
