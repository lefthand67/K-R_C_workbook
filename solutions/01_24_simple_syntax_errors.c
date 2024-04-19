#include <stdio.h>

/*
 * simple syntax checker
 * looks for unbalances braces, parentheses, et.
 */

#define IN 1
#define OUT 0

int main()
{
	/* set the list of chars to check */
	char char_set[] = { '(', ')', '[', ']', '{', '}', '\'', '\'', '"', '"' };
	/* count the length of this array */
	int length = sizeof(char_set) / sizeof(char_set[0]);

	int c, prev_c, state;
	char unbalanced_char;
	int i, diff;			/* i for loops, and diff for comparison of number of chars */
	int found_problems;		/* see final print statement */
	int check_list[length]; /* count occurences array */

	/* initialize check_list with 0s */
	for (i = 0; i < length; ++i)
		check_list[i] = 0;

	/* count all the occurences of char pairs */
	prev_c = -1;
	state = OUT; /* start check as non-comment */
	while ((c = getchar()) != EOF) {

		/* we are not in comment yet */
		if (state == OUT) {

			/* check for comment */
			if (prev_c == '/' && c == '*') { /* comment starts */
				state = IN;
				continue; /* do not save * in prev_c */
			}
			/* ignore quotes as quoted chars */
			if ((prev_c == '\\' && c == '\'') || (prev_c == '\'' && c == '"'))
				continue;

			/* populate chars array witn new entries count */
			for (i = 0; i < length; ++i)
				if (c == char_set[i])
					++check_list[i];
		}

		/* we are in comment */
		else if (state == IN) {
			if (prev_c == '*' && c == '/') { /* comment ends */
				state = OUT;
				continue; /* do not save / in prev_c */
			}
		}
		prev_c = c;
	}

	/* check comment { ( */

	found_problems = 0;
	for (i = 0; i < length; i += 2) {
		// printf("%c: %d, %c:  %d\n", char_set[i], check_list[i], char_set[i + 1], check_list[i + 1]);
		/* check quotes */
		if (char_set[i] == '\'' || char_set[i] == '"') {
			if ((diff = check_list[i] % 2) != 0)
				unbalanced_char = char_set[i];
		} else {
			if ((diff = check_list[i] - check_list[i + 1]) < 0)
				unbalanced_char = char_set[i + 1];
			else if (diff > 0)
				unbalanced_char = char_set[i];
		}
		if (diff) {
			found_problems = 1;
			printf("Unbalanced %c\n", unbalanced_char);
		}
	}
	if (!found_problems)
		printf("No problems found.\n");
	printf("Check is done.\n");
}
