//
// Created by vjgti on 4/27/2024.
//

#ifndef MISCFUNCTIONS_H
#define MISCFUNCTIONS_H
#include <string>
#include <vector>
#include <cstdint>
#include "drawLayout.h"


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


// ReSharper disable once CppDeclarationSpecifierWithoutDeclarators
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


//read file names if dir and add to vector
void fileInput(std::vector<fileInfoStruct>& fileNames, const std::string& pathDir);

//go to the parent dir - accutly can do both i think
void changeDir(std::vector<fileInfoStruct>& fileNames, std::string& pathDir);


struct temp_size {
    double size;
    char suffix;
};


//caluclate displayable size of file
//original code (https://en.cppreference.com/w/cpp/filesystem/file_size)
//EXTREAMLY modified though
temp_size calcSize(std::uintmax_t size);

//regets files and folders from dir
void researchDir();

//return a vector of tokens for user input
//take into accout quotes
std::vector<std::string> tokenizeInput(std::string init);
#endif //MISCFUNCTIONS_H
