#include "ButtonLegendController.h"
#include <iostream>

/**
* DOES: Creates a new instance of ButtonLegendController class
* PARAMS: enabledNavigationButtonColor - Color of up and down button glyphs when enabled
*         enabledOkButtonColor - Color of ok button glyph when enabled
*         disabledButtonColor - Color of button glyphs when disabled
*         spacing - Spacing between button glyphs
*         print3D - Pointer to an already set up CPVRTPrint3D object
* RETURNS: ButtonLegendController instance
* THROWS: None
*/
ButtonLegendController::ButtonLegendController(unsigned enabledNavigationButtonColor, unsigned enabledOkButtonColor, unsigned disabledButtonColor, int spacing, CPVRTPrint3D *print3D) {
    const int BUTTON_COUNT = 3;
    for (int ii = 0; ii < BUTTON_COUNT; ii++) {
        Print2D::AttributedText attributedText;
        attributedText.color = disabledButtonColor;
        attributedText.scale = SCALE;
        attributedText.text = stringRepresentationOfButton(ii);
        legendItemsAttributedText.push_back(attributedText);
    }

    this->enabledNavigationButtonColor = enabledNavigationButtonColor;
    this->enabledOkButtonColor = enabledOkButtonColor;
    this->disabledButtonColor = disabledButtonColor;
    this->spacing = spacing;
    print2D = new Print2D(print3D);
}

/**
* DOES: Frees memory and destroys ButtonLegendController instance
* PARAMS: None
* RETURNS: None
* THROWS: None
*/
ButtonLegendController::~ButtonLegendController() {
    delete print2D;
}

/**
* DOES: Renders button legend on screen
* PARAMS: None
* RETURNS: None
* THROWS: None
*/
void ButtonLegendController::render() {
    print2D->renderVerticalMenuCenteredAt(X_RELATIVE_CENTER_COORDINATE, Y_RELATIVE_CENTER_COORDINATE, spacing, legendItemsAttributedText);
}

/**
* DOES: Sets the button at the given buttonIndex to its enabled/disabled appearance
* PARAMS: buttonIndex - Index of button to change state of
*         enabled - Whether the button should be enabled or disabled
* RETURNS: None
* THROWS: None
*/
void ButtonLegendController::setButtonIsEnabled(int buttonIndex, bool enabled) {
    const int BUTTON_COUNT = 3;
    if (buttonIndex < 0 || buttonIndex >= BUTTON_COUNT) { return; }

    legendItemsAttributedText[buttonIndex].color = enabled ? selectedColorOfButton(buttonIndex) : disabledButtonColor;
}

// ***** HELPER FUNCTIONS ****
/**
* DOES: Returns the ASCII character corresponding to a button glyph
* PARAMS: buttonIndex - Index of button to find button glyph character of
* RETURNS: String containing ASCII character corresponding to a button glyph
* THROWS: None
*/
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

/**
* DOES: Returns the color of a button glyph in its selected state
* PARAMS: buttonIndex - Index of button to find selected color of
* RETURNS: Selected color of button in ABGR format
* THROWS: None
*/
unsigned int ButtonLegendController::selectedColorOfButton(int buttonIndex) {
    switch (buttonIndex) {
    case 0:
        return enabledNavigationButtonColor;
    case 1:
        return enabledNavigationButtonColor;
    case 2:
        return enabledOkButtonColor;
    default:
        return disabledButtonColor;
    }
}