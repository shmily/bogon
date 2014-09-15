
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define MAX_LEN		(128)


void pre_process(const char *in, char *out);
void longest_palindrome(const char *str);

int main(void)
{
	char in[MAX_LEN] = {0};
	char *tmp;

	while (scanf("%s", in)!=EOF) {

		tmp = malloc(strlen(in)*2+4);
		pre_process(in, tmp);

		printf("%s\n", tmp);
		longest_palindrome(tmp);
	}

	return 0;
}

/*
 * "abc" -> "^#a#b#c#$"
 */
void pre_process(const char *in, char *out)
{
	int len = strlen(in);

	*(out++) = '^';
	if (len==0) goto _out;

	for (int i=0; i<len; i++) {
		*(out++) = '#';
		*(out++) = *(in++);
	}

_out:
	*(out++) = '$';
	*(out++) = '\0';
	return;
}

void longest_palindrome(const char *str)
{
	int length = strlen(str);
	int *rad = malloc(sizeof(int)*length);
	int mx=0, id=0;

	memset(rad, 0, sizeof(int)*length);
	for (int i=1; i<length-1; i++) {
		rad[i] = mx > i ? min(rad[2*id-i], mx-i) : 1;
		while (str[i+rad[i]] == str[i-rad[i]]) rad[i]++;
		if (i+rad[i] > mx) {
			mx = i + rad[i];
			id = i;
		}

		printf("%d ", rad[i]);
	}
}
