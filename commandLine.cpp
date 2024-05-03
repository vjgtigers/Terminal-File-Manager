//
// Created by vjgti on 5/3/2024.
//

#include "commandLine.h"

#include <iostream>

#include "keyTracker.h"
#include "miscFunctions.h"
#include "terminalCommands.h"


void cmdMain() {
    std::string currCommand = "";
    int currPos = 1;
    xy wd = detectSize();
    setCursorPosition(0,wd.y-2);
    std::cout << ':';
    while(true) {

        const int key = key_press(); // blocks until a key is pressed
        xy available = detectSize();
        if (key == 10) {setCursorPosition(0, wd.y-2); std::cout<<std::string(wd.x-1, ' ');return;} //TODO: call funtion search
        else if (key == 8) { if (currCommand.length() != 0) {currCommand.pop_back(); drawCommand(currCommand, wd);}}
        else {currCommand += key; drawCommand(currCommand, wd);}
        debugOutput(currCommand, -7);

    }

}

void drawCommand(const std::string& currCommand, const xy& wd) {
    setCursorPosition(1, wd.y-2);
    std::cout << std::string(wd.x-2, ' ');
    setCursorPosition(1, wd.y-2);
    std::cout << currCommand;
}
