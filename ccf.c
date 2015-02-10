//Copyright (C) 2014-2015  Corwin Hansen
#include "data.h"

int main(int argc, unsigned char *argv[]){
	if (argc == 3 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-d") == 0)){//if valid input
		FILE* test = fopen(argv[2], "r");//test if file can be opend
		if (test == NULL || errno == ENOENT){
			fclose(test);//close file
			printf("file: %s could not be opend\n", argv[2]);//give error message
			exit(EXIT_SUCCESS);//exit
		}
		if (strcmp(argv[1], "-c") == 0){//if input wat compress
			if (compress(argv[2])){//run compress function and check if it gives errors
				printf("error: could not compress file");//error message
			}
			exit(EXIT_SUCCESS);//exit
		}
		else if (strcmp(argv[1], "-d") == 0){//if input was decompress
			if (decompress(argv[2])){//runde compress function and check if it gives errors
				printf("error: could not decompress file");//error message
			}
			exit(EXIT_SUCCESS);//exit
		}
	}
	printf("Invalid argument. \n -c <file> to compress. \n -d <file> to decompress");//give error message and instruction
	exit(EXIT_FAILURE);//exit
}














int compress(const unsigned char* file){//compress file and write on disk. Return 1 for error.
	FILE *input, *output, *temp1, *temp2;//input and output files
	temp1 = tmpfile();//set temp files
	temp2 = tmpfile();
	input = fopen(file, "rb");//open file for binary reading
	unsigned char* data = malloc(256);//allocate 256 byte for file name 
	strcpy(data, file);//copy destination file
	data = strcat(data, VERSION);//copy file extention
	output = fopen(data, "wb");//open destination for writing
	free(data);//ferr data
	data = calloc(1, 1);//allocate 1 bytes for data
	if (input == NULL || output == NULL){//if files could not be opend
		printf("could not open fikes\n");//error message
		return 1;//exit
	}






	//rle
	int element = DEFAULT_RLE_ELEMENT_SIZE;//get elemnt size. make sure it will fit the file without remainder.
	data[0] = element;//each element's size in bytes
	if (fwrite(data, 1, 1, output) != 1){
		printf("error, coluld not write to file\n");
		return 1;//exit
	}
	if (element == 0){//deal with no rle
		while (1){//loop
			fread(data, 1, 1, input);//read byte from temp
			if (feof(input)){//get out of loop if at end of file
				break;
			}
			fwrite(data, 1, 1, temp1);//write to output
		}
	}
	else {//if there is rle
		unsigned char *current = malloc(element);
		unsigned char *last = malloc(element);
		int count = 0;//current number of 
		while (1){//loop
			fread(current, element, 1, input);//get input
			if (feof(input)){//write last byte and get out of loop if at end of file
				putc(count, temp1);//write number of element
				fwrite(last, element, 1, temp1);//write the element
				break;
			}
			if (count == 0) {//if it is the first letter
				count++;//increment count
			}
			else {//if not first of serese
				if (memcmp(last, current, element) == 0 && count < 255){//if current element is equal to last element
					count++;//increment count
				}
				else{//if at end of serese of elements
					putc(count, temp1);//write number of element
					fwrite(last, element, 1, temp1);//write the element
					count = 0;//reset count
					fseek(input, -1, SEEK_CUR);//go back one
				}

			}
			memcpy(last, current, element);//copy current to last
		}


		free(current);//free memory used for rle
		free(last);
	}
	//end of rle







	//copy file
	rewind(temp1);
	while (1){//loop
		fread(data, 1, 1, temp1);//read byte from temp
		if (feof(temp1)){//get out of loop if at end of file
			break;
		}
		fwrite(data, 1, 1, output);//write to output
	}



	fclose(temp1);//close files
	fclose(temp2);
	fclose(input);
	fclose(output);
	free(data);
	return 0;//no error
}



















int decompress(const unsigned char* file){//decompress file and write on disk. Return 1 for error.
	FILE *input, *output, *temp1, *temp2;//input and output files
	temp1 = tmpfile();//set temp files
	temp2 = tmpfile();
	input = fopen(file, "rb");//open file for binary reading
	unsigned char *data = malloc(256);//allocate 256 bytes for file name
	if (removeExtension(data, file)){//remove file extension and check if there was 
		return 1;//exit
	}
	output = fopen(data, "w");//open destination for writing
	free(data);//free data
	data = calloc(1, 1);//allocate 1 bytes for data
	if (input == NULL || output == NULL){//if files could not be opend
		printf("could not open files\n");//error message
		return 1;//exit
	}







	//rle
	int element;//size of elemnt
	if (fread(data, 1, 1, input) != 1){
		printf("error, coluld not read file\n");
		return 1;//exit
	}
	element = data[0];
	if (element == 0){//deal with no rle
		while (1){//loop
			fread(data, 1, 1, input);//read byte from temp
			if (feof(input)){//get out of loop if at end of file
				break;
			}
			fwrite(data, 1, 1, temp1);//write to output
		}
	}
	else{//if there is rle
		unsigned char *current = malloc(element);//current element
		int count = 0;//number of element
		while (1){//loop while not at end of file
			fread(data, 1, 1, input);//get number of element
			fread(current, element, 1, input);//get element
			if (feof(input)){//get out of loop if at end of file
				break;
			}
			int i;
			for (i = data[0]; i > 0; i--){//for number of element times
				fwrite(current, element, 1, temp1);//write element
			}
		}
	}






	


	//copy file
	rewind(temp1);
	while (1){//loop
		fread(data, 1, 1, temp1);//read byte from temp
		if (feof(temp1)){//get out of loop if at end of file
			break;
		}
		fwrite(data, 1, 1, output);//write to output
	}



	
	free(data);//free data memory
	return 0;//no error
}

























int removeExtension(unsigned char* dest, const unsigned char* file){//remove file extension. return 1 for error
	strcpy(dest, file);//copy string
	unsigned char* extension = strstr(dest, VERSION);//get extention
	if (extension == NULL){
		printf("incorrect file format\n");//print out error
		return 1;
	}
	dest[strlen(dest) - 4] = 0;//end string before extension
	return 0;//end function
}