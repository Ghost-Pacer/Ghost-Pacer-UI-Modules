#ifndef __BANNER_VIEW_H_
#define __BANNER_VIEW_H_

#include <vector>
#include "Print2D.h"

using std::vector;

class BannerView {
public:
    enum Position { TOP, CENTER };

    BannerView(vector<char*> bannerLinesText, Position position, int spacing, float scale, unsigned int color, CPVRTPrint3D *print3D);
    ~BannerView();
    void render();
private:
    struct Coordinate {
        float x, y;
    };

    const float TOP_PADDING_PIXELS = 20;
    const float MAX_HORIZONTAL_PADDING_PIXELS = 20;

    vector<char*> bannerLinesText;
    Position position;
    int spacing;
    float scale;
    unsigned int color;
    CPVRTPrint3D *print3D;
    Print2D *print2D;

    void renderAtTopPosition();
    void renderAtCenterPosition();
    Coordinate topPositionAbsoluteOriginCoordinate();
    Coordinate centerPositionRelativeCenterCoordinate();
    void scaleToFitIfNeeded();
    Coordinate screenDimensions();
    float maxTextWidth();
};

#endif