#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#define FILENAME_LEN_MAX 10

#define ANSI 0
#define UTF_8 1
#define UNICODE 2

void print_input_file_prompt()
{
	printf("Input the filename(%d characters most) to be tranformed:", FILENAME_LEN_MAX);
}

int get_user_input(char *pszBuf)
{
	int iInput = 0;
	int iInputLen = 0;
	for(iInputLen = 0; iInputLen < FILENAME_LEN_MAX && (iInput = getchar()) != '\n'; iInputLen++)
	{
		pszBuf[iInputLen] = iInput;
	}
	
	if(iInputLen >= FILENAME_LEN_MAX)
		return 0;//filename len exceeds size
	
	return 1;//filename len is valid
}

void print_options()
{
	printf("%d .ANSI\n", ANSI);
	printf("%d .UTF-8\n", UTF_8);
	printf("%d .Unicode\n", UNICODE);
}

int main()
{
	char szFilename[FILENAME_LEN_MAX + 1] = {0};
	print_input_file_prompt();
	int iRes = get_user_input(szFilename);
	
	if(iRes)
	{
		int iOption = 0;
		printf("Open file %s to transform\n", szFilename);
		print_options();
		scanf(" %d", &iOption);
	}
	else{
		printf("Input file length exceeds the limit(%d)\n", FILENAME_LEN_MAX);
	}
	return 0;
}
