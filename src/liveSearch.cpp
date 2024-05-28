//
// Created by vjgti on 5/21/2024.
//

#include "liveSearch.h"

#include <ranges>
#include <string>
#include <vector>

#include "commands.h"
#include "keyTracker.h"
#include "terminalCommands.h"

//clear screen
//while true loop
//section to display what type of search is working. ie regular regex etc
//search
//list of valid files
    //can i scroll through these?
//amount of files returned
//recursive search?

void lsBaseLayout(std::string& searchPattern) {
    xy wd = detectSize();
    displayTime();
    displayDirBar(path_dir);
    int displayLength = wd.x/2;
    int displayStart = 3;
    if(searchPattern.length() < displayLength) {
        sendData(searchPattern, {displayStart, 3});
    }
    sendData(std::string(displayLength, renderCodes.divHori), {displayStart, 4});
    sendData(std::string(displayLength, renderCodes.divHori), {displayStart, 2});
    sendData(renderCodes.divVert, {displayStart -1, 3});
    sendData(renderCodes.divVert, {displayStart + displayLength, 3});
    sendData(std::string(wd.x, renderCodes.divHori), {0,1});


    sendData(std::string(displayLength, renderCodes.divHori), {displayStart, 6});
    sendData(std::string(displayLength, renderCodes.divHori), {displayStart, 8});
    sendData(renderCodes.divVert, {displayStart -1, 7});
    sendData(renderCodes.divVert, {displayStart + displayLength, 7});
    sendData(std::string(wd.x, renderCodes.divHori), {0,1});


    sendData(std::string(displayLength, renderCodes.divHori), {displayStart, wd.y-2});
    sendData(std::string(displayLength, renderCodes.divHori), {displayStart, 9});

    for(int i = 10; i < wd.y-2; ++i) {
        sendData(renderCodes.divVert, {displayStart -1, i});
        sendData(renderCodes.divVert, {displayStart + displayLength, i});
    }
}


void liveSearch(std::vector<fileInfoStruct> files, std::string command) {
    std::string searchPattern = advancedCodes.defaultSearchPattern;
    std::string searchString = "";
    clearScreen();
    lsBaseLayout(searchPattern);


    if (!command.empty()) {
        std::vector<std::string> tokens = tokenizeInput(command);
        for(int i = 0; i < tokens.size(); ++i) {
            if(tokens[i] == "-t" && i+1 < tokens.size()) {
                searchPattern = tokens[i+1];
            }
            if(tokens[i] == "-s" && i+1 < tokens.size()) {
                searchString = tokens[i+1];
            }
        }
    }
    while(true) {
        const int key = key_press();
        if (key == keyPressCodes.quit) {
            return;
        }
    }
}
