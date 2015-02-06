//Copyright (C) 2014-2015  Corwin Hansen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
	if (argc == 2 && (strcmp(argv[1], "-c") || strcmp(argv[1], "-d")){//if valid input
		if (strcmp(argv[1], "-c")){//if input wat compress


			exit(EXIT_SUCCESS);//exit
		}
		else if (strcmp(argv[1], "-d")){//if input was decompress


			exit(EXIT_SUCCESS);//exit
		}
	}
	printf("Invalid argument. \n -c <file> to compress. \n -d <file> to decompress")
		exit(EXIT_FAILURE);//exit
}














int compress(FILE* file){//compress file and write on disk. Return 1 for error.

}



















int decompress(FILE* file){//decompress file and write on disk. Return 1 for error.

}