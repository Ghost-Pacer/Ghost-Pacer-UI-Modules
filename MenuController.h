#ifndef __MENU_CONTROLLER_H_
#define __MENU_CONTROLLER_H_

#include <vector>
#include "Print2D.h"
#include "OGLES2Tools.h"

using std::vector;

class MenuController {
public:
	MenuController(vector<char*> menuItemsText, int spacing, float scale, unsigned int selectedItemColor, unsigned int unselectedItemColor, CPVRTPrint3D *print3D);
	int selectedItemIndex();
	char* selectedItem();
	void navigateDown();
	void navigateUp();
	void render();
private:
	vector<Print2D::AttributedText> menuItemsAttributedText;
	int itemSpacing;
	unsigned int selectedItemColor;
	unsigned int unselectedItemColor;
	CPVRTPrint3D *print3D;
	int selectedItemIndex;

};

#endif