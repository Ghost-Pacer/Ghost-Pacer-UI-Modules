#ifndef __BUTTON_LEGEND_CONTROLLER_H_
#define __BUTTON_LEGEND_CONTROLLER_H_

#include "Print2D.h"

class ButtonLegendController {
public:
    // ButtonLegendController Constructor
    ButtonLegendController(int spacing, CPVRTPrint3D *print3D);

    // ButtonLegendController Destructor
    ~ButtonLegendController();

    // Renders button legend on screen
    void render();

    // Sets the button at the given index with either its
    // selected or deselected color
    void setButtonIsEnabled(int buttonIndex, bool enabled);
private:
    const char *UP_BUTTON = "~";
    const char *DOWN_BUTTON = "`";
    const char *OK_BUTTON = "\\";
    const unsigned int UP_BUTTON_SELECTED_COLOR = 0xFFFF0000;
    const unsigned int DOWN_BUTTON_SELECTED_COLOR = 0xFFFF0000;
    const unsigned int OK_BUTTON_SELECTED_COLOR = 0xFF00FF00;
    const unsigned int UNSELECTED_COLOR = 0x99999999;
    const float SCALE = 0.9;
    const float X_RELATIVE_CENTER_COORDINATE = 90.0;
    const float Y_RELATIVE_CENTER_COORDINATE = 88.0;

    vector<Print2D::AttributedText> legendItemsAttributedText;
    int itemSpacing;
    Print2D *print2D;

    char* stringRepresentationOfButton(int buttonIndex);
    unsigned int selectedColorOfButton(int buttonIndex);
};

#endif