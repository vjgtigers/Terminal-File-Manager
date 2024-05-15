//
// Created by vjgti on 5/7/2024.
//

#ifndef CONFIGINFO_H
#define CONFIGINFO_H


void readUserConfig();
void setUserConfig(std::string setting, std::string data);

//writes the provided config info to the file
//only works if the option is already in the file
void writeUserConfig(std::string& command);

//sets the config setting while the progrom is running
//does NOT write to file - ends affect after program ends
void tempUserConfig(std::string& command);
#endif //READCONFIG_H
