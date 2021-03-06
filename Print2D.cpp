#include "Print2D.h"

/**
 * DOES: Creates new instance of Print2D class
 * PARAMS: print3D - Pointer to an already set up CPVRTPrint3D object
 * RETURNS: Print2D instance
 * THROWS: None
 */
Print2D::Print2D(CPVRTPrint3D *print3D, bool isScreenRotated) {
    this->print3D = print3D;
    if (isScreenRotated) {
        print3D->GetAspectRatio(&this->screenHeight, &this->screenWidth);
    } else {
        print3D->GetAspectRatio(&this->screenWidth, &this->screenHeight);
    }
}

/**
 * DOES: Renders text with top left coordinate of bounding box at (xRelativePosition, yRelativePosition)
 * PARAMS: xRelativePosition - Horizontal position of text, can be between 0 and 100 inclusive
 *         yRelativePosition - Vertical position of text, can be between 0 and 100 inclusive
 *         scale - Size of text, 1 corresponds to 100% size
 *         color - Color of text
 *         text - Text to display
 * RETURNS: None
 * THROWS: None
 */
void Print2D::renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text) {
    print3D->Print3D(xRelativePosition, yRelativePosition, scale, color, text);
}

/**
 * DOES: Renders text with center coordinate of bounding box at (xRelativePosition, yRelativePosition)
 * PARAMS: xRelativePosition - Horizontal position of text, can be between 0 and 100 inclusive
 *         yRelativePosition - Vertical position of text, can be between 0 and 100 inclusive
 *         scale - Size of text, 1 corresponds to 100% size
 *         color - Color of text
 *         text - Text to display
 * RETURNS: None
 * THROWS: None
 */
void Print2D::renderTextCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text) {
    Coordinate centerRelativePosition;
    centerRelativePosition.x = xRelativePosition;
    centerRelativePosition.y = yRelativePosition;

    Coordinate originRelativeCoordinate = convertCenterRelativeToOriginRelative(centerRelativePosition, text, scale);
    renderText(originRelativeCoordinate.x, originRelativeCoordinate.y, scale, color, text);
}

/**
 * DOES: Renders vertical list of text with top left coordinate of bounding box at (xAbsolutePosition, yAbsolutePosition)
 * PARAMS: xAbsolutePosition - Horizontal position of text in pixels
 *         yAbsolutePosition - Vertical position of text in pixels
 *         scale - Size of text, 1 corresponds to 100% size
 *         color - Color of text
 *         spacing - Spacing between list items
 *         menuItemsText - Vector of text to display, first element displayed on top
 * RETURNS: None
 * THROWS: None
 */
void Print2D::renderVerticalMenuAbsoluteOriginAt(float xAbsolutePosition, float yAbsolutePosition, float scale, unsigned int color, int spacing, vector<char*> menuItemsText) {
    vector<MenuItem> menuItems;
    int size = menuItemsText.size();
    for (int ii = 0; ii < size; ii++) {
        AttributedText attributedText;
        attributedText.text = menuItemsText[ii];
        attributedText.color = color;
        attributedText.scale = scale;

        Coordinate initialAbsolutePosition;
        initialAbsolutePosition.x = 0;
        initialAbsolutePosition.y = 0;

        MenuItem menuItem;
        menuItem.attributedText = attributedText;
        menuItem.coordinate = initialAbsolutePosition;

        menuItems.push_back(menuItem);
    }

    Coordinate originAbsoluteCoordinate;
    originAbsoluteCoordinate.x = xAbsolutePosition;
    originAbsoluteCoordinate.y = yAbsolutePosition;

    setMenuItemsSpacing(menuItems, spacing);
    justifyMenuItems(menuItems);
    offsetMenuItemsBy(originAbsoluteCoordinate, menuItems);
    convertMenuItemPositionsFromAbsoluteToRelative(menuItems);
    renderMenuItems(menuItems);
}

/**
 * DOES: Renders vertical list of text with center coordinate of bounding box at (xRelativePosition, yRelativePosition)
 * PARAMS: xRelativePosition - Horizontal position of text, can be between 0 and 100 inclusive
 *         yRelativePosition - Vertical position of text, can be between 0 and 100 inclusive
 *         scale - Size of text, 1 corresponds to 100% size
 *         color - Color of text
 *         spacing - Spacing between list items
 *         menuItemsText - Vector of text to display, first element displayed on top
 * RETURNS: None
 * THROWS: None
 */
void Print2D::renderVerticalMenuCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, int spacing, vector<char*> menuItemsText) {	
    vector<MenuItem> menuItems;
    int size = menuItemsText.size();
    for (int ii = 0; ii < size; ii++) {
        AttributedText attributedText;
        attributedText.text = menuItemsText[ii];
        attributedText.color = color;
        attributedText.scale = scale;

        Coordinate initialAbsolutePosition;
        initialAbsolutePosition.x = 0;
        initialAbsolutePosition.y = 0;

        MenuItem menuItem;
        menuItem.attributedText = attributedText;
        menuItem.coordinate = initialAbsolutePosition;

        menuItems.push_back(menuItem);
    }

    setMenuItemsSpacing(menuItems, spacing);
    justifyMenuItems(menuItems);
    Coordinate originAbsoluteCoordinate = calculateMenuOriginAbsoluteCoordinate(xRelativePosition, yRelativePosition, spacing, menuItems);
    offsetMenuItemsBy(originAbsoluteCoordinate, menuItems);
    convertMenuItemPositionsFromAbsoluteToRelative(menuItems);
    renderMenuItems(menuItems);
}

/**
 * DOES: Renders vertical list of text with center coordinate of bounding box at (xRelativePosition, yRelativePosition)
 * PARAMS: xRelativePosition - Horizontal position of text, can be between 0 and 100 inclusive
 *         yRelativePosition - Vertical position of text, can be between 0 and 100 inclusive
 *         spacing - Spacing between list items
 *         menuItemsText - Vector of AttributedText to display, first element displayed on top
 * RETURNS: None
 * THROWS: None
 */
void Print2D::renderVerticalMenuCenteredAt(float xRelativePosition, float yRelativePosition, int spacing, vector<AttributedText> menuItemsAttributedText) {
    vector<MenuItem> menuItems;
    int size = menuItemsAttributedText.size();
    for (int ii = 0; ii < size; ii++) {
        Coordinate initialAbsolutePosition;
        initialAbsolutePosition.x = 0;
        initialAbsolutePosition.y = 0;
        
        MenuItem menuItem;
        menuItem.attributedText = menuItemsAttributedText[ii];
        menuItem.coordinate = initialAbsolutePosition;

        menuItems.push_back(menuItem);
    }

    setMenuItemsSpacing(menuItems, spacing);
    justifyMenuItems(menuItems);
    Coordinate originAbsoluteCoordinate = calculateMenuOriginAbsoluteCoordinate(xRelativePosition, yRelativePosition, spacing, menuItems);
    offsetMenuItemsBy(originAbsoluteCoordinate, menuItems);
    convertMenuItemPositionsFromAbsoluteToRelative(menuItems);
    renderMenuItems(menuItems);
}

/**
 * DOES: Gets width of screen
 * PARAMS: None
 * RETURNS: Width of screen
 * THROWS: None
 */
float Print2D::getScreenWidth() {
    return screenWidth;
}

/**
 * DOES: Gets height of screen
 * PARAMS: None
 * RETURNS: Height of screen
 * THROWS: None
 */
float Print2D::getScreenHeight() {
    return screenHeight;
}

// ***** HELPER FUNCTIONS *****

/**
 * DOES: Updates y-coordinate of each menu item to vertically space them evenly.
 *       Assumes the y-coordinates of each menu item are the same when function is called.
 * PARAMS: menuItems - Reference to MenuItems to update y-coordinates of
 *         spacing - Vertical spacing between each MenuItem
 * RETURNS: None
 * THROWS: None
 */
void Print2D::setMenuItemsSpacing(vector<MenuItem> &menuItems, int spacing) {
    int size = menuItems.size();
    float yOffset = 0;
    for (int ii = 0; ii < size; ii++) {
        menuItems[ii].coordinate.y = yOffset;

        char *menuItemText = menuItems[ii].attributedText.text;
        float menuItemScale = menuItems[ii].attributedText.scale;
        float textWidth;
        float textHeight;
        print3D->MeasureText(&textWidth, &textHeight, menuItemScale, menuItemText);

        yOffset += textHeight + spacing;
    }
}

/**
 * DOES: Centers menu items within its bounding box such that the 
 *       center x-coordinate of each menu item is equal to the center x-coordinate
 *       of the longest width menu item.
 * PARAMS: menuItems - Reference to MenuItems to update x-coordinates of
 * RETURNS: None
 * THROWS: None
 */
void Print2D::justifyMenuItems(vector<MenuItem> &menuItems) {
    float maxTextWidth = calculateMaxTextWidth(menuItems);

    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        char *menuItemText = menuItems[ii].attributedText.text;
        float menuItemScale = menuItems[ii].attributedText.scale;
        float textWidth;
        float textHeight;
        print3D->MeasureText(&textWidth, &textHeight, menuItemScale, menuItemText);

        float widthDifference = maxTextWidth - textWidth;
        if (widthDifference > 0) {
            menuItems[ii].coordinate.x += widthDifference / 2;
        }
    }
}

/**
 * DOES: Converts the given relative, center coordinate of a menu to an
 *       absolute, origin coordinate.
 * PARAMS: xCenterRelativePosition - Horizontal position of menu center, can be between 0-100 inclusive
 *         yCenterRelativePosition - Vertical position of menu center, can be between 0-100 inclusive
 *         spacing - Spacing between menu items
 *         menuItems - MenuItems to calculate absolute origin coordinate for
 * RETURNS: Absolute, origin coordinate of menu
 * THROWS: None
 */
Print2D::Coordinate Print2D::calculateMenuOriginAbsoluteCoordinate(float xCenterRelativePosition, float yCenterRelativePosition, int spacing, vector<MenuItem> menuItems) {
    float maxTextWidth = calculateMaxTextWidth(menuItems);
    float totalTextHeight = calculateTotalTextHeight(menuItems, spacing);

    Coordinate centerAbsoluteCoordinate;
    centerAbsoluteCoordinate.x = convertRelativeToAbsolutePosition(xCenterRelativePosition, (float) screenWidth);
    centerAbsoluteCoordinate.y = convertRelativeToAbsolutePosition(yCenterRelativePosition, (float) screenHeight);

    Coordinate originAbsoluteCoordinate;
    originAbsoluteCoordinate.x = centerAbsoluteCoordinate.x - maxTextWidth / 2;
    originAbsoluteCoordinate.y = centerAbsoluteCoordinate.y - totalTextHeight / 2;

    return originAbsoluteCoordinate;
}

/**
 * DOES: Offets the coordinate of each given menu item by the given offset amount.
 * PARAMS: offset - How much to offset menu item positions by
 *         menuItems - Reference to MenuItems to offset positions of
 * RETURNS: None
 * THROWS: None
 */
void Print2D::offsetMenuItemsBy(Coordinate offset, vector<MenuItem> &menuItems) {
    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        menuItems[ii].coordinate.x += offset.x;
        menuItems[ii].coordinate.y += offset.y;
    }
}

/**
 * DOES: Coverts coordinate of each menu item from an absolute coordinate to
 *       a relative coordinate. Assumes that each menu item coordinate is a
 *       valid absolute coordinate before function is called.
 * PARAMS: menuItems - Reference to MenuItems to convert coordinates for
 * RETURNS: None
 * THROWS: None
 */
void Print2D::convertMenuItemPositionsFromAbsoluteToRelative(vector<MenuItem> &menuItems) {
    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        menuItems[ii].coordinate.x = convertAbsoluteToRelativePosition(menuItems[ii].coordinate.x, (float) screenWidth);
        menuItems[ii].coordinate.y = convertAbsoluteToRelativePosition(menuItems[ii].coordinate.y, (float) screenHeight);
    }
}
/**
 * DOES: Renders a list of menu items. Assumes that the coordinates of each menu
 *       item are relative, origin coordinates.
 * PARAMS: menuItems - MenuItems to render
 * RETURNS: None
 * THROWS: None
 */
void Print2D::renderMenuItems(vector<MenuItem> menuItems) {
    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        AttributedText attributedText = menuItems[ii].attributedText;
        Coordinate coordinate = menuItems[ii].coordinate;
        renderText(coordinate.x, coordinate.y, attributedText.scale, attributedText.color, attributedText.text);
    }
}

/**
 * DOES: Reports the width of the longest menu item from the given menu items
 * PARAMS: menuItems - MenuItems to calculate max text width from
 * RETURNS: The width of the longest menu item found
 * THROWS: None
 */
float Print2D::calculateMaxTextWidth(vector<MenuItem> menuItems) {
    int size = menuItems.size();
    float maxTextWidth = 0;
    for (int ii = 0; ii < size; ii++) {
        char *menuItemText = menuItems[ii].attributedText.text;
        float menuItemScale = menuItems[ii].attributedText.scale;
        float textWidth;
        float textHeight;
        print3D->MeasureText(&textWidth, &textHeight, menuItemScale, menuItemText);

        if (textWidth > maxTextWidth) { maxTextWidth = textWidth; }
    }

    return maxTextWidth;
}

/**
 * DOES: Reports the total height of the menu, with spacing between 
 *       items taken into account
 * PARAMS: menuItems - MenuItems to measure total height of
 *         spacing - Spacing between menu items
 * RETURNS: Total height of menu
 * THROWS: None
 */
float Print2D::calculateTotalTextHeight(vector<MenuItem> menuItems, int spacing) {
    int size = menuItems.size();

    // The total number of spaces added should be totalMenuItems - 1
    float totalTextHeight = (float) -spacing;
    for (int ii = 0; ii < size; ii++) {
        char *menuItemText = menuItems[ii].attributedText.text;
        float menuItemScale = menuItems[ii].attributedText.scale;
        float textWidth;
        float textHeight;
        print3D->MeasureText(&textWidth, &textHeight, menuItemScale, menuItemText);
        
        totalTextHeight += textHeight + (float) spacing;
    }

    return totalTextHeight;
}

/**
 * DOES: Converts relative, center coordinate to a relative, origin coordinate
 * PARAMS: centerRelativeCoordinate - Coordinate to convert
 *         text - Text that the given centerRelativeCoordinate corresponds to
 *         scale - Size of text
 * RETURNS: Relative, origin coordinate of given text
 * THROWS: None
 */
Print2D::Coordinate Print2D::convertCenterRelativeToOriginRelative(Print2D::Coordinate centerRelativeCoordinate, char* text, float scale) {
    Coordinate centerAbsoluteCoordinate;
    centerAbsoluteCoordinate.x = convertRelativeToAbsolutePosition(centerRelativeCoordinate.x, (float) screenWidth);
    centerAbsoluteCoordinate.y = convertRelativeToAbsolutePosition(centerRelativeCoordinate.y, (float) screenHeight);

    Coordinate originAbsoluteCoordinate = convertCenterAbsoluteToOriginAbsolute(centerAbsoluteCoordinate, text, scale);

    Coordinate originRelativeCoordinate;
    originRelativeCoordinate.x = convertAbsoluteToRelativePosition(originAbsoluteCoordinate.x, (float) screenWidth);
    originRelativeCoordinate.y = convertAbsoluteToRelativePosition(originAbsoluteCoordinate.y, (float) screenHeight);

    return originRelativeCoordinate;
}

/**
 * DOES: Converts absolute, center coordinate to an absolute, origin coordinate
 * PARAMS: centerAbsoluteCoordinate - Coordinate to convert
 *         text - Text that the given centerAbsoluteCoordinate corresponds to
 *         scale - Size of text
 * RETURNS: Absolute, origin coordinate of given text
 * THROWS: None
 */
Print2D::Coordinate Print2D::convertCenterAbsoluteToOriginAbsolute(Print2D::Coordinate centerAbsoluteCoordinate, char* text, float scale) {
    float textWidth;
    float textHeight;
    print3D->MeasureText(&textWidth, &textHeight, scale, text);

    Coordinate originAbsoluteCoordinate;
    originAbsoluteCoordinate.x = centerAbsoluteCoordinate.x - textWidth / 2;
    originAbsoluteCoordinate.y = centerAbsoluteCoordinate.y - textHeight / 2;

    return originAbsoluteCoordinate;
}

/**
 * DOES: Converts a relative position to an absolute position
 * PARAMS: relativePosition - Relative position to convert, can be between 0-100 inclusive
 *          pixels - Number of pixels corresponding to relative position 100
 * RETURNS: Absolute position
 * THROWS: None
 */
float Print2D::convertRelativeToAbsolutePosition(float relativePosition, float pixels) {
    return pixels * relativePosition / 100;
}

/**
 * DOES: Converts an absolute position to a relative position
 * PARAMS: absolutePosition - Absolute position to convert
 *         pixels - Number of pixels corresponding to relative position 100
 * RETURNS: Relative position
 * THROWS: None
 */
float Print2D::convertAbsoluteToRelativePosition(float absolutePosition, float pixels) {
    return absolutePosition / pixels * 100;
}