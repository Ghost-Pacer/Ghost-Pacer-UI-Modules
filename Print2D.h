#ifndef __PRINT2D_H_
#define __PRINT2D_H_

#include <vector>
#include "OGLES2Tools.h";

using std::vector;

class Print2D {
public:	
	struct AttributedText {
		char *text;
		float scale;
		unsigned int color;
	};

	Print2D(CPVRTPrint3D *print3D);
	void renderText(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);
	void renderTextCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, char *text);
	void renderVerticalMenuCenteredAt(float xRelativePosition, float yRelativePosition, float scale, unsigned int color, int spacing, vector<char*> menuItemsText);
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
    Coordinate calculateMenuOriginAbsoluteCoordinate(float xCenterRelativePosition, float yCenterRelativePosition, vector<MenuItem> menuItems);
    void offsetMenuItemsBy(Coordinate offset, vector<MenuItem> &menuItems);
    void convertMenuItemPositionsFromAbsoluteToRelative(vector<MenuItem> &menuItems);
    void renderMenuItems(vector<MenuItem> menuItems);
    float maxTextWidth(vector<MenuItem> menuItems);
    float totalTextHeight(vector<MenuItem> menuItems);

	Coordinate convertCenterRelativeToOriginRelative(Coordinate centerRelativeCoordinate, char *text, float scale);
	Coordinate convertCenterAbsoluteToOriginAbsolute(Coordinate centerAbsoluteCoordiate, char *text, float scale);
	float convertRelativeToAbsolutePosition(float relativePosition, float pixels);
	float convertAbsoluteToRelativePosition(float absolutePosition, float pixels);
};

#endif