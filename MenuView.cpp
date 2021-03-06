#include "MenuView.h"

/**
 * DOES: Creates a new instance of MenuView class
 * PARAMS: menuItemsText - Title of each option in menu. First element
 *         is displayed at the top, last element at the bottom.
 *         selectedItemIndex - Index of selected item
 *         spacing - Spacing between menu items
 *         scale - Size of menu item text
 *         selectedItemColor - Color of menu item when selected
 *         unselectedItemColor - Color of menu item when unselected
 *         print3D - Pointer to an already set up CPVRTPrint3D object
 * RETURNS: MenuView instance
 * THROWS: None
 */
MenuView::MenuView(vector<char*> menuItemsText, int selectedItemIndex, int spacing, float scale, unsigned int selectedItemColor, unsigned int unselectedItemColor, CPVRTPrint3D *print3D, bool isScreenRotated) {
    int size = menuItemsText.size();

    bool selectedItemIndexIsValid = selectedItemIndex >= 0 && selectedItemIndex < size;
    this->selectedItemIndex = selectedItemIndexIsValid ? selectedItemIndex : 0;

    for (int ii = 0; ii < size; ii++) {
        Print2D::AttributedText attributedText;
        attributedText.color = ii == this->selectedItemIndex ? selectedItemColor : unselectedItemColor;
        attributedText.scale = scale;
        attributedText.text = menuItemsText[ii];
        menuItemsAttributedText.push_back(attributedText);
    }

    this->itemSpacing = spacing;
    this->selectedItemColor = selectedItemColor;
    this->unselectedItemColor = unselectedItemColor;
    this->print2D = new Print2D(print3D, isScreenRotated);
}

/**
 * DOES: Frees memory and destroys MenuView instance
 * PARAMS: None
 * RETURNS: None
 * THROWS: None
 */
MenuView::~MenuView() {
    delete print2D;
}

/**
 * DOES: Renders menu on screen
 * PARAMS: None
 * RETURNS: None
 * THROWS: None
 */
void MenuView::render() {
    refreshMenuItemAttributes();

    const float X_RELATIVE_CENTER_COORDINATE = 50.0;
    const float Y_RELATIVE_CENTER_COORDINATE = 50.0;
    print2D->renderVerticalMenuCenteredAt(X_RELATIVE_CENTER_COORDINATE, Y_RELATIVE_CENTER_COORDINATE, itemSpacing, menuItemsAttributedText);
}

/**
 * DOES: Gets the index of the currently selected menu item.
 *       0 corresponds to the top most item
 * PARAMS: None
 * RETURNS: Index of currently selected menu item
 * THROWS: None
 */
int MenuView::getSelectedItemIndex() {
    return selectedItemIndex;
}

/**
 * DOES: Gets the title of the currently selected menu item.
 * PARAMS: None
 * RETURNS: Title of currently selected menu item
 * THROWS: None
 */
char* MenuView::getSelectedItem() {
    return menuItemsAttributedText[selectedItemIndex].text;
}

/**
 * DOES: Selects the menu item above the currently selected item
 *       Wraps around if already at the top
 * PARAMS: None
 * RETURNS: None
 * THROWS: None
 */
void MenuView::navigateUp() {
    selectedItemIndex = (selectedItemIndex - 1) % menuItemsAttributedText.size();
}

/**
 * DOES: Selects the menu item below the currently selected item
 *       Wraps around if already at the bottom
 * PARAMS: None
 * RETURNS: None
 * THROWS: None
 */
void MenuView::navigateDown() {
    selectedItemIndex = (selectedItemIndex + 1) % menuItemsAttributedText.size();
}

// ***** HELPER FUNCTIONS *****

/**
 * DOES: Updates the color of each menu item so that everything displays
 *       the unselected color except for the currently selected item
 * PARAMS: None
 * RETURNS: None
 * THROWS: None
 */
void MenuView::refreshMenuItemAttributes() {
    int size = menuItemsAttributedText.size();
    for (int ii = 0; ii < size; ii++) {
        menuItemsAttributedText[ii].color = (ii == selectedItemIndex) ? selectedItemColor : unselectedItemColor;
    }
}