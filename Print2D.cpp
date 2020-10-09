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
	/*vector<MenuItem> menuItems;
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
	*/

	vector<Coordinate> menuItemPositions;
	float xAbsolutePosition = 0;
	float yAbsolutePosition = 0;
	for (int ii = 0; ii < menuItemsText.size(); ii++) {
		Coordinate menuItemPosition;
		menuItemPosition.x = xAbsolutePosition;
		menuItemPosition.y = yAbsolutePosition;
		menuItemPositions.push_back(menuItemPosition);

		float textWidth;
		float textHeight;
		print3D->MeasureText(&textWidth, &textHeight, scale, menuItemsText[ii]);
		yAbsolutePosition += textHeight;
	}

	float maxTextWidth = 0;
	float totalTextHeight = 0;
	for (int ii = 0; ii < menuItemsText.size(); ii++) {
		float textWidth;
		float textHeight;
		print3D->MeasureText(&textWidth, &textHeight, scale, menuItemsText[ii]);

		if (textWidth > maxTextWidth) { maxTextWidth = textWidth; }
		totalTextHeight += textHeight;
	}

	for (int ii = 0; ii < menuItemsText.size(); ii++) {
		float textWidth;
		float textHeight;
		print3D->MeasureText(&textWidth, &textHeight, scale, menuItemsText[ii]);
		
		float largestAndCurrentWidthDifference = maxTextWidth - textWidth;
		if (largestAndCurrentWidthDifference > 0) {
			menuItemPositions[ii].x += largestAndCurrentWidthDifference / 2;
		}
	}

	Coordinate centerAbsoluteCoordinate;
	centerAbsoluteCoordinate.x = convertRelativeToAbsolutePosition(xRelativePosition, screenWidth);
	centerAbsoluteCoordinate.y = convertRelativeToAbsolutePosition(yRelativePosition, screenHeight);

	Coordinate targetOriginAbsoluteCoordinate;
	targetOriginAbsoluteCoordinate.x = centerAbsoluteCoordinate.x - maxTextWidth / 2;
	targetOriginAbsoluteCoordinate.y = centerAbsoluteCoordinate.y - totalTextHeight / 2;

	for (int ii = 0; ii < menuItemsText.size(); ii++) {
		menuItemPositions[ii].x += targetOriginAbsoluteCoordinate.x;
		menuItemPositions[ii].y += targetOriginAbsoluteCoordinate.y;
	}

	for (int ii = 0; ii < menuItemsText.size(); ii++) {
		menuItemPositions[ii].x = convertAbsoluteToRelativePosition(menuItemPositions[ii].x, screenWidth);
		menuItemPositions[ii].y = convertAbsoluteToRelativePosition(menuItemPositions[ii].y, screenHeight);
	}

	for (int ii = 0; ii < menuItemsText.size(); ii++) {
		Coordinate renderAtCoordinate = menuItemPositions[ii];
		renderText(renderAtCoordinate.x, renderAtCoordinate.y, scale, color, menuItemsText[ii]);
	}
}

// HELPER FUNCTIONS
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