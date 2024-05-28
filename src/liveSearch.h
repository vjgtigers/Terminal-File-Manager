//
// Created by vjgti on 5/21/2024.
//

#ifndef LIVESEARCH_H
#define LIVESEARCH_H
#include "drawLayout.h"

//the main function that is called when the livesearch window is displayed
void liveSearch(std::vector<fileInfoStruct> files, std::string command = "");

//draw backgroud for searchpage
void lsBaseLayout(std::string& searchPattern);

//check through the list of files for "matches" given a string and search mode - not implemented yet
void lsSearch(std::string& sString);

//draw the current typing string (modified from commandline)
void lsDrawCommand(std::string currCommand, xy wd);

//if enter is pressed open file that is at the top - not implemented yet
void lsCall(std::string& sString, std::vector<fileInfoStruct>& files);

//main running loop in the liveSearch function
void lsCmdMain(std::vector<fileInfoStruct>& files);
#endif //LIVESEARCH_H
