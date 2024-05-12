//
// Created by vjgti on 5/7/2024.
//

#ifndef CONFIGINFO_H
#define CONFIGINFO_H


void readUserConfig();
void setUserConfig(std::string setting, std::string data);


void writeUserConfig(std::string& command);

void tempUserConfig(std::string& command);
#endif //READCONFIG_H
