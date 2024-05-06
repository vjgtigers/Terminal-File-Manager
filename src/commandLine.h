//
// Created by vjgti on 5/3/2024.
//

#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <string>

//main loop for typing out command
void cmdMain();

typedef struct xy;

//displays the current input for the command at the second to last line of the screen
void drawCommand(const std::string& currCommand, const xy& wd);

void commandCalls(std::string& currCommands);

#endif //COMMANDLINE_H
