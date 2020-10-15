#include "BannerView.h"

BannerView::BannerView(vector<char*> bannerLinesText, Position position, int spacing, float scale, unsigned int color, CPVRTPrint3D* print3D) {
    this->bannerLinesText = bannerLinesText;
    this->position = position;
    this->spacing = spacing;
    this->scale = scale;
    this->color = color;
    this->print3D = print3D;
    this->print2D = new Print2D(print3D);
}

BannerView::~BannerView() {
    delete print2D;
}

void BannerView::render() {
    scaleToFitIfNeeded();

    switch (position) {
    case TOP:
        renderAtTopPosition();
        break;
    case CENTER:
        renderAtCenterPosition();
        break;
    }
}

// ***** HELPER FUNCTIONS *****
void BannerView::renderAtTopPosition() {
    Coordinate absoluteOriginCoordinate = topPositionAbsoluteOriginCoordinate();
    print2D->renderVerticalMenuAbsoluteOriginAt(absoluteOriginCoordinate.x, absoluteOriginCoordinate.y, scale, color, spacing, bannerLinesText);
}

BannerView::Coordinate BannerView::topPositionAbsoluteOriginCoordinate() {
    float screenWidth = screenDimensions().x;
    float bannerWidth = maxTextWidth();

    Coordinate absoluteOriginCoordinate;
    absoluteOriginCoordinate.x = (screenWidth - bannerWidth) / 2;
    absoluteOriginCoordinate.y = TOP_PADDING_PIXELS;

    return absoluteOriginCoordinate;
}

void BannerView::renderAtCenterPosition() {
    Coordinate relativeCenterCoordinate = centerPositionRelativeCenterCoordinate();
    print2D->renderVerticalMenuCenteredAt(relativeCenterCoordinate.x, relativeCenterCoordinate.y, scale, color, spacing, bannerLinesText);
}

BannerView::Coordinate BannerView::centerPositionRelativeCenterCoordinate() {
    Coordinate relativeCenterCoordinate;
    relativeCenterCoordinate.x = 50.0f;
    relativeCenterCoordinate.y = 50.0f;
    return relativeCenterCoordinate;
}

void BannerView::scaleToFitIfNeeded() {
    float screenWidth = screenDimensions().x;
    float bannerWidth = maxTextWidth();
    float safeAreaWidth = screenWidth - 2 * MAX_HORIZONTAL_PADDING_PIXELS;
    if (bannerWidth > safeAreaWidth) {
        float oversizeFactor = safeAreaWidth / bannerWidth;
        this->scale = this->scale * oversizeFactor;
    }
}

BannerView::Coordinate BannerView::screenDimensions() {
    unsigned int screenWidth;
    unsigned int screenHeight;
    print3D->GetAspectRatio(&screenWidth, &screenHeight);

    Coordinate screenDimensions;
    screenDimensions.x = screenWidth;
    screenDimensions.y = screenHeight;
    
    return screenDimensions;
}

float BannerView::maxTextWidth() {
    float maxWidth = 0;
    int size = bannerLinesText.size();
    for (int ii = 0; ii < size; ii++) {
        float textWidth;
        float textHeight;
        print3D->MeasureText(&textWidth, &textHeight, scale, bannerLinesText[ii]);

        if (textWidth > maxWidth) { maxWidth = textWidth; }
    }

    return maxWidth;
}