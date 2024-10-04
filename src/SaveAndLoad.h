#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

#include <SDL2/SDL.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void save_to_file(const char *filename, const char *data);
char* load_from_file(const char *filename);

#endif