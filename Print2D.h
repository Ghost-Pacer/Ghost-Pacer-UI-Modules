#ifndef __PRINT2D_H_
#define __PRINT2D_H_

#include <vector>
#include "OGLES2Tools.h"

using std::vector;

class Print2D {
public:
    // Stores text with color and scale attributes
    struct AttributedText {
        char *text;
        float scale;
        unsigned int color;
    };

    // Print2D Constructor
    Print2D(CPVRTPrint3D *print3D, bool isScreenRotated);

    // Renders text with top left coordinate of bounding box at (xRelativePosition, yRelativePosition)
    // xRelativePosition and yRelativePosition need to be between 0-100 inclusive
    void renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);

    // Renders text with center coordinate of bounding box at (xRelativePosition, yRelativePosition)
    // xRelativePosition and yRelativePosition need to be between 0-100 inclusive
    void renderTextCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);

    // Renders vertical list of text with top left coordinate of bounding box at (xAbsolutePosition, yAbsolutePosition)
    void renderVerticalMenuAbsoluteOriginAt(float xAbsolutePosition, float yAbsolutePosition, float scale, unsigned int color, int spacing, vector<char*> menuItemsText);

    // Renders vertical list of text with center coordinate of the list's bounding box at (xRelativePosition, yRelativePosition)
    // xRelativePosition and yRelative Position need to be between 0-100 inclusive
    void renderVerticalMenuCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, int spacing, vector<char*> menuItemsText);

    // Renders vertical list of text with center coordinate of the list's bounding box at (xRelativePosition, yRelativePosition)
    // xRelativePosition and yRelative Position need to be between 0-100 inclusive
    void renderVerticalMenuCenteredAt(float xRelativePosition, float yRelativePosition, int spacing, vector<AttributedText> menuItemsAttributedText);

    // Gets screen width
    float getScreenWidth();

    // Gets screen height
    float getScreenHeight();
    
private:
    struct Coordinate {
        float x;
        float y;
    };

    struct MenuItem {
        Print2D::AttributedText attributedText;
        Print2D::Coordinate coordinate;
    };

    CPVRTPrint3D *print3D;
    unsigned int screenWidth;
    unsigned int screenHeight;

    void setMenuItemsSpacing(vector<MenuItem> &menuItems, int spacing);
    void justifyMenuItems(vector<MenuItem> &menuItems);
    Coordinate calculateMenuOriginAbsoluteCoordinate(float xCenterRelativePosition, float yCenterRelativePosition, int spacing, vector<MenuItem> menuItems);
    void offsetMenuItemsBy(Coordinate offset, vector<MenuItem> &menuItems);
    void convertMenuItemPositionsFromAbsoluteToRelative(vector<MenuItem> &menuItems);
    void renderMenuItems(vector<MenuItem> menuItems);
    float calculateMaxTextWidth(vector<MenuItem> menuItems);
    float calculateTotalTextHeight(vector<MenuItem> menuItems, int spacing);

    Coordinate convertCenterRelativeToOriginRelative(Coordinate centerRelativeCoordinate, char *text, float scale);
    Coordinate convertCenterAbsoluteToOriginAbsolute(Coordinate centerAbsoluteCoordiate, char *text, float scale);
    float convertRelativeToAbsolutePosition(float relativePosition, float pixels);
    float convertAbsoluteToRelativePosition(float absolutePosition, float pixels);
};

#endif