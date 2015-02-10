//Copyright (C) 2014-2015  Corwin Hansen
#ifndef MAIN_H//include protection
#define MAIN_H
#include <stdio.h>//standard libraries
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define VERSION ".cf0" //version 0 file extension will be cf0

#define DEFAULT_RLE_ELEMENT_SIZE 1 //default size for each element of rle compression

int compress(const unsigned char* file);//compress file and write on disk. Return 1 for error.

int decompress(const unsigned char* file);//decompress file and write on disk. Return 1 for error.

int removeExtension(unsigned char* dest, const unsigned char* file);//remove file extension. return 1 for error.



#endif