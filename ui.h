#ifndef maze_ui_h
#define maze_ui_h

#include <stdbool.h>

typedef struct {
    
    int xStart;
    int yStart;
    int width;
    int height;
    // TODO text 
} Button;

bool IsInButton(Button button, int xpos, int ypos);
#endif
