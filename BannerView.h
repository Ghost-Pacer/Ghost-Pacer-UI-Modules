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
    vector<char*> bannerLinesText;
    Position position;
    int itemSpacing;
    float scale;
    unsigned int color;
    Print2D *print2D;
};

#endif