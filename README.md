## Overview
Print2D and MenuController are dependent on OGLESTools2.h, which is provided by the PowerVR SDK.

These files were designed to work specifically with OpenGL ES 2.

## Print2D
This class adds extra functionality to the CPVRTPrint3D class provided by PowerVR. CPVRTPrint3D can render text where the top left coordinate of its bounding box is given by the user. Print2D allows the rendering text at a given center coordinate of its bounding box. This makes it trivial to center text on a screen.

Additionally, Print2D can render a list of text, each with their own scale and color. The text will appear spaced evenly and will be centered horizontally within its bounding box.

## MenuView
MenuView interface allows easily displaying a menu and visually navigating up and down to select different options.

## BannerView
Used to display single/multi-line text centered or pinned-to-top of screen. You can customize the text size, but if the provided size is too large the banner will automatically scale to fit the screen width.

## ButtonLegendView
Displays Ghost Pacer Glasses button glyphs in the bottom right corner of the screen. Loads glyphs from a custom version of Montserrat Bold font.

## CustomMontserratBold
A modified version of Montserrat Bold font that replaces certain characters with Ghost Pacer icons.
Modified chracters:
* ~ → Up Button Glyph
* ` → Down Button Glyph
* \ → Ok Button Glyph