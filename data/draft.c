#include <stdio.h>

#define TAB 4
#define MAXLINE 1000

int get_line(char line[], int limit);
void detab(char new_line[], char old_line[], int tab_length);
void entab (char new_line[], char old_line[], int tab_lenght);


int main()
{
	char raw_line[MAXLINE], correct_line[MAXLINE];
	int len, i;

	for (i = 0; (len=get_line(raw_line, MAXLINE)) > 0; ++i)
		entab(correct_line, raw_line, TAB);

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


void entab (char new_line[], char old_line[], int tab_length)
{
	int c, prev_c;    /* current and previous chars */
    int	i, j;    /* i is for old_line and j is for new_line */
    int	count;    /* count blanks */

	prev_c = -1;  /* -1 is certainly is not in ASCII table */
	j = 0;
	count = 1;

	for (i = 0; (c=old_line[i])!=EOF && c!='\0'; ++i) {
		if (c == ' ' && prev_c == ' ') {
			++count;
			if ((count % (tab_length*2)) == 0) {
				j -= tab_length-1;		/* indexing starts from 0 */
				c = '\t';
				count = 1;
			}
		}
		else
			count = 1;
		new_line[j] = c;
		prev_c = c;
		++j;
	}
	new_line[j] = '\0';
}
