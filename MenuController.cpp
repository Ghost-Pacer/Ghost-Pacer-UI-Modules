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
	this->print2D = new Print2D(print3D);
	this->selectedItemIndex = 0;
}

MenuController::~MenuController() {
	delete print2D;
}

void MenuController::render() {
	refreshMenuItemAttributes();

	const float X_RELATIVE_CENTER_COORDINATE = 50.0;
	const float Y_RELATIVE_CENTER_COORDINATE = 50.0;
	print2D->renderVerticalMenuCenteredAt(X_RELATIVE_CENTER_COORDINATE, Y_RELATIVE_CENTER_COORDINATE, itemSpacing, menuItemsAttributedText);
}

int MenuController::getSelectedItemIndex() {
	return selectedItemIndex;
}

char* MenuController::getSelectedItem() {
	return menuItemsAttributedText[selectedItemIndex].text;
}

void MenuController::navigateUp() {
	selectedItemIndex = (selectedItemIndex - 1) % menuItemsAttributedText.size();
}

void MenuController::navigateDown() {
	selectedItemIndex = (selectedItemIndex + 1) % menuItemsAttributedText.size();
}

// HELPER FUNCTIONS
void MenuController::refreshMenuItemAttributes() {
	int size = menuItemsAttributedText.size();
	for (int ii = 0; ii < size; ii++) {
		menuItemsAttributedText[ii].color = (ii == selectedItemIndex) ? selectedItemColor : unselectedItemColor;
	}
}