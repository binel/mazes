#ifndef maze_memory_h
#define maze_memory_h

#include <stdlib.h>

void *Maze_malloc(size_t size);

void Maze_free(void *p);

#endif