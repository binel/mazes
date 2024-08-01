
#include "ui.h"

bool IsInButton(Button button, int xpos, int ypos) {
    bool inXRange = xpos >= button.xStart && xpos <= button.xStart + button.width;
    bool inYRange = ypos >= button.yStart && ypos <= button.yStart + button.height;

    return inXRange && inYRange;
}
