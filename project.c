/*
Chris Taylor, Josh Gilley OS Final Project

11/17/2020

Information about assignment is in the README.md


Sources Used: 

	For reading a file line by line:
	https://stackoverflow.com/questions/3501338/c-read-file-line-by-line 
	
	For getting a substring of a char*
	https://stackoverflow.com/questions/4214314/get-a-substring-of-a-char
	
	For comparing strings
	https://www.programiz.com/c-programming/library-function/string.h/strcmp
	
*/



#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char* read(char* string)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int buffSize;
    int lastChar;
    
    
    //if statements to search for either "cache_alignment" of "cache size"
    if (!strcmp(string, "cache_alignment")){
    	buffSize = 16;
    	lastChar = 15;
    }
    
    else if (!strcmp(string, "cache size")){
    	buffSize = 11;
    	lastChar = 10;
    }
    
    else {
    	printf("Given argument other than 'cache_alignment' or 'cache size'");
    	return "";
    }
    
    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        
        //splice string to compare to passed in string
        char subbuff[buffSize];
		memcpy( subbuff, &line[0], lastChar );
		subbuff[lastChar] = '\0';
        
        char* passedInString = string;
        
        //if statement to compare strings
        if (!strcmp(subbuff, passedInString)){
        
		    // assign variables for seperated values
			char* first_val;
			char* second_val;
		
			// loop through the entire line
			for (int i = 0; i < len-1; i = i+1){
			
		  		// if a char of the line is equal to a comma
		  		if (line[i] == ':'){ 

		      		// Set the second val to the address of the char after the end char assigned above
		      		second_val = &line[i+2];
		    	}
			}
			return (second_val);
        }   
    }

	//closing the file
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

int readAndWriteFileByBlock(int block){
	FILE *in, *out;
	int blockSize = block;
	unsigned char *buffer = NULL;
	buffer = (unsigned char*) malloc(blockSize);
	size_t bufSize;
	
	if ((in=fopen("readIn.txt", "rb")) == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	if ((out=fopen("writeOut.txt", "wb")) == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	while((bufSize = fread(buffer, sizeof(unsigned char), blockSize, in)) > 0) {
		fwrite(buffer, sizeof(unsigned char), bufSize, out);
	}
	fclose(out);
	fclose(in);
	
	return 0;
	
}


int main(int argc, char *argv[]){

	struct timespec ts_begin, ts_end;
	double elapsed1;
	int *arr;

	char* cache_block_size = read("cache_alignment");
	printf("%s", cache_block_size);
	
	char* cache_size = read("cache size");
	printf("%s", cache_size);
	
	int intarr[15] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
	for (int i = 0; i < sizeof(intarr); i++){
		clock_gettime(CLOCK_MONOTONIC, &ts_begin);
		readAndWriteFileByBlock(intarr[i]);
		clock_gettime(CLOCK_MONOTONIC, &ts_end);
		
		elapsed1 = ts_end.tv_sec - ts_begin.tv_sec;
		elapsed1 += ((ts_end.tv_nsec - ts_begin.tv_nsec)/ 1000000000.0);
		
		printf("Block Size %d: %f\n", intarr[i], elapsed1);
		
		if (i == 15){
			break;
		}
	}
	
	printf("\n\n\n");
	
	
	/////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	// New Comparing multiple arrays like assignment suggests (getting good results)
	long length = (1024 * 1024) -1;
	
	for (int j = 0; j < sizeof(intarr); j++){
	
		arr = malloc(sizeof(int) * (1024 * 1024));
	
		clock_gettime(CLOCK_MONOTONIC, &ts_begin);
		for (int i = 0; i < (intarr[j] * 1024 * 1024); i++){
			int val = arr[(i *16) & length]++;
		}
		clock_gettime(CLOCK_MONOTONIC, &ts_end);
		elapsed1 = ts_end.tv_sec - ts_begin.tv_sec;
		elapsed1 += ((ts_end.tv_nsec - ts_begin.tv_nsec));
		printf("%f nanoseconds at ... %d block size\n", elapsed1, intarr[j]);
		
		
		clock_gettime(CLOCK_MONOTONIC, &ts_begin);
		for (int i = 0; i < (intarr[j] * 1024 * 1024); i++){
			arr[(0 *16) & length]++;
		}
		clock_gettime(CLOCK_MONOTONIC, &ts_end);
		elapsed1 = ts_end.tv_sec - ts_begin.tv_sec;
		elapsed1 += ((ts_end.tv_nsec - ts_begin.tv_nsec));
		printf("%f nanoseconds at ... %d block size\n", elapsed1, intarr[j]);
		
		if (j == 15){
			break;
		}
	}
	/////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	
	

}






