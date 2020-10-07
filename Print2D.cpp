#include "Print2D.h"

Print2D::Print2D(CPVRTPrint3D *print3D) {
	this->print3D = print3D;
}

void Print2D::renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text) {
	print3D->Print3D(xRelativePosition, yRelativePosition, scale, color, text);
}

void Print2D::renderTextAtOrigin(float xOriginRelativePosition, float yOriginRelativePosition, float scale, unsigned int color, char *text) {
	float* width = new float();
	float* height = new float();
	print3D->MeasureText(width, height, 1.0f, text);

	float screenWidth = 720;
	float screenHeight = 1280;

	float xOriginAbsolutePosition = screenWidth * xOriginRelativePosition / 100;
	float yOriginAbsolutePosition = screenHeight * yOriginRelativePosition / 100;

	float xAbsolutePosition = xOriginAbsolutePosition - *width / 2;
	float yAbsolutePosition = yOriginAbsolutePosition - *height / 2;


	float xRelativePosition = xAbsolutePosition / screenWidth * 100;
	float yRelativePosition = yAbsolutePosition / screenHeight * 100;
	renderText(xRelativePosition, yRelativePosition, scale, color, text);
}