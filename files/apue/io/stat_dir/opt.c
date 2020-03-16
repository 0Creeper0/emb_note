#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// -a -i -l -d
int main(int argc, char *argv[])
{
	// -开头非选项参数(1) :带参数的选项　::可选择参数
	char *optstring = "-a:il::d";
	int ch;
	struct option opt[] = {
		{"help", no_argument, NULL, 'h'},
		{"version", optional_argument, NULL, 'v'},
		{NULL, 0, NULL, 0}
	};

	while (1) {
		//ch = getopt(argc, argv, optstring);
		ch = getopt_long(argc, argv, optstring, opt, NULL);
		if (ch == -1) {
			break;
		}
		switch (ch) {
			case 'a':
				printf("-a......\n");
				printf("argument:%s\n", optarg);
				break;
			case 'd':
				printf("-d.....\n");
				break;
			case 'l':
				printf("-l.....\n");
				if (optarg != NULL) {
					printf("optional arg:%s\n", optarg);
				}
				break;
			case 'i':
				printf("-i.....\n");
				break;
			case '?':
				printf("i don't know\n");
				break;
			case 1:
				printf("argument:%s\n", optarg);
				break;
			case 'h':
				printf("help document\n");
				break;
			case 'v':
				printf("version info\n");
				if (optarg != NULL)
					printf("args:%s\n", optarg);
				break;
			default:
				break;
		}
	}

	return 0;
}

