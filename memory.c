#include "memory.h"

// TODO break this raylib dependency - probably do your own logging
#include <raylib.h>
#include <stdio.h>

/*
 * Every allocation is size_t larger than it needs to be (probably 8 bytes), 
 * which is used to store the size of the allocation for logging
 */

long total = 0;

void *Maze_malloc(size_t size) {
    size_t *p = (size_t *)malloc(size + sizeof(size_t));
    *p = size;
    total += size; 
    char logMessage[100];
    snprintf(logMessage, sizeof(logMessage), "Allocated %zu bytes. %zu total", size, total);
    TraceLog(LOG_INFO, logMessage);    
    
    return (void *)(p + 1);
    
    return malloc(size);
}

void Maze_free(void *p) {
	if (p) {
		size_t *ptr = (size_t *)p - 1;
		
		total -= *ptr;
		
		char logMessage[100];
		snprintf(logMessage, sizeof(logMessage), "Freed memory: %zu bytes. %zu total", *ptr, total);
		TraceLog(LOG_INFO, logMessage);
		
		free(ptr);
	} else {
		TraceLog(LOG_INFO, "Attempted to free null pointer");
	}
}
