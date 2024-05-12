//
// Created by vjgti on 5/3/2024.
//

#include "commandLine.h"

#include <iostream>

#include "keyTracker.h"
#include "miscFunctions.h"
#include "terminalCommands.h"
#include "commands.h"
#include "configInfo.h"

void cmdMain() {
    std::string currCommand = "";
    int currPos = 1;
    xy wd = detectSize();
    sendData(':', {0, wd.y-2});
    sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
    while(true) { //TODO: swap to case and in main too
        const int key = key_press(); // blocks until a key is pressed
        xy available = detectSize();

        if (key == 27) {
            sendData(std::string(wd.x-1, ' '), {0, wd.y-2});
            sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
            return;
        }
        if (key == 10) { //enter
            commandCalls(currCommand);
            sendData(std::string(wd.x-1, ' '), {0, wd.y-2});
            sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
            return;
        } //TODO: call funtion search

        if (key == 8) {//backspace
            if (currCommand.length() != 0) {
                currCommand.pop_back();
                drawCommand(currCommand, wd);
                currPos -= 1;
                sendData(std::string(wd.x-1, ' '), {0,wd.y-1});
                sendData(renderCodes.cmdLcursor, {currPos-1, wd.y-1});
                sendData(renderCodes.cmdRcursor);
            }
        }

        else {
            currCommand += key;
            drawCommand(currCommand, wd);
            sendData(std::string(wd.x-1, ' '), {0, wd.y-1});
            sendData(renderCodes.cmdLcursor, {currPos, wd.y-1});
            sendData(renderCodes.cmdRcursor);
            currPos += 1;
        }
        debugOutput(currCommand, -7);

    }
}

void drawCommand(const std::string& currCommand, const xy& wd) {
    sendData(std::string(wd.x-2, ' '), {1, wd.y-2});
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
    else if (command == "sco" || command == "setConfigOption") {writeUserConfig(currCommand);}
    else if (command == "tco" || command == "testConfigOption") {tempUserConfig(currCommand);}
    else if (command == "mkdir") {createDir(currCommand);}

    else {displayError("Command does not exist");}
}