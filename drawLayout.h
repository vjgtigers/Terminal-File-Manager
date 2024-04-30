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
typedef struct xy;

typedef struct fileInfoStruct;
//used to draw the base outline of the main file view screen
void drawBaseLayout();

//draws selection pointer
void drawSelectionPointer(xy xy_cursor);


//can be used to clear the entire screen and redraw
//helpful if viewing window gets messed up on resize
void refreshScreen(const std::vector<fileInfoStruct>& fileNames);




struct fileInfoStruct {
    std::string name;
    std::string extention;
    std::string size;
    std::string modDate;
    std::string createDate;
};
extern std::vector<fileInfoStruct> fileInformation;




void displayFileInfo(const std::vector<fileInfoStruct>& fileNames);



#endif //DRAWLAYOUT_H
