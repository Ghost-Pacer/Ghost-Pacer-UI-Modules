#include "ButtonLegendController.h"
#include <iostream>

ButtonLegendController::ButtonLegendController(int spacing, float scale, CPVRTPrint3D *print3D) {
	const int BUTTON_COUNT = 3;
	for (int ii = 0; ii < BUTTON_COUNT; ii++) {
		Print2D::AttributedText attributedText;
		attributedText.color = UNSELECTED_COLOR;
		attributedText.scale = scale;
		attributedText.text = stringRepresentationOfButton(ii);
		legendItemsAttributedText.push_back(attributedText);
	}

	itemSpacing = spacing;
	print2D = new Print2D(print3D);
}

ButtonLegendController::~ButtonLegendController() {
	delete print2D;
}

void ButtonLegendController::render() {
	const float X_RELATIVE_CENTER_COORDINATE = 85.0;
	const float Y_RELATIVE_CENTER_COORDINATE = 85.0;
	print2D->renderVerticalMenuCenteredAt(X_RELATIVE_CENTER_COORDINATE, Y_RELATIVE_CENTER_COORDINATE, itemSpacing, legendItemsAttributedText);
}

// ***** HELPER FUNCTIONS ****
char* ButtonLegendController::stringRepresentationOfButton(int buttonIndex) {
	switch (buttonIndex) {
	case 0:
		return const_cast<char*>(UP_BUTTON);
	case 1:
		return const_cast<char*>(DOWN_BUTTON);
	case 2:
		return const_cast<char*>(OK_BUTTON);
	default:
		return "\0";
	}
}