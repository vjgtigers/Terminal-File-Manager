//
// Created by vjgti on 4/27/2024.
//

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H
#include <string>


//can be used for debugging //most likely wont be used in accutall product

void println(const std::string& s="");

//prehaps an inproved version of sleep? im not sure
void sleep(const double t);

//struct for k,y coords
struct xy {
    int x;
    int y;
};

xy detectSize();
#endif //MISCFUNCTIONS_H
