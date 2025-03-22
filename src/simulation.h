//
// Created by vjgti on 3/20/2025.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "commands.h"

using namespace std;

//TODO: implement a specific class that can be used for all of this an in attempt to be more object oriented
//class can have something like a current item counter for how many timse its been called so know when it hits amount
//what command in the vector its currently on
//etc



struct commandItems {
    char c; //letter to be sent as input
    int delayMs; //how long to wait before sending this input
    int amount; //how many times to use this command ie 3, would be a a a
};

vector<commandItems> readSimulationFile(string filepath);


class simulation {
public:
    vector<commandItems> commandList;
    int currentCommandCount;
    int currentCommandIndex;
    vector<string> readSimulationFile(string filepath);
    vector<commandItems> convertToCommand(vector<string>);
    void goToNextCommand();
    char returnCurrentCommand();
    //continue if anything else more can be thought of

};

#endif //SIMULATION_H
