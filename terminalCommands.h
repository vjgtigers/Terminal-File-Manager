//
// Created by vjgti on 4/27/2024.
//

#ifndef TERMINALCOMMANDS_H
#define TERMINALCOMMANDS_H

//sets cursor position, top left being 0,0
void setCursorPosition(int x, int y);

//used to enable virtule terminal process
//allows to return to previous screen when program is done
//DOES NOT ACTIVATE IT
bool EnableVTMode();

//toggle between virtule terminal and regular terminal
void toggleVT(bool toggle);

//clear terminal screen TODO: make better
void clearScreen();

#endif //TERMINALCOMMANDS_H
