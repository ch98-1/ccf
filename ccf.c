//Copyright (C) 2014-2015  Corwin Hansen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
	if (argc == 2 && (strcmp(argv[1], "-c") || strcmp(argv[1], "-d")){//if valid input
		if (strcmp(argv[1], "-c")){//if input wat compress
			if (compress(argv[2])){//run compress function and check if it gives errors
				printf("error: could not compress file");//error message
			}
			exit(EXIT_SUCCESS);//exit
		}
		else if (strcmp(argv[1], "-d")){//if input was decompress
			if (decompress(argv[2])){//runde compress function and check if it gives errors
				printf("error: could not decompress file");//error message
			}
			exit(EXIT_SUCCESS);//exit
		}
	}
	printf("Invalid argument. \n -c <file> to compress. \n -d <file> to decompress")
		exit(EXIT_FAILURE);//exit
}














int compress(const char* file){//compress file and write on disk. Return 1 for error.
	FILE* input, output;//input and output file





	return 0;//no error
}



















int decompress(const char* file){//decompress file and write on disk. Return 1 for error.
	FILE* input, output;//input and output file




	return 0;//no error
}