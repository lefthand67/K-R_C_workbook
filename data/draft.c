#include <stdio.h>

#define TAB 4
#define MAXLINE 1000
#define NCOLUMN 40

int get_line(char line[], int limit);
void detab(char new_line[], char old_line[], int tab_length);
void wrap_line(char new_line[], char old_line[], int line_length, int n_column);


int main()
{
	int len;
	char line[MAXLINE], detabbed_line[MAXLINE*2], wrapped_line[MAXLINE*2];

	while ((len=get_line(line, MAXLINE)) > 0) {
		detab(detabbed_line, line, TAB);
		wrap_line(wrapped_line, detabbed_line, len, NCOLUMN);
		printf("%s\n", wrapped_line);
	}
	return 0;
}


int get_line(char line[], int limit)
{
	int c, i;

	for (i = 0; i<limit-1 && (c = getchar())!='\n' && c != EOF; ++i)
		line[i] = c;
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


void wrap_line(char new_line[], char old_line[], int line_length, int n_column)
{
	int c, end_c;  /* current char and end char of the short line */
	int i, j;  /* counters for old and new lines respectively */
	int line_end;  /* helps to find the end of the short line */
	int keeper;  /* keeps the last end_line value */
	int problem_line;  /* the flag indicates there are no blanks in the short line */

	keeper = line_end = n_column;
	problem_line = 0;
	j = 0;  /* normally j == i, but we will need it in case of problem lines */

	/* loop through old line */
	for (i = 0; (c=old_line[i])!='\0' && c!=EOF; ++i, ++j) {
		/* find the end of new line, this is the blank or null terminator */
		if (!problem_line)
			while ((end_c=old_line[line_end]) != ' ' && end_c!='\0')
				--line_end;
		/* in case the short line does not contain blanks */
		if (line_end == -1) {
			line_end = keeper;  /* restore the line_end */
			problem_line = 1;  /* mark the problem */
		}
		/* put \n at the end of the current line_end */
		if (i == line_end) {
			new_line[j] = '\n';
			/* emergency plan for a problem line */
			if (problem_line) {
				--j;
				new_line[j] = '-';
				++j;
				i -= 2;  /* we had to substitute 2 non blank chars with '-'
							and \n */
				problem_line = 0;
			}
			keeper = line_end += n_column-1;
			continue;
		}
		new_line[j] = c;
	}
	/* finish the whole expression */
	new_line[j] = '\0';
}
