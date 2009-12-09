/*
 *  I saw a similar program on a BSD/OS 3.1 system.  Used it to exploit
 *  local security holes.
 */ 

#include <err.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

static void help();

int main(int argc, char *argv[]) 
{
	int c, nochdir = 1, noclose = 1;

	if(argc < 2)
		help();
	while((c = getopt(argc, argv, "cf")) != EOF)
		switch(c) {
		case 'c':
			nochdir = 0;
			break;
		case 'f':
			noclose = 0;
			break;
		default:
			help();
		}
	argc -= optind;
        argv += optind;  
	if (daemon(nochdir, noclose) == -1)
		err(1, "");
	execvp(argv[0], &argv[0]);
	err(1, "%s", argv[0]);
}

void help() {

	(void)fprintf(stderr, "\
usage: daemon [-cf] executable argv[1] ...\n");
	(void)exit(2);
}
