//
// Created by vjgti on 5/3/2024.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>


struct keyPressCodes_temp {
    char quit;
    char refresh;
    char maintainStateRefresh;
    char clear;
    char enterCurrFolder;
    char enterParFolder;
    char down;
    char up;

};
extern keyPressCodes_temp keyPressCodes ;

//changes dir to absoulute path
//if rel path then curret functinoaliy is undefined
void changeDir(const std::string& command);


//clears screen and displays help data for passed command ie help cd
//press q to return to file screen
void displayHelp(const std::string& command);

//displays message on the last row
//gets cleared when user starts typing a new command
void displayError(const std::string& message);


//launch neovim
//if file name is provided opens that file
//else checks if pointer is on a file if so opens that in neovim
//if folder then lauches blank nvim
void launchNVim(const std::string& command);

//hot refreshable config so program doesnt have to be relaunched on config change
void refreshConfig();

//create dir in current path with provided name
void createDir(std::string& command);

//creates new file - doesnt work if file already exists but no error message
void createFile(std::string& command);
#endif //COMMANDS_H
