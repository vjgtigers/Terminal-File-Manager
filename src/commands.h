//
// Created by vjgti on 5/3/2024.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>


struct keyPressCodes_template {
    char quit;
    char refresh;
    char maintainStateRefresh;
    char clear;
    char enterCurrFolder;
    char enterParFolder;
    char down;
    char up;
    char search;
    char github;

};
extern keyPressCodes_template keyPressCodes ;

//update dir on user input through :cd <dir>
//works with absolute path. mostly works with rel path
void changeDir(const std::string& command);

//display help page for provided command - q to quit
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

//use debug clearBuffer to clear and writeBuffer to write to file
// addToBuffer to add text to buffer
void debug(std::string& command);

//deletes specified file - read help
void deleteFile(std::string& command);

//delete an empty directory
void deleteDir(std::string& command);
#endif //COMMANDS_H
