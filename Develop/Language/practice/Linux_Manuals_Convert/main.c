
/*******************************************************************************
*	author: jie
*	Non-publicise
*	Do not use without authorization
* *****************************************************************************/


/*******************************************************************************
*	include
* *****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/*******************************************************************************
*	code
* *****************************************************************************/
uint64_t GetFileSize(char* File)
{
	FILE *fp = NULL;
	uint64_t FileSize = 0;

	fp = fopen(File, "r");
	fseek(fp, 0L, SEEK_END);
	FileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	fclose(fp);

	return FileSize;
}


uint64_t GetFileImage(char* File, void *pBuffer, uint64_t Size)
{
	FILE *fp = NULL;
	uint64_t Result;

	fp = fopen(File, "r");
	fseek(fp, 0, SEEK_SET);

	Result = fread(pBuffer, sizeof(char), Size, fp);
	fclose(fp);

	return Result;
}

uint64_t OutputImageToFile(char* File, void *pBuffer, uint64_t Size)
{
	FILE *fp = NULL;
	uint64_t Result;

	fp = fopen(File, "w");
	fseek(fp, 0, SEEK_SET);

	Result = fwrite(pBuffer, sizeof(char), Size, fp);
	fclose(fp);

	return Result;
}

void ConvertProcess(char *pStart, uint64_t *pOffset)
{

	uint32_t ConvertSize = 0;
	uint32_t WhiteSize = 0;
	uint64_t Header = *pOffset;

	while (0x0a == *(pStart + ConvertSize))
	{
		
		*(pStart + ConvertSize) = 0x20;
		
		WhiteSize++;
		ConvertSize++;
	}
	
	while (0x20 == *(pStart + ConvertSize))
	{
		WhiteSize++;
		ConvertSize++;
	}

	while (0x0a != *(pStart + ConvertSize))
	{
		ConvertSize++;
	}

		
	for (uint64_t i = 0; i < ConvertSize/2; i++)
	{
		char TempChar = *(pStart + i);
		*(pStart + i) = *(pStart + ConvertSize - 1 - i);
		*(pStart + ConvertSize - 1 - i) = TempChar;
	}

	for (uint64_t i = 0; i < (ConvertSize - WhiteSize)/2; i++)
	{
		char TempChar = *(pStart + i);
		*(pStart + i) = *(pStart + (ConvertSize - WhiteSize - 1) - i);
		*(pStart + (ConvertSize - WhiteSize - 1) - i) = TempChar;
	}

	*pOffset += ConvertSize;

	if (ConvertSize >= 197)
		ConvertProcess(pStart + ConvertSize, pOffset);

}


void ContentProcess(void *pBuffer, uint64_t Size)
{
	char *c = (char*)pBuffer;
	uint8_t LineWidth = 0;
	uint64_t LineSize = 0;
	
	for (uint64_t i = 0; i < Size; i++)
	{
		if (0x0a != *(c + i))
			LineWidth++;
		else
		{
			if (197 <= LineWidth)
			{
				ConvertProcess(c + i, &i);
			}
			LineWidth = 0;
			LineSize++;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf(".e.g: ./main file outfile\n");
		return 1;
	}

	uint64_t FileSize;
	void *pBuffer;
	uint64_t Result;

	
	FileSize = GetFileSize(argv[1]);

	pBuffer = malloc(sizeof(char) * FileSize);

	Result = GetFileImage(argv[1], pBuffer, FileSize);

	ContentProcess(pBuffer, FileSize);
	
	OutputImageToFile(argv[2], pBuffer, FileSize);
		
	free(pBuffer);

	return 0;
}

