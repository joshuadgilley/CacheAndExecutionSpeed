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


int main(void){

	char* cache_block_size = read("cache_alignment");
	printf("%s", cache_block_size);
	
	char* cache_size = read("cache size");
	printf("%s", cache_size);

}







