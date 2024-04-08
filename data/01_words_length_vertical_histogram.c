#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_WORDS 100

/* draw histograms of the words' length */
int main()
{
	int c, i, j, state, prev_c;
	int nw;				  /* count number of words */
	int longest_word_idx; /* the longest length for print */
	int upper_limit;	  /* the highest point of the plot */
	int upper_limit_copy; /* copy for plotting */
	int words[MAX_WORDS]; /* container for lengths of words */

	state = OUT;
	prev_c = -1;
	nw = longest_word_idx = 0;

	/* initialize lengths with 0s */
	for (i = 0; i < MAX_WORDS; ++i)
		words[i] = 0;

	while ((c = getchar()) != '\n') {

		/* check for maximum number of words */
		if (nw > MAX_WORDS) {
			printf("Maximum words limit (%d words) reached, sorry", MAX_WORDS);
			break;
		}

		/* check end of a word and skip blanks */
		if (c == ' ' || c == '\t') {
			if (prev_c == ' ' || prev_c == '\t')
				continue;
			state = OUT;

		} else if (state == OUT) { /* starting a new word */
			state = IN;
			++nw;
		}

		/* increment length */
		if (state == IN) {
			if (c != ',' && c != '.' && c != '!' && c != '?')
				++words[nw - 1];
			/* save current char for next check */
			prev_c = c;
		}
	}

	/* update longest_word_idx variable */
	for (i = 0; i < nw; ++i) {
		if (words[longest_word_idx] < words[i])
			longest_word_idx = i;
		// printf("Word %d: %d\n", i, words[i]);
	}

	upper_limit = upper_limit_copy = words[longest_word_idx];
	for (i = 0; i < upper_limit; ++i) {
		for (j = 0; j < nw; ++j) {
			// printf("Word number: %d, Words[j]: %d\n", j, words[j]);
			if (upper_limit_copy == words[j]) {
				printf("*");
				--words[j];
			} else
				printf(" ");
		}
		--upper_limit_copy;
		printf("\n");
	}

	return 0;
}
