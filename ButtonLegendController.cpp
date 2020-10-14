#include "ButtonLegendController.h"
#include <iostream>

ButtonLegendController::ButtonLegendController(int spacing, CPVRTPrint3D *print3D) {
	const int BUTTON_COUNT = 3;
	for (int ii = 0; ii < BUTTON_COUNT; ii++) {
		Print2D::AttributedText attributedText;
		attributedText.color = UNSELECTED_COLOR;
		attributedText.scale = SCALE;
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
	print2D->renderVerticalMenuCenteredAt(X_RELATIVE_CENTER_COORDINATE, Y_RELATIVE_CENTER_COORDINATE, itemSpacing, legendItemsAttributedText);
}

void ButtonLegendController::setButtonIsEnabled(int buttonIndex, bool enabled) {
	const int BUTTON_COUNT = 3;
	if (buttonIndex < 0 || buttonIndex >= BUTTON_COUNT) { return; }

	legendItemsAttributedText[buttonIndex].color = enabled ? selectedColorOfButton(buttonIndex) : UNSELECTED_COLOR;
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

unsigned int ButtonLegendController::selectedColorOfButton(int buttonIndex) {
	switch (buttonIndex) {
	case 0:
		return UP_BUTTON_SELECTED_COLOR;
	case 1:
		return DOWN_BUTTON_SELECTED_COLOR;
	case 2:
		return OK_BUTTON_SELECTED_COLOR;
	default:
		return UNSELECTED_COLOR;
	}
}