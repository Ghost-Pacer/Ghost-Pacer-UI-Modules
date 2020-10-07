#ifndef __PRINT2D_H_
#define __PRINT2D_H_

#include "OGLES2Tools.h";

class Print2D {
public:	
	Print2D(CPVRTPrint3D *print3D);
	void renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);
	void renderTextAtOrigin(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);

private:
	CPVRTPrint3D *print3D;
};

#endif