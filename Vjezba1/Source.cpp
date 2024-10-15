#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 1024

int NumberOfRows(const char*);


int main()
{
	int numOfRows = 0;

	numOfRows = NumberOfRows("imedat.txt");
	
	printf("Hello world\n");
	return 0;
}


int NumberOfRows(const char*)
{
	

	FILE* fp = NULL;
	int numOfRows = 0;
	char buffer[MAX] = {};

	fp = fopen(fileName, "r");
	if(!fp)
	{
		return -1;
	}

	while(!feof(fp))
	{
	   fgets(buffer, MAX, fp)
	   numOfRows++;
	}

}
int NumberOfRows(const char*)
{
	

	FILE* fp = NULL;
	int numOfRows = 0;
	char buffer[MAX] = {};

	fp = fopen(fileName, "r");
	if(!fp)
	{
		return -1;
	}

	while(!feof(fp))
	{
	   fgets(buffer, MAX, fp)
	   numOfRows++;
	}

}