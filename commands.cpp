//
// Created by vjgti on 5/3/2024.
//

#include "commands.h"

#include <string>

#include "miscFunctions.h"


void changeDir(const std::string& command) {
        std::string subCommand = command.substr(command.find(' ') +1);
        debugOutput(subCommand, -10);

        debugOutput(std::to_string(subCommand.back()) + "ansoteuh", -11);
        if (subCommand.back() != '\\') {
                subCommand += '\\';

        }
        path_dir = subCommand;
        backOneDir(fileInformation, path_dir);

}
