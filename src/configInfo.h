//
// Created by vjgti on 5/7/2024.
//

#ifndef CONFIGINFO_H
#define CONFIGINFO_H


struct configData {
    std::string name;
    std::string subClass;
    std::string value;
};

//reads in config options from TFV_config.txt
void readUserConfig();

//sets the user config option in the program
void setUserConfig(std::string setting, std::string data);

//writes the provided config info to the file
//only works if the option is already in the file
void writeUserConfig(std::string& command);

//sets the config setting while the progrom is running
//does NOT write to file - ends affect after program ends
void tempUserConfig(std::string& command);

//write config file with default config options
void createUserConfig(const std::string& command);

//gets specific config line subclass, name(redundant since passed in), and value
configData getConfigLine(std::string str);
#endif //READCONFIG_H
