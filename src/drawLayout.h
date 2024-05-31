//
// Created by vjgti on 4/27/2024.
//

#ifndef DRAWLAYOUT_H
#define DRAWLAYOUT_H
#include <string>
#include <vector>

#include "miscFunctions.h"

//type and if active of the diffrent information to be displayed
struct fd_display_data {
    bool active;
    int size;
};
extern struct fd_display_data nameView;
extern struct fd_display_data extentionView;
extern struct fd_display_data sizeView;
extern struct fd_display_data modifiedView;
extern struct fd_display_data createdView;

extern int fileSelectionPointer;

struct renderCodes_template {
    char pointer;
    char divVert;
    char divHori;
    char topCombine;
    char bottomCombine;
    char allcombine;
    char cmdLcursor;
    char cmdRcursor;
};
struct advancedCodes_template {
    bool debugMode;
    bool disableConfigLoad;
    bool debugModeScreenDisplay;
    std::string defaultSearchPattern;
};
extern advancedCodes_template advancedCodes;

extern renderCodes_template renderCodes;

extern std::string path_dir;

// ReSharper disable once CppDeclarationSpecifierWithoutDeclarators
typedef struct fileInfoStruct;
// ReSharper disable once CppDeclarationSpecifierWithoutDeclarators
typedef struct xy;

//used to draw the base outline of the main file view screen
void drawBaseLayout();

//draws pointer that shows what file is currently selected
void drawSelectionPointer(xy xy_cursor);

extern std::string currTime;

//can be used to clear the entire screen and redraw
//helpful if viewing window gets messed up on resize
void refreshScreen(const std::vector<fileInfoStruct>& fileNames);

//display the current dir at the top of the screen
void displayDirBar(const std::string& dirName);

//display the current time
void displayTime();

struct fileInfoStruct {
    std::string name;
    std::string extention;
    std::string size;
    std::string modDate;
    std::string createDate;
};
extern std::vector<fileInfoStruct> fileInformation;


struct topBarSettings_template {
    int dirMaxLen;
    int timeMaxLen;
};
extern topBarSettings_template topBarSettings;


//display the filenames in the first colum
void displayFileInfo(const std::vector<fileInfoStruct>& fileNames);

//display more information about the files
void extendedFileInfoDisplay();

//used to redraw file screen from point left off - usefull if screen is needed to display alternate information
void maintainStateRefresh(const std::vector<fileInfoStruct>& fileNames);


//refresh command when directiory changes
void dirBackRefresh(const std::vector<fileInfoStruct>& fileNames);

//erases file info ON THE SCREEN so shorter dir can be displayed
void clearFileInfo(const int& size);

//templated function for printing data to screen
template <typename T> void sendData(const T out, const xy& pos= {1000,1000}, const std::string& function = "0");
//function 0 - regular | cs - clearScreen


//can be used to preform actions before the program exits
void onQuit();

#endif //DRAWLAYOUT_H
