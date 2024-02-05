#include <stdio.h>

#define TAB 4
#define MAXLINE 1000


int get_line(char line[], int limit);
void detab(char new_line[], char old_line[], int tab_stop);
void remove_comments(char new_line[], char old_line[]);


int main()
{
	char original_line[MAXLINE], detabbed_line[MAXLINE*TAB], new_line[MAXLINE*TAB];

	while (get_line(original_line, MAXLINE) > 0) {
		detab(detabbed_line, original_line, TAB);
		remove_comments(new_line, original_line);
		printf("%s", new_line);
	}
}


int get_line(char line[], int limit)
{
	int c, i;

	for (i = 0; i<limit-1 && (c=getchar())!='\n' && c!=EOF; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';

	return i;
}


void detab(char new_line[], char old_line[], int tab_length)
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


void remove_comments(char new_line[], char old_line[])
{
	int i, j, c, prev_c;
	int comment;  /* comment line checker */

	comment = j = 0;

	for (i = 0; (c=old_line[i])!=EOF && c!='\0'; ++i) {
		/* check for comment line */
		if (prev_c == '/' && c == '*') {
			comment = 1;
			--j;
		}
		else if (prev_c == '*' && c == '/') {
			comment = 0;
			prev_c = c;
			continue;
		}
		/* if comment line then just skip chars */
		if (!comment) {
			new_line[j] = c;
			++j;
		}
		prev_c = c;
	}
	new_line[j] = '\0';
}
