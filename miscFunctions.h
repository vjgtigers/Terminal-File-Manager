//
// Created by vjgti on 4/27/2024.
//

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H
#include <string>
#include <vector>


//can be used for debugging //most likely wont be used in accutall product

void println(const std::string& s="");

//prehaps an inproved version of sleep? im not sure
void sleep(const double t);

//struct for k,y coords
struct xy {
    int x;
    int y;
};


struct tmb_tem {
    int top_length;
    int middle_pos;
    int bottom_length;
};

extern int fileSelectionPointer;


void updateCursorandPointerSync(const std::vector<std::string>& fileNames);

tmb_tem tmbDeterminator();

//detect the amout of "rows/coulums" that are avalible
//doeset work if you scroll in/out to make text larger or smaller
xy detectSize();

//debugging output for the time being
void debugOutput(const std::string& s, const int offset);


//used to disable/enable cursor
//shouldnt really need to be re enabled
void cursorToggle(bool enable);


//determin where in the file list should be drawn
//0 - begining till cant anymore
//2 - working from bottom up, last files to beginning till cant anymore
//1 - the middle section of files TODO: this
extern int globalState;

#endif //MISCFUNCTIONS_H
