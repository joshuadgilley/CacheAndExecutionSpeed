#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        
        
        //splice string to compare to passed in string
        char subbuff[16];
		memcpy( subbuff, &line[0], 15 );
		subbuff[15] = '\0';
        
        char* passedInString = "cache_alignment";
        
        //if statement to compare strings
        if (!strcmp(subbuff, passedInString)){
        
		    // assign variables for seperated values
			char* first_val;
			char* second_val;
		
			// loop through the entire line
			for (int i = 0; i < len-1; i = i+1)
			{
		  		// if a char of the line is equal to a comma
		  		if (line[i] == ':')
		    		{ 
		      		// Set the first val to the line and add an end char where the comma was
		      		first_val = line;
		      		line[i] = '\0';
		      
		      		// Set the second val to the address of the char after the end char assigned above
		      		second_val = &line[i+2];
		    	}
			}
			printf("%s", second_val);
        }   
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
