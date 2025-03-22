//
// Created by vjgti on 3/20/2025.
//

#include <fstream>

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
