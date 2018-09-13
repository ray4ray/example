#include <stdio.h>
#include <sys/time.h>
#include <memory.h>
#include <stdlib.h>

#define TIMEDIFF(start, end)  ((end.tv_sec-start.tv_sec)*1000000 + end.tv_usec -start.tv_usec)
#define LOOP_NUMBER (30000)

int main()
{

	struct timeval start, end;
        int memSize[9]= {64, 512, 1024, 4096, 16384, 65536, 1048576,4194304,8388608};

        for(int sizeIndex = 0 ; sizeIndex < 9; sizeIndex++)
	{
		void * memPtr = malloc(memSize[sizeIndex]);
		if(NULL == memPtr)
		{
		      printf("failed to allocate memory, sizeIndex %d, size %d\n", sizeIndex, memSize[sizeIndex]);
		      break;
		}

                gettimeofday(&start, NULL);
		for(int loopCount = 0; loopCount < LOOP_NUMBER ; loopCount++)
		{
		     memset(memPtr, 0 , memSize[sizeIndex]);
		}
	        gettimeofday(&end, NULL);

		printf("memset cost %4.6f us for memory size %d bytes\n", memSize[sizeIndex], TIMEDIFF(start,end)/(1.0*LOOP_NUMBER));
	}
	return 0;
}
