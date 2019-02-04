/*
* @Author Sahil Patel (spatel32@umbc.edu)
* This file contains a program that gets an argument from
* the command line and then find whether the requested device
* has ioports and memory mapped to it
*
* Resources used:
* https://stackoverflow.com/questions/14376696/searching-for-specific-words-in-a-text-file
* https://stackoverflow.com/questions/4841219/print-part-of-a-string-in-c
* https://stackoverflow.com/questions/6567742/passing-an-array-as-an-argument-to-a-function-in-c
*/


#include <stdio.h>
#include <string.h>

/*
* print_without_whitespace - Prints the passed in array without whitespaces
*   and only for a specific amount of characters.
*
* @line[]: c-string of what is to be printed
* @size: length of the c-string line
* @printChar: number of character user wants printed not including whitespaces
* Return: nothing
*/
void print_without_whitespace(char line[], int size, int printChar);

int main( int argc, char *argv[] ) 
{  
    if( argc > 2 ) 
    {
        printf("Multiple devices given. \n");
    }
    else if( argc < 2 ) 
    {
        printf("No device given \n");
    }
    else 
    {
        FILE *ioports = fopen("/proc/ioports", "r");
        int foundIOPort = 0;
  
        if ( ioports != NULL )
        {
            char line[128];
            
            printf("ioports: \n");       
            while( fgets( line, sizeof(line), ioports) != NULL )
            {
                if( strstr(line, argv[1]) != NULL)
                {
                    foundIOPort = 1;
                    //printf("%*.*s \n", 5, 12, line);
                    print_without_whitespace(line, 128, 9);
                }
            }

            if( foundIOPort == 0 )
            {
                printf("No matching entry found in /proc/ioports \n");
            }
        }
        fclose(ioports);

        FILE *iomem = fopen("/proc/iomem", "r");
        int foundIOMem = 0;

        if ( iomem != NULL )
        {
            char line[128];

            printf("iomem: \n");
            while( fgets( line, sizeof(line), iomem) != NULL )
            {
                if( strstr(line, argv[1]) != NULL)
                {
                    foundIOMem = 1;
                    //printf("%*.*s \n", 5, 22, line);
                    print_without_whitespace(line, 128, 17);
                }
                
            }

            if( foundIOMem == 0 )
            {
                printf("No matching entry found in /proc/iomem \n");
            }
        }
        fclose(iomem);
   }
}


void print_without_whitespace(char line[], int size, int printChar)
{
    int counter = 0;
    for(int i = 0; i < size; i++)
    {
        if( line[i] != 32 && counter < printChar)
        {
            printf("%c", line[i]);
            counter++;
        }
    }
    printf("\n");
}
