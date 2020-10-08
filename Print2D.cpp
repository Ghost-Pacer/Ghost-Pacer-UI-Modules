#include "Print2D.h"

Print2D::Print2D(CPVRTPrint3D *print3D) {
	this->print3D = print3D;
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

// HELPER FUNCTIONS
Print2D::Coordinate Print2D::convertCenterRelativeToOriginRelative(Print2D::Coordinate centerRelativeCoordinate, char* text, float scale) {
	unsigned int screenWidth;
	unsigned int screenHeight;
	print3D->GetAspectRatio(&screenWidth, &screenHeight);

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