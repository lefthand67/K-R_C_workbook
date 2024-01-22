#include <stdio.h>

#define TAB 4
#define MAXLINE 1000

int get_line(char line[], int limit);
void tab_to_space(char new_line[], char old_line[], int tab_length);


int main()
{
	char raw_line[MAXLINE], correct_line[MAXLINE];
	int len, i;

	for (i = 0; (len=get_line(raw_line, MAXLINE)) > 0; ++i)
		tab_to_space(correct_line, raw_line, TAB);

	/* I want the result on new line in case of EOF without '\n'*/
	if (len == 0)
		printf("\n");

	printf("%s\n", correct_line);

	return 0;
}


int get_line(char line[], int limit)
{
	int c, i;

	for (i = 0; i<limit-1 && (c = getchar())!='\n' && c != EOF; ++i)
		line[i] = c;

//	if (c == '\n') {
//		line[i] = c;
//		++i;
//	}

	line[i] = '\0';

	return i;
}


void tab_to_space(char new_line[], char old_line[], int tab_length)
{
	int c, i, j, k;  /* j counts chars for new_line, k counts spaces */

	j = 0;
	for (i = 0; (c = old_line[i])!= EOF && c!='\0'; ++i) {
		if (c == '\t') {
			for (k = 0; k < tab_length; ++k) {
				new_line[j] = ' ';
				++j;
			}
			continue;
		}
		new_line[j] = c;
		++j;
	}
	new_line[j] = '\0';
}
