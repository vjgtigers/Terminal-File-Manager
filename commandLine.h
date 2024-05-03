//
// Created by vjgti on 5/3/2024.
//

#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <string>

void cmdMain();

typedef struct xy;

void drawCommand(const std::string& currCommand, const xy& wd);
#endif //COMMANDLINE_H
