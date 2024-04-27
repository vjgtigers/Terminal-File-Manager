//
// Created by vjgti on 4/27/2024.
//

#ifndef DRAWLAYOUT_H
#define DRAWLAYOUT_H


struct fd_display_data {
    bool active;
    int size;
};

extern struct fd_display_data nameView;
extern struct fd_display_data extentionView;
extern struct fd_display_data sizeView;
extern struct fd_display_data typeView;
extern struct fd_display_data modifiedView;
extern struct fd_display_data createdView;

//used to draw the base outline of the main file view screen
void drawBaseLayout();












#endif //DRAWLAYOUT_H
