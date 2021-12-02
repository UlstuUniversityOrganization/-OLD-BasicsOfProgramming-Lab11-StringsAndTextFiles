#include <stdio.h>
#include <string>

#define ARRAY_SIZE 1000
#define MAX_SYMBOLS 256

void SetNop(char*& string, const char* inputStr)
{
	int strLength = strlen(string);
	int inputStrLength = strlen(inputStr);

	for (int i = 0; i < strLength; i++)
	{
		if (string[i] == 'a' || string[i] == 'A')
		{
			memcpy(string + i + inputStrLength, string + i + 1, strLength - i);
			strLength += inputStrLength;
			for (int j = 0; j < inputStrLength; j++)
			{
				string[i] = inputStr[j];
				i++;
			}
		}
	}

}

int main()
{
	FILE* filePointer;
	fopen_s(&filePointer, "data.txt", "rt");

	unsigned int stringsCount = ARRAY_SIZE;
	char** strings = new char*[stringsCount];
	for (int i = 0; i < stringsCount; i++)
		strings[i] = nullptr;

	int id = 0;
	while (!feof(filePointer))
	{
		strings[id] = new char[MAX_SYMBOLS];
		fgets(strings[id], MAX_SYMBOLS, filePointer);
		SetNop(strings[id], "<i><b>NOP</b></i>");
		id++;
	}
	fclose(filePointer);

	fopen_s(&filePointer, "site.html", "wt");

	fputs("<HTML>\n", filePointer);
	fputs("    <BODY>\n", filePointer);
	for (int i = 0; i < stringsCount; i++)
	{
		if (strings[i])
		{
			if (i == 0)
			{
				int len = strlen(strings[i]);
				strings[i][len - 1] = '\0';
				fprintf(filePointer, "        <H1> %s <BR></H1>\n", strings[i]);
				strings[i][len - 1] = '\n';
			}
			else
			{
				int len = strlen(strings[i]);
				strings[i][len - 1] = '\0';
				fprintf(filePointer, "        %s <BR>\n", strings[i]);
				strings[i][len - 1] = '\n';
			}
		}
		else
			break;

	}
	fputs("    </BODY>", filePointer);
	fputs("\n", filePointer);
	fputs("</HTML>", filePointer);


	char* tempStr = new char[MAX_SYMBOLS] {"Hola, what are you doing?"};

	SetNop(tempStr, "HER");

	for (int i = 0; i < MAX_SYMBOLS; i++)
		printf("%c", tempStr[i]);
}