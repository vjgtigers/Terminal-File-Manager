//
// Created by vjgti on 4/27/2024.
//

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H
#include <string>
#include <vector>

#include "drawLayout.h"


//can be used for debugging //most likely wont be used in accutall product

void println(const std::string& s="");

//prehaps an inproved version of sleep? im not sure
void sleep(const double t);

//struct for k,y coords
struct xy {
    int x;
    int y;
};

//struct used for tmbDeterminator()
struct tmb_tem {
    int top_length;
    int middle_pos;
    int bottom_length;
};

extern int fileSelectionPointer;
typedef struct fileInfoStruct;
extern std::vector<fileInfoStruct> fileNames;

//calculate where the selection cursor is to be drawn when filepointer changes
void updateCursorandPointerSync(const std::vector<fileInfoStruct>& fileNames);

//calculates the centerpoint of file drawing and the amount of files that can be displayed above and below
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
//1 - the middle section of files
//3 - special case for if there is less needed slots than is provided
extern int globalState;

//used to calclate global state - needed for refreshing screen with diffrent size
void globalStateCalculator();

#endif //MISCFUNCTIONS_H
