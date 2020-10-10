#include "MenuController.h"

MenuController::MenuController(vector<char*> menuItemsText, int spacing, float scale, unsigned int selectedItemColor, unsigned int unselectedItemColor, CPVRTPrint3D *print3D) {
	int size = menuItemsText.size();
	for (int ii = 0; ii < size; ii++) {
		Print2D::AttributedText attributedText;
		attributedText.color = ii == 0 ? selectedItemColor : unselectedItemColor;
		attributedText.scale = scale;
		attributedText.text = menuItemsText[ii];
		menuItemsAttributedText.push_back(attributedText);
	}

	this->itemSpacing = spacing;
	this->selectedItemColor = selectedItemColor;
	this->unselectedItemColor = unselectedItemColor;
	this->print3D = print3D;
	this->selectedItemIndex = 0;
}

