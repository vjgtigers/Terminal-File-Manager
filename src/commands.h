//
// Created by vjgti on 5/3/2024.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>

//changes dir to absoulute path
//if rel path then curret functinoaliy is undefined
void changeDir(const std::string& command);


//clears screen and displays help data for passed command ie help cd
//press q to return to file screen
void displayHelp(const std::string& command);

//displays message on the last row
//gets cleared when user starts typing a new command
void displayError(const std::string& message);

#endif //COMMANDS_H
