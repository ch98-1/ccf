//Copyright (C) 2014-2015  Corwin Hansen
#ifndef MAIN_H//include protection
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VERSION 0

int compress(const char* file);//compress file and write on disk. Return 1 for error.

int decompress(const char* file);//decompress file and write on disk. Return 1 for error.



#endif