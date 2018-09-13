/********
* the insertion sort algorithm 
***************/

#include<stdio.h>

/*********************************************************/
#define ARRAY_SIZE 15

/*********************************************************/
void OuputArrayItem(char a[], char length);
void insertionSortMy(char a[], char length);
void insertionSort(char a[], char length);
void insertionSort1(char a[], char length);
void insertionSort2(char a[], char length);

/*********************************************************/
void OuputArrayItem(char a[], char length)
{	
	char index = 0;
	printf("%d\n",length);
	for(; index < length; index++)
	{
		printf(" %d", a[index]);
	}
	printf("\n");
}

/*********************************************************
*
* this function is no the optimal algorithm as there are my replace operation.
*
**********************************************************/
void insertionSortMy(char a[], char length)
{
    char tmp;	
	char iterate = 1;

	if((char*)0 == a)
		printf("the array pointer is wrong\n");

	if(ARRAY_SIZE != length)
		printf("the arry size is wrong\n");
	
	for(; iterate < length; iterate++)
	{
		char index = iterate;
		for(; index > 0; index--)
		{
			if(a[index] < a[index - 1])
			{
				tmp = a[index];
				a[index] = a[index -1];
				a[index -1] = tmp;
			}
			else
				break;
		}
		OuputArrayItem(a,ARRAY_SIZE);
	}
}

void insertionSort(char a[], char length)
{
	char key;
	char iterate = 1;
	
	if((char*)0 == a)
		printf("the array pointer is wrong\n");

	if(ARRAY_SIZE != length)
		printf("the arry size is wrong\n");

	
	for(; iterate < length; iterate++)
	{
		key = a[iterate];
		char index = iterate - 1;
		/*ERR, the for loop could not let the index pointer to the position that should be replaced*/
		for(; index >= 0; index--)
		{
			if( key < a[index])
			{
				a[index + 1] = a[index];
			}
			else
			{
				break;
			}
		}		
		/*ERR, the wrong index leading to small data lost*/
		a[index] = key;
		OuputArrayItem(a,ARRAY_SIZE);
	}
}

/**************************************************
*
* this function is the optimal insetion sort algorithm.
*
**************************************************/

void insertionSort2(char a[], char length)
{
	char key;
	char iterate = 1;
	if((char*)0 == a)
		printf("the array pointer is wrong\n");

	if(ARRAY_SIZE != length)
		printf("the arry size is wrong\n");
	
	for(; iterate < length; iterate++)
	{
		key = a[iterate];
		char index = iterate;
		while((index >0) && (a[index-1] > key))
		{
			a[index] = a[index-1];
			index--;
			
		}
		a[index] = key;
		OuputArrayItem(a,ARRAY_SIZE);
	}
}

void insertionSort1(char a[], char length)
{
	char key;
	char iterate = 1;
	
	if((char*)0 == a)
		printf("the array pointer is wrong\n");

	if(ARRAY_SIZE != length)
		printf("the arry size is wrong\n");	
	
	for(; iterate < length; iterate++)
	{
		key = a[iterate];
		/*ERR, the index should be more than 0*/
		char index = iterate - 1;
		while((index > 0) && (a[index] > key))
		{
			a[index + 1] = a[index];
			index--;
		}
		a[index] = key;
	}
}

int main()
{
	char array[ARRAY_SIZE]={14,23,43,30,5,13,20,1,7,0,6,12,4,100,2};
	OuputArrayItem(array, ARRAY_SIZE);
	insertionSortMy(array, ARRAY_SIZE);
	OuputArrayItem(array, ARRAY_SIZE);
	return 0;
}

