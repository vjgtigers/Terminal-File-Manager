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

//clear screen - done
//while true loop - done
//section to display what type of search is working. ie regular regex etc -done
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


void lsDrawCommand(std::string currCommand, xy wd) {
    int displayLength = wd.x/2;
    int displayStart = 3;
    sendData(std::string(displayLength, ' '), {displayStart, 7});
    sendData(currCommand, {displayStart, 7});
}

void lsCmdMain(std::vector<fileInfoStruct>& files) {
    std::string currCommand = "";
    int currPos = 1;
    xy wd = detectSize();
    int displayLength = wd.x/2;
    int displayStart = 3;
    sendData(std::string(displayLength, ' '), {displayStart, 6});
    while(true) {
        const int key = key_press(); // blocks until a key is pressed

        if (key == 27) {
            return;
        }
        if (key == 10) { //enter
            sendData(std::string(7, ' '), {displayStart, 7});
            lsCall(currCommand, files);
            return;
        }

        if (key == 8) {//backspace
            if (currCommand.length() != 0) {
                currCommand.pop_back();
                lsDrawCommand(currCommand, wd);
                currPos -= 1;
                sendData(std::string(wd.x-1, ' '), {0,8});
                sendData(renderCodes.cmdLcursor, {currPos-1 + 2, 8});
                sendData(renderCodes.cmdRcursor);
            }
        }

        else {
            currCommand += key;
            lsDrawCommand(currCommand, wd);
            sendData(std::string(wd.x-1, ' '), {0, 8});
            sendData(renderCodes.cmdLcursor, {currPos + 2, 8});
            sendData(renderCodes.cmdRcursor);
            currPos += 1;
        }
        debugOutput(currCommand, -7);
    }
}


void lsSearch(std::string& sString) {
    return;
}
//TODO: the file list that will be used will be different becauge the lsSearch will change it
void lsCall(std::string& sString, std::vector<fileInfoStruct>& files) {
    system(("nvim " +path_dir+ '\\'+  files[0].name).c_str());
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    toggleVT(true);

    return;
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
    lsCmdMain(files);
}
