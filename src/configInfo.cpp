//
// Created by vjgti on 5/7/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "configInfo.h"

#include <string>
#include <unordered_map>

#include "commands.h"
#include "drawLayout.h"

void setUserConfig(std::string setting, std::string data) {
    std::unordered_map<std::string, int> convToInt;
    convToInt = {
        {"rc-pt", 0},
        {"rc-vd", 1},
        {"rc-hd", 2},
        {"rc-tc", 3},
        {"rc-bc", 4},
        {"rc-ac", 5},
        {"nameV", 6},
        {"extentionV", 7},
        {"sizeV", 8},
        {"modV", 9},
        {"createV", 10},
        {"kc-up", 11},
        {"kc-down", 12},
        {"kc-quit", 13},
        {"kc-refresh", 14},
        {"kc-maintainRefresh", 15},
        {"kc-clear", 16},
        {"kc-enterFolder", 17},
        {"kc-enterPar", 18},
        {"rc-cl", 19},
        {"rc-cr", 20},
        {"ac-debug", 21},
        {"ac-config", 22},
        {"ac-sdd", 23},
        {"ac-dss", 24},

        {"kc-search", 25},
        {"kc-github", 26},
        {"LicenseKey", 27}
    };


    switch (convToInt[setting]) {
        //start render codes
        case 0:
            renderCodes.pointer = char(std::stoi(data));
            break;
        case 1:
            renderCodes.divVert  = char(std::stoi(data));
            break;
        case 2:
            renderCodes.divHori  = char(std::stoi(data));
            break;
        case 3:
            renderCodes.topCombine  = char(std::stoi(data));
            break;
        case 4:
            renderCodes.bottomCombine  = char(std::stoi(data));
            break;
        case 5:
            renderCodes.allcombine  = char(std::stoi(data));
            break;
        case 19:
            renderCodes.cmdLcursor = char(std::stoi(data));
            break;
        case 20:
            renderCodes.cmdRcursor = char(std::stoi(data));
            break;
        //end render codes

        //start view options
        case 6:
            nameView.active = true;
            nameView.size = std::stoi(data.substr(2));
            break;
        case 7:
            extentionView.active = std::stoi(data.substr(0,1));
            extentionView.size = std::stoi(data.substr(2));
            break;
        case 8:
            sizeView.active = std::stoi(data.substr(0,1));
            sizeView.size = std::stoi(data.substr(2));
            break;
        case 9:
            modifiedView.active = std::stoi(data.substr(0,1));
            modifiedView.size = std::stoi(data.substr(2));
            break;
        case 10:
            createdView.active = std::stoi(data.substr(0,1));
            createdView.size = std::stoi(data.substr(2));
            break;
        //end view options

        //start key press codes
        case 11:
            keyPressCodes.up = char(stoi(data));
            break;
        case 12:
            keyPressCodes.down = char(stoi(data));
            break;
        case 13:
            keyPressCodes.quit = char(stoi(data));
            break;
        case 14:
            keyPressCodes.refresh = char(stoi(data));
            break;
        case 15:
            keyPressCodes.maintainStateRefresh = char(stoi(data));
            break;
        case 16:
            keyPressCodes.clear = char(stoi(data));
            break;
        case 17:
            keyPressCodes.enterCurrFolder = char(stoi(data));
            break;
        case 18:
            keyPressCodes.enterParFolder = char(stoi(data));
            break;
        //end key press codes

        //start advanced codes
        case 21:
            advancedCodes.debugMode = std::stoi(data);
            break;
        case 22:
            advancedCodes.disableConfigLoad = std::stoi(data);
            break;
        case 23:
            advancedCodes.debugModeScreenDisplay = std::stoi(data);
            break;
        case 24:
            advancedCodes.defaultSearchPattern = data;
            break;

        //TODO: probably should be put with the keypress codes, but that would require redoing the numbers and i dont want to break anything right now
        case 25:
            keyPressCodes.search = char(stoi(data));
            break;
        case 26:
            keyPressCodes.github = char(stoi(data));
            break;
        case 27:
            advancedCodes.licenseKey = data;
            break;
        //end advanced codes
        default:
            break;
    }
}

void readUserConfig() {
    if (advancedCodes.disableConfigLoad == true) {return;}
    std::fstream configFile;
    configFile.open("TFV_config.txt");
    if (configFile.is_open() == true) {
        std::string lineData;
        while(std::getline(configFile, lineData)) {
            if(lineData[0] == '1' || lineData[0] == '2' || lineData[0] == '3' || lineData[0] == '4'){
                //debugOutput("user data: " + lineData.substr(2, lineData.find(']')-2) + " " + lineData.substr(lineData.find('(')+1, lineData.find(')')-1), -16);
                //system("PAUSE");
                setUserConfig(lineData.substr(2, lineData.find(']')-2), lineData.substr(lineData.find('(')+1, lineData.find(')')-lineData.find('(')-1));
            } else if (lineData[0] == '*') {
                setUserConfig(lineData.substr(2, lineData.find(']')-2), lineData.substr(lineData.find('(')+1, lineData.find(')')-lineData.find('(')-1));
                if (lineData.substr(2, lineData.find(']')-2) == "ac-config" && lineData.substr(lineData.find('(')+1, lineData.find(')')-lineData.find('(')-1) == "1") {
                    break;
                }
            }
        }
    }
}


void writeUserConfig(std::string& command) {
    std::string option = command.substr(command.find(' ') + 1);
    std::string setting = option.substr(option.find(' ')+1);
    option = option.substr(0, option.find(' '));
    std::fstream configFile;
    configFile.open("TFV_config.txt");
    std::vector<std::string> lineData;
    std::string tempData;
    if (configFile.is_open() == true) {
        while (std::getline(configFile, tempData)) {
            lineData.push_back(tempData);
        }
    }
    configFile.close();
    std::string beforeInput = "";
    std::string afterInput = "";
    for(int i = 0; i < lineData.size(); ++i) {
        if ('['+option+']'==lineData[i].substr(1, lineData[i].find(']')) && lineData[i][0] != '#') {
            beforeInput = lineData[i].substr(0,lineData[i].find('(')+1);
            afterInput = lineData[i].substr(lineData[i].find(')'));
            lineData[i] = beforeInput + setting + afterInput;
        }
    }
    std::ofstream configFileOut("TFV_config.txt");
    for(std::string t : lineData) {
        //std::cout << t << std::endl;
        configFileOut << t << std::endl;
    }
    //configFileOut << option << "," << setting;
    configFileOut.close();
    refreshConfig();
}

void tempUserConfig(std::string& command) {
    std::string option = command.substr(command.find(' ') + 1);
    std::string setting = option.substr(option.find(' ')+1);
    option = option.substr(0, option.find(' '));
    setUserConfig(option, setting);
    refreshScreen(fileInformation);
}



void createUserConfig(const std::string& command) {
    struct stat buffer;
    std::string commandName = "initConfig";
    std::string name = "TFV_config.txt";
    bool override = false;
    if (command.length() == commandName.length()) {override = false;}
    else {
        if(command.find("--override") != std::string::npos) {
            override = true;
        }
    }

    bool exists = (stat(name.c_str(), &buffer) == 0);
    if (exists == true && override == false) {displayError("already exits - use --override to rewrite");return;}
    struct temp_template {
        std::string name;
        std::string option;
    };
    std::vector<temp_template> config {
    {"1[rc-vd]", "179"},
    {"1[rc-hd]", "196"},
    {"1[rc-tc]", "194"},
    {"1[rc-bc]", "193"},
    {"1[rc-ac]", "197"},
    {"1[rc-pt]", "62"},
    {"1[rc-cl]", "217"},
    {"1[rc-cr]", "192"},

    {"2[nameV]", "1|20"},
    {"2[extentionV]", "1|5"},
    {"2[sizeV]", "1|8"},
    {"2[modV]", "1|14"},
    {"2[createV]", "1|14"},

    {"3[kc-up]", "116"},
    {"3[kc-down]", "104"},
    {"3[kc-quit]", "113"},
    {"3[kc-refresh]", "114"},
    {"3[kc-maintainRefresh]", "82"},
    {"3[kc-clear]", "99"},
    {"3[kc-enterFolder]", "115"},
    {"3[kc-enterPar]", "97"},
    {"3[kc-search]", "103"},
    {"3[kc-search]", "102"},

    {"4[ac-debug]", "0"},
    {"*[ac-config]", "0"},
    {"4[ac-sdd]", "0"},
    {"4[ac-dss]", "regular"},

    {"![LicenseKey]", "_____"}
    };

    std::ofstream file;
    file.open(name);
    for (temp_template t : config) {
        file << t.name << "(" << t.option << ")" << std::endl;
    }
    file.close();
    return;
}


configData getConfigLine(std::string str) {
    configData config_data = {"","",""};
    config_data.name = "ERROR_NOT_VALID_FILE_LOAD_DISABLED";
    if (advancedCodes.disableConfigLoad == true) {return config_data;}
    std::fstream configFile;
    configFile.open("TFV_config.txt");
    if (configFile.is_open() == true) {
        std::string lineData;
        while(std::getline(configFile, lineData)) {
            //debugOutput("user data: " + lineData.substr(2, lineData.find(']')-2) + " " + lineData.substr(lineData.find('(')+1, lineData.find(')')-1), -16);
            //system("PAUSE");
            if(lineData.substr(2, lineData.find(']')-2) == str) {
                config_data.subClass = lineData[0];
                config_data.name = lineData.substr(2, lineData.find(']')-2);
                config_data.value = lineData.substr(lineData.find('(')+1, lineData.find(')')-lineData.find('(')-1);
                return config_data;
            }
        }
        config_data.name = "ERROR_NOT_FOUND_IN_FILE";
        return config_data;
    }
    config_data.name = "ERROR_FILE_OPEN_FAILED";
    return config_data;
}


