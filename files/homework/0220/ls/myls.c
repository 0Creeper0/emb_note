#include <stdio.h>
#include <unistd.h>

#include "mystat.h"

// -a -i -l -d
int main(int argc, char *argv[])
{
	struct stat statbuf;
	int ch;

	char *optstring = "-ail:d";
	while (1)
	{
		ch = getopt(argc, argv, optstring);
		if (ch == -1)
			break;
		switch (ch)
		{
			case 'a':
				break;
			case 'i':
				break;
			case 'l':
				if (optarg != NULL)
					display_dir(optarg);
				break;
			case 'd':
				break;
			case '?':
				printf("error\n");
				break;
			case 1:
				if (optarg != NULL)
					puts(optarg);
				break;
			default:
				break;
		}
	}

	return 0;
}
