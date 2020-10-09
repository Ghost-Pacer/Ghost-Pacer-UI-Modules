#include "Print2D.h"

Print2D::Print2D(CPVRTPrint3D *print3D) {
	this->print3D = print3D;
	print3D->GetAspectRatio(&this->screenWidth, &this->screenHeight);
}

void Print2D::renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text) {
	print3D->Print3D(xRelativePosition, yRelativePosition, scale, color, text);
}

void Print2D::renderTextCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text) {
	Coordinate centerRelativePosition;
	centerRelativePosition.x = xRelativePosition;
	centerRelativePosition.y = yRelativePosition;

	Coordinate originRelativeCoordinate = convertCenterRelativeToOriginRelative(centerRelativePosition, text, scale);
	renderText(originRelativeCoordinate.x, originRelativeCoordinate.y, scale, color, text);
}

void Print2D::renderVerticalMenuCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, int spacing, vector<char*> menuItemsText) {	
	vector<MenuItem> menuItems;
	for (int ii = 0; ii < menuItemsText.size(); ii++) {
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



// HELPER FUNCTIONS
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

Print2D::Coordinate Print2D::calculateMenuOriginAbsoluteCoordinate(float xCenterRelativePosition, float yCenterRelativePosition, int spacing, vector<MenuItem> menuItems) {
    float maxTextWidth = calculateMaxTextWidth(menuItems);
    float totalTextHeight = calculateTotalTextHeight(menuItems, spacing);

    Coordinate centerAbsoluteCoordinate;
	centerAbsoluteCoordinate.x = convertRelativeToAbsolutePosition(xCenterRelativePosition, screenWidth);
	centerAbsoluteCoordinate.y = convertRelativeToAbsolutePosition(yCenterRelativePosition, screenHeight);

	Coordinate originAbsoluteCoordinate;
	originAbsoluteCoordinate.x = centerAbsoluteCoordinate.x - maxTextWidth / 2;
	originAbsoluteCoordinate.y = centerAbsoluteCoordinate.y - totalTextHeight / 2;

    return originAbsoluteCoordinate;
}

void Print2D::offsetMenuItemsBy(Coordinate offset, vector<MenuItem> &menuItems) {
    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        menuItems[ii].coordinate.x += offset.x;
		menuItems[ii].coordinate.y += offset.y;
    }
}

void Print2D::convertMenuItemPositionsFromAbsoluteToRelative(vector<MenuItem> &menuItems) {
    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        menuItems[ii].coordinate.x = convertAbsoluteToRelativePosition(menuItems[ii].coordinate.x, screenWidth);
        menuItems[ii].coordinate.y = convertAbsoluteToRelativePosition(menuItems[ii].coordinate.y, screenHeight);
    }
}

void Print2D::renderMenuItems(vector<MenuItem> menuItems) {
    int size = menuItems.size();
    for (int ii = 0; ii < size; ii++) {
        AttributedText attributedText = menuItems[ii].attributedText;
        Coordinate coordinate = menuItems[ii].coordinate;
        renderText(coordinate.x, coordinate.y, attributedText.scale, attributedText.color, attributedText.text);
    }
}

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

float Print2D::calculateTotalTextHeight(vector<MenuItem> menuItems, int spacing) {
    int size = menuItems.size();

    // The total number of spaces added should be totalMenuItems - 1
    float totalTextHeight = -spacing;
    for (int ii = 0; ii < size; ii++) {
        char *menuItemText = menuItems[ii].attributedText.text;
        float menuItemScale = menuItems[ii].attributedText.scale;
        float textWidth;
        float textHeight;
		print3D->MeasureText(&textWidth, &textHeight, menuItemScale, menuItemText);
        
        totalTextHeight += textHeight + spacing;
    }

    return totalTextHeight;
}


Print2D::Coordinate Print2D::convertCenterRelativeToOriginRelative(Print2D::Coordinate centerRelativeCoordinate, char* text, float scale) {
	Coordinate centerAbsoluteCoordinate;
	centerAbsoluteCoordinate.x = convertRelativeToAbsolutePosition(centerRelativeCoordinate.x, screenWidth);
	centerAbsoluteCoordinate.y = convertRelativeToAbsolutePosition(centerRelativeCoordinate.y, screenHeight);

	Coordinate originAbsoluteCoordinate = convertCenterAbsoluteToOriginAbsolute(centerAbsoluteCoordinate, text, scale);

	Coordinate originRelativeCoordinate;
	originRelativeCoordinate.x = convertAbsoluteToRelativePosition(originAbsoluteCoordinate.x, screenWidth);
	originRelativeCoordinate.y = convertAbsoluteToRelativePosition(originAbsoluteCoordinate.y, screenHeight);

	return originRelativeCoordinate;
}

Print2D::Coordinate Print2D::convertCenterAbsoluteToOriginAbsolute(Print2D::Coordinate centerAbsoluteCoordinate, char* text, float scale) {
	float textWidth;
	float textHeight;
	print3D->MeasureText(&textWidth, &textHeight, scale, text);

	Coordinate originAbsoluteCoordinate;
	originAbsoluteCoordinate.x = centerAbsoluteCoordinate.x - textWidth / 2;
	originAbsoluteCoordinate.y = centerAbsoluteCoordinate.y - textHeight / 2;

	return originAbsoluteCoordinate;
}

float Print2D::convertRelativeToAbsolutePosition(float relativePosition, float pixels) {
	return pixels * relativePosition / 100;
}

float Print2D::convertAbsoluteToRelativePosition(float absolutePosition, float pixels) {
	return absolutePosition / pixels * 100;
}