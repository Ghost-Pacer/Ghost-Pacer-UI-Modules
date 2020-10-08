#ifndef __PRINT2D_H_
#define __PRINT2D_H_

#include "OGLES2Tools.h";

class Print2D {
public:	
	Print2D(CPVRTPrint3D *print3D);
	void renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);
	void renderTextCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);

private:
	struct Coordinate {
		float x;
		float y;
	};

	CPVRTPrint3D *print3D;
	Coordinate convertCenterRelativeToOriginRelative(Coordinate centerRelativeCoordinate, char* text, float scale);
	Coordinate convertCenterAbsoluteToOriginAbsolute(Coordinate centerAbsoluteCoordiate, char *text, float scale);
	float convertRelativeToAbsolutePosition(float relativePosition, float pixels);
	float convertAbsoluteToRelativePosition(float absolutePosition, float pixels);
};

#endif