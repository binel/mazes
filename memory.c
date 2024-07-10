#include "memory.h"

// TODO break this raylib dependency - probably do your own logging
#include <raylib.h>
#include <stdio.h>

void *Maze_malloc(size_t size) {
    char logMessage[100];
    snprintf(logMessage, sizeof(logMessage), "Allocated %zu bytes", size);
    TraceLog(LOG_INFO, logMessage);
    return malloc(size);
}

void Maze_free(void *p) {
    // TODO figure out how to log the amount of memory freed
    TraceLog(LOG_INFO, "Freed memory");
    free(p);
}
