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

int z = 0;
int blockSize = 32;


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

// takes in number of times to run the test and get average of (n)
float getAvgTimeMain(int n){

	struct timespec ts_begin, ts_end;
	double elapsed1;
	double totalElapsed = 0;
	
	z = 0;
	
	

	for (int i = 0; i < n; i++){
	
		int arr[1024*1024];// * (1024 * 1024)); // turn size of int (bytes) to size of int (kilobyte) smaller number to larger number
		
		int arrSize = 1024 * 1024;// * (1024 * 1024);
		
		//populate array
		for (int x = 0; x < arrSize; x++){
			arr[x] = x;
		}
	
		//for main memory
		clock_gettime(CLOCK_MONOTONIC, &ts_begin);
		for (int j = 0; j < arrSize; j = j + blockSize){
			z += arr[j];
		}
		
		clock_gettime(CLOCK_MONOTONIC, &ts_end);
		
		elapsed1 = ts_end.tv_sec - ts_begin.tv_sec;
		elapsed1 += ((ts_end.tv_nsec - ts_begin.tv_nsec)/1000000000.0);
		totalElapsed = totalElapsed + elapsed1;
		
	}
	printf("Ignore, this is a dummy value to keep compiler from throwing away loops: %d\n", z);
	return(totalElapsed/n); // returning the average time for all results
}

// takes in number of times to run the test and get average of (n)
float getAvgTimeCache(int n){

	struct timespec ts_begin, ts_end;
	double elapsed1;
	double totalElapsed = 0;
	
	z = 0;
	

	for (int i = 0; i < n; i++){
	
		int arr[1024*1024];// * (1024 * 1024)); // turn size of int (bytes) to size of int (kilobyte) smaller number to larger number
		
		int arrSize = 1024 * 1024;// * (1024 * 1024);
		
		//populate array
		for (int x = 0; x < arrSize; x++){
			arr[x] = x+1;
		}
		
		// only check the same amount of time that we did for main memory
		arrSize = arrSize/blockSize;
	
		//for cache memory
		clock_gettime(CLOCK_MONOTONIC, &ts_begin);
		for (int j = 0; j < arrSize; j++){
			z += arr[0];
		}
		clock_gettime(CLOCK_MONOTONIC, &ts_end);
		
		
		elapsed1 = ts_end.tv_sec - ts_begin.tv_sec;
		elapsed1 += ((ts_end.tv_nsec - ts_begin.tv_nsec)/1000000000.0);
		totalElapsed = totalElapsed + elapsed1;
		
		
	}
	
	
	printf("Ignore, this is a dummy value to keep compiler from throwing away loops: %d\n", z);
	return(totalElapsed/n); // returning the average time for all results
	
	
}

int getCacheSize(){

	struct timespec ts_begin, ts_end;
 	double elapsed1;
 	int *arr;

	int MAX_CACHE = 65536;

 	/////////////////////////////////////////////////////////////////////////////
 	////////////////////////////////////////////////////////////////////////////
 	// New Comparing multiple arrays like assignment suggests (getting good results)
 	//long length = (1024 * 1024) -1;
 	int j;

 	for (j = 1; j <= MAX_CACHE; j = j*2){

 		arr = malloc(sizeof(int) * (1024 * 1024));

 		
 		clock_gettime(CLOCK_MONOTONIC, &ts_begin);
 		for (int i = 0; i < (j * 1024 * 1024); i++){
 			arr[0]++;
 		}
 		clock_gettime(CLOCK_MONOTONIC, &ts_end);
 		elapsed1 = ts_end.tv_sec - ts_begin.tv_sec;
 		elapsed1 += ((ts_end.tv_nsec - ts_begin.tv_nsec));

 		if (elapsed1 < 1000.0 && elapsed1 > 0.0){
 			break;
 		} 
 	}
 	return j;
}


int main(int argc, char *argv[]){

	int numTimesToAccess = 1000;

	printf("Calculating time to access main memory...\n");
	float mainTime = getAvgTimeMain(numTimesToAccess);
	printf("Complete!\n");
	
	printf("Calculating time to access cache...\n");
	float cacheTime = getAvgTimeCache(numTimesToAccess);
	printf("Complete!\n");
	
	//float percentFaster = (mainTime/cacheTime) * 100;
	
	printf("Calculating cache size...\n");
	int cacheSize = getCacheSize();
	printf("Complete!\n\n");

	printf("Average time to access main memory is %f seconds\n", mainTime);
	printf("Average time to access cache is %f seconds\n", cacheTime);
	
	//printf("Accessing cache is %.0f%% faster than main memory when running %d tests\n", percentFaster, numTimesToAccess);
	
	printf("Cache Size is: %d\n\n", cacheSize);
	
	

}






