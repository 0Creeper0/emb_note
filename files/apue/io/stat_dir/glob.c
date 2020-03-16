#include <stdio.h>
#include <glob.h>

int main()
{
	glob_t res;
	if (glob("/home/creeper/*", 0, NULL, &res) != 0)
		return 1;
	if (glob("/home/creeper/.*", GLOB_APPEND, NULL, &res) != 0)
		return 1;
	for (int i = 0; i < (int)(res.gl_pathc); i++)
		puts((res.gl_pathv)[i]);
	globfree(&res);
}
