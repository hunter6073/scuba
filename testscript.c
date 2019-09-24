#include<stdio.h>
#include<sys/time.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
/* demo script version 2.0 */

void readfile(char*,char*,int); // not needed right now
void writefile(char*,char*,int,int);

int main(int argc, char* argv[]) // with user input for the amount of memory blocks to initialize
{
    char block_size[64];
    strcpy(block_size, argv[1]);
    int iblock_size;
    iblock_size = atoi(block_size); // get the number of memory blocks from script input

    // creating a pointer array of input size
    char *mp[iblock_size];
    char *output[iblock_size];
    int i = 0; // typical counter for for loops
    int n = 0; // typical counter for for loops
    int counter = 0; // counter for files
    int memoryarr[iblock_size]; // array to store memory size of each pointer;
    double timearr[iblock_size];// array to store runtime
    int setpoint[8] = {20,50,70,90,100,125,150,160};
    for(i=0;i<iblock_size;i++)
    {
        n = setpoint[i%8]*1000; // n will float along the lines of the setpoint value
        mp[i]= (char*)malloc(n);
	memoryarr[i] = n;
	output[i] = (char*)malloc(200);
    }

    // clock current time as start time
    struct timeval stop, start,indstart,indend;
    gettimeofday(&start, NULL);

    // write memory block to 100 files each
    for(n=0;n<iblock_size;n++)
    {
	gettimeofday(&indstart,NULL); // get start time for current pointer

        for(i=0;i<100;i++)
        {
            //create a temp file
            char name[22];
            snprintf(name, 100, "./tempfolder/temp%d.dat", counter++); // puts string into buffer
            //write to temp files
           writefile(mp[n],name,(memoryarr[n]-rand()%5000+1),1);
        }
        gettimeofday(&indend,NULL); // get end time for current pointer
        // output the time of one pointer's output
	timearr[n] = (double) (indend.tv_sec - indstart.tv_sec) * 1000 + (double) (indend.tv_usec - indstart.tv_usec) / 1000;
    }

    //clock current time as end time
    gettimeofday(&stop, NULL);

    // get time difference and output result
    for(i=0;i<iblock_size;i++)
	{
        snprintf(output[i],200,"this is pointer %d, the size is %d bytes, it took %'.3f' milliseconds to finish writing 100 files within a 5 KB range.\n",i+1,memoryarr[i],timearr[i]);
	printf("%s",output[i]);
	}
    printf("A total of %d files have been written",iblock_size*100);
    printf("The entire duration is %'.3f'milliseconds\n", (double) (stop.tv_sec - start.tv_sec) * 1000 + (double) (stop.tv_usec - start.tv_usec) / 1000);
    double timediff = (double) (stop.tv_sec - start.tv_sec) * 1000 + (double) (stop.tv_usec - start.tv_usec) / 1000;
    printf("The file writing rate is %f files per milisecond", iblock_size*100/timediff);
    return 0;
}

/************* read file into memory *************/
// currently, this function is deemed optional, but it's good to keep it in the code for future usage
void readfile(char* filename, char* memorypointer, int iblock_size)
{
    FILE* input;
    input = fopen(filename,"r");
    while (!feof(input))
    {
        fread(memorypointer,iblock_size, 1, input);
    }
    
}

/*********** write from memory to file ************/
void writefile(char* memorypointer, char* filename, int size_of_element, int num_of_element)
{
    FILE* output;
    output = fopen(filename,"wb+");
    //write to temp file
    fwrite(memorypointer,size_of_element,num_of_element,output);
    fclose(output);
}

