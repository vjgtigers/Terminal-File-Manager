//
// Created by vjgti on 3/20/2025.
//

#include <fstream>
#include <windows.h>

#include "simulation.h"



vector<string> simulation::readSimulationFile(string filepath) {
    ifstream simFile;
    simFile.open(filepath);
    if(simFile.is_open() != true) {
        displayError("File could not be opened");
    }
    vector<string> simCommandList;
    string line;
    while(getline(simFile, line)) {
        simCommandList.push_back(line);
    }
    return simCommandList;
}

vector<commandItems> simulation::convertToCommand(vector<string> strList) {
    vector<commandItems> vect;
    for(string &p : strList) {
        if (p[0] != '*') {
            continue;
        }
        commandItems item{};
        item.c = p[1];
        item.amount = 1;
        item.delayMs = 500;
        vect.push_back(item);

    }

    return vect;
}




void simulation::goToNextCommand() {
    currentCommandIndex+=1;
    currentCommandCount=0;
}

char simulation::returnCurrentCommand(bool delay) {
    while(currentCommandCount == commandList[currentCommandIndex].amount-1) {
        goToNextCommand();
    }
    char c = commandList[currentCommandIndex].c;
    if(delay == true) {
        Sleep(commandList[currentCommandIndex].delayMs);
    }
    currentCommandCount+=1;
    return c;

}
