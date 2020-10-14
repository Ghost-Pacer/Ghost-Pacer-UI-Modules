#ifndef __BUTTON_LEGEND_CONTROLLER_H_
#define __BUTTON_LEGEND_CONTROLLER_H_

#include "Print2D.h"

class ButtonLegendController {
public:
	ButtonLegendController(int spacing, float scale, CPVRTPrint3D *print3D);
	~ButtonLegendController();
	void render();
	void setButtonIsEnabled(int buttonIndex, bool enabled);
private:
	const char *UP_BUTTON = "\"";
	const char *DOWN_BUTTON = "#";
	const char *OK_BUTTON = "$";
	const unsigned int UP_BUTTON_SELECTED_COLOR = 0xFFFF0000;
	const unsigned int DOWN_BUTTON_SELECTED_COLOR = 0xFFFF0000;
	const unsigned int OK_BUTTON_SELECTED_COLOR = 0xFF00FF00;
	const unsigned int UNSELECTED_COLOR = 0x99999999;

	vector<Print2D::AttributedText> legendItemsAttributedText;
	int itemSpacing;
	Print2D *print2D;

	char* stringRepresentationOfButton(int buttonIndex);
};

#endif