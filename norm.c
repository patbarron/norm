#include <stdio.h>
#include <stdlib.h>

/* max number of founds in an event - anything more than this is
 * considered to be unreasonable/unlikely
 * */
#define NROUNDS 20

/* number of titles available (must correspond to values initialized in
 * titles, norm_titles, and norm_awarded arrays
 * */
#define NTITLES 7

void main(int argc, char *argv[])
{
	int round[NROUNDS];
	int num_rounds;
	float score;
	int num_unplayed = 0;
	char *titles[] = { "4", "3", "2", "1", "C", "M", "S" };
	int norm_levels[] = { 1200, 1400, 1600, 1800, 2000, 2200, 2400 };
	int norm_awarded[] = { 0, 0, 0, 0, 0, 0, 0 };
	int i, j, k; /* generic loop counter */
	int rating_diff; /* difference between opponent's rating and title level rating */
	float cr; /* win expectancy for a given round */
	float ct; /* sum of all win expectancies in a round */


	/* Basic checks to see if command line is reasonable */
	if (argc == 1) {
		fprintf(stderr,"Usage: %s result rating1 rating2 rating3 ...\n", argv[0]);
		exit(1);
	}
	if (argc < 6) {
		fprintf(stderr, "%s: tournament must have at least 4 rounds\n", argv[0]);
		exit(1);
	}
	if (argc > NROUNDS + 2) {
		fprintf(stderr, "%s: tournament must have less than %d rounds\n", argv[0], NROUNDS);
	}
	num_rounds = argc - 2;
	score = atof(argv[1]);
	for (i = 2; i < argc; i++ ) {
		round[i-2] = atoi(argv[i]);
		if (round[i-2] == 0) num_unplayed++;
	}
	if (num_unplayed > 1) {
		fprintf(stderr, "%s: can't have more than 1 unplayed round\n", argv[0]);
		exit(1);
	}
	for (i = 0; i < NTITLES; i++) {
		ct = 0.0;
		for (j = 0; j < num_rounds; j++) {
			if (round[j] == 0) break;
			rating_diff = norm_levels[i] - round[j];
			if (rating_diff <= -400) cr = 0.0;
			else if ((-400 < rating_diff) && (rating_diff <= 0)) cr=0.5+(((float)rating_diff)/800.0);
			else if ((0 < rating_diff) && (rating_diff <= 200)) cr=0.5+(((float)rating_diff)/400.0);
			else cr = 1.0;
			ct += cr;
		}
		if (((score - ct) > (1.0 + (float)num_unplayed))) norm_awarded[i] = 1;
	}
	/* Count down backwards through the list of titles, print the
	 * highest norm awarded.  There could be other, lower norms
	 * awarded too, but we don't care about those - we only print
	 * the highest.
	 * */
	for (i = NTITLES-1; i >= 0; i--) {
		if (norm_awarded[i] == 1) {
			printf("%s\n", titles[i]);
			break;
		}
	}
}

