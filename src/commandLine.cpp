//
// Created by vjgti on 5/3/2024.
//

#include "commandLine.h"

#include <iostream>

#include "keyTracker.h"
#include "miscFunctions.h"
#include "terminalCommands.h"
#include "commands.h"

void cmdMain() {
    std::string currCommand = "";
    int currPos = 1;
    xy wd = detectSize();
    //setCursorPosition(0,wd.y-2);
    //std::cout << ':';
    sendData(':', {0, wd.y-2});
    //setCursorPosition(0,wd.y-1);
    //std::cout << std::string(wd.x-1, ' ');
    sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
    while(true) { //TODO: swap to case and in main too
        const int key = key_press(); // blocks until a key is pressed
        xy available = detectSize();
        if (key == 10) { //enter
            commandCalls(currCommand);
            //setCursorPosition(0, wd.y-2);
            //std::cout<<std::string(wd.x-1, ' ');
            sendData(std::string(wd.x-1, ' '), {0, wd.y-2});
            //setCursorPosition(0, wd.y-1);
            //std::cout<<std::string(wd.x-1, ' ');
            sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
            return;
        } //TODO: call funtion search

        if (key == 8) {//backspace
            if (currCommand.length() != 0) {
                currCommand.pop_back();
                drawCommand(currCommand, wd);
                currPos -= 1;
                //setCursorPosition(0,wd.y-1);
                //std::cout<<std::string(wd.x-1, ' ');
                sendData(std::string(wd.x-1, ' '), {0,wd.y-1});
                //setCursorPosition(currPos-1, wd.y-1);
                //std::cout << char(217) << char(192);
                sendData(char(217), {currPos-1, wd.y-1});
                sendData(char(192));//TODO: add this to config options
            }
        }

        else {
            currCommand += key;
            drawCommand(currCommand, wd);
            //setCursorPosition(0, wd.y-1);
            //std::cout<<std::string(wd.x-1, ' ');
            sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
            //setCursorPosition(currPos, wd.y-1);
            //std::cout << char(217) << char(192);
            sendData(char(217), {currPos, wd.y-1});
            sendData(char(192));
            currPos += 1;
        }
        debugOutput(currCommand, -7);

    }
}

void drawCommand(const std::string& currCommand, const xy& wd) {
    //setCursorPosition(1, wd.y-2);
    //std::cout << std::string(wd.x-2, ' ');
    sendData(std::string(wd.x-2, ' '), {1, wd.y-2});
    //setCursorPosition(1, wd.y-2);
    //std::cout << currCommand;
    sendData(currCommand, {1, wd.y-2});
}

void commandCalls(std::string& currCommand) {
    //find first n char untill space
    //macth to funtcion
    //default no macth
    int firstSpaceIndex = currCommand.find(' ');
    std::string command = currCommand.substr(0, firstSpaceIndex);
    debugOutput(command, -9);


    if (command == "cd") {changeDir(currCommand);}
    else if (command == "help") {displayHelp(currCommand);}
    else if (command == "nvim") {launchNVim(currCommand);}
    else if (command == "refreshConfig") {refreshConfig();}

    else {displayError("Command does not exist");}
}