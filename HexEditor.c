#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void parseAndPrint (FILE * file, int granularity)
{
	int currentChar  = 0;
	int msbOfAddress = 0;
	int bytesCounter = 0;
	int endOfLine    = 0;

	currentChar = fgetc(file);

	switch (granularity)
	{
		case 8:
			printf("\n            00 01 02 03 04 05 06 07");
			break;

		case 16:
			printf("\n            00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
			break;

		default:
			printf("\n            00 01 02 03 04 05 06 07");
			break;
	}

	while (currentChar != EOF)
	{
		endOfLine = 0;
		printf("\n0x%08x ", msbOfAddress);

		while ( (currentChar != EOF) && (endOfLine == 0) )
		{
			printf(" %02x", currentChar);
			currentChar = fgetc(file);
			bytesCounter++;

			if (bytesCounter%granularity == 0)
			{
				msbOfAddress = msbOfAddress + granularity;
				endOfLine = 1;
			}
		}
	}

	printf("\n\n");
	printf("Number of bytes : %d\n", bytesCounter);
}


int main (int argc, char * argv[])
{
	FILE * file;
	int printScale = 16;

	if (argc == 1)
	{
		printf("No file specified\n");
		return -1;
	}

	if (argc == 3)
	{
		if (strcmp(argv[2], "-8" ) == 0) printScale = 8;
		if (strcmp(argv[2], "-16") == 0) printScale = 16;
	}

	file = fopen(argv[1], "rb");

	if (file == NULL)
	{
		printf("File %s cannot be opened. Check that it exists.\n", argv[1]);
		return -1;
	}

	parseAndPrint(file, printScale);

	if (file != NULL)
	{
		fclose(file);
	}

	return EXIT_SUCCESS;
}
