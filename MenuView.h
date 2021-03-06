#ifndef __MENU_VIEW_H_
#define __MENU_VIEW_H_

#include <vector>
#include "Print2D.h"

using std::vector;

class MenuView {
public:
    // MenuView Constructor
    MenuView(vector<char*> menuItemsText, int spacing, float scale, unsigned int selectedItemColor, unsigned int unselectedItemColor, CPVRTPrint3D* print3D, bool isScreenRotated) : MenuView(menuItemsText, 0, spacing, scale, selectedItemColor, unselectedItemColor, print3D, isScreenRotated) {};

    // MenuView Constructor
    MenuView(vector<char*> menuItemsText, int selectedItemIndex, int spacing, float scale, unsigned int selectedItemColor, unsigned int unselectedItemColor, CPVRTPrint3D *print3D, bool isScreenRotated);
    
    // MenuView Destructor
    ~MenuView();

    // Renders menu on screen
    void render();

    // Gets the index of the currently selected menu item
    // 0 corresponds to the top most item
    int getSelectedItemIndex();

    // Gets the title of the currently selected menu item
    char* getSelectedItem();

    // Selects the menu item above the currently selected item
    // Wraps around if already at the top
    void navigateUp();

    // Selects the menu item below the currently selected item
    // Wraps around if already at the bottom
    void navigateDown();
private:
    vector<Print2D::AttributedText> menuItemsAttributedText;
    int itemSpacing;
    unsigned int selectedItemColor;
    unsigned int unselectedItemColor;
    Print2D *print2D;
    int selectedItemIndex;

    void refreshMenuItemAttributes();
};

#endif