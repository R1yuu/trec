#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POS_ST "START_TIME"
#define POS_ST_DESC "When you started working"

#define OPT_H "-h"
#define OPT_B "-b B"
#define OPT_O "-o O"

#define OPT_H_DESC "Show this help message and exit"
#define OPT_B_DESC "Time spent during break"
#define OPT_O_DESC "Accumulated over-/undertime"

#define USAGE "trec [" OPT_H "] [" OPT_B "] [" OPT_O "] " POS_ST
#define DESC "Calculate when you can go home from work."

static inline void
help(int status)
{
	printf("usage: %s\n\n"
		   "%s\n\n"
		   "positional arguments:\n"
		   "  %-12s%s\n\n"
		   "options:\n"
		   "  %-12s%s\n  %-12s%s\n  %-12s%s\n\n",
		   USAGE, DESC, POS_ST, POS_ST_DESC, OPT_H, OPT_H_DESC, OPT_B,
		   OPT_B_DESC, OPT_O, OPT_O_DESC);
	exit(status);
}

static inline long
parse_num(const char* s, char** e)
{
	long res = 0;
	errno = 0;
	res = strtol(s, e, 10);
	if (errno) {
		perror("Couldn't parse number.");
		exit(1);
	};
	return res;
}

int
main(int argc, char* argv[])
{
	long hh = 0;
	long mm = 0;
	long b = 0;
	long o = 0;

	if (argc == 1) {
		help(1);
	}

	/* Parse args */
	for (unsigned i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h':
				help(0);
				break;
			case 'b': {
				i++;
				char* be = argv[i] + (strlen(argv[i]) - 1);
				b = parse_num(argv[i], &be);
				break;
			}
			case 'o': {
				i++;
				char* oe = argv[i] + (strlen(argv[i]) - 1);
				o = parse_num(argv[i], &oe);
				break;
			}
			default:
				help(1);
				break;
			}
		} else {
			char* cln = strchr(argv[i], ':');
			if (cln) {
				char* he = cln - 1;
				char* me = cln + (strlen(cln) - 1);
				hh = parse_num(argv[i], &he);
				mm = parse_num(cln + 1, &me);
			}
			if (!cln || hh < 0 || mm < 0) {
				perror("Couldn't parse time. Use Format: hh:mm");
				exit(1);
			}
			break;
		}
	}

	mm += 42 + b - o;
	hh += 7 + mm / 60;
	mm %= 60;

	printf("%ld:%ld\n\n", hh, mm);

	return 0;
}
