#include <stdio.h>

char *mystrstr(char *haystack, char *needle);
char *mystrcpy(char *dest, char *src);
char *mystrcat(char *dest, char *src);
int mystrcmp(char *s1, char *s2);
int main(void)
{
	char *p1 = "llab";
	char *p2 = "lla";
	char *ret = NULL;
	char str[100] = "good morning";
	char str2[] = "hello";

	ret = mystrstr(p1, p2);
	if (ret == NULL)
		printf("%s没有%s\n", p1, p2);
	else
		printf("%s\n", ret);

	printf("%s\n", mystrcpy(str, str2));

	printf("%s\n", mystrcat(str, str2));

	printf("%d\n", mystrcmp(p1, p2));

	return 0;
}

// 字符串中找子串
char *mystrstr(char *haystack, char *needle)
{
	char *hay_next, *needle_next;

	while (*haystack) {
		if (*haystack == *needle) {
			hay_next = haystack+1;	
			needle_next = needle+1;
			while (*needle_next != '\0') {
				if (*hay_next != *needle_next)
					break;
				hay_next++;
				needle_next++;
			}
			if (*needle_next == '\0')
				return haystack;
		}
		haystack ++;		
	}
	return NULL;
}

char *mystrcpy(char *dest, char *src)
{
	char *ret = dest;
	
	while ((*dest = *src) != '\0') {
		dest ++;
		src ++;
	}

	return ret;
}

char *mystrcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest != '\0')
		dest ++;
	mystrcpy(dest, src);

	return ret;
}

int mystrcmp(char *s1, char *s2)
{
#if 0
	while (*s1 != '\0' || *s2 != '\0') {
		if (*s1 != *s2)
			return *s1 - *s2;
		s1 ++;
		s2 ++;
	}

	return 0;
#endif
	while (*s1 == *s2) {
		if (!*s1)
			return 0;
		s1 ++;
		s2 ++;
	}
	return *s1 - *s2;
}


