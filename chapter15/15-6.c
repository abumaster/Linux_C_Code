#include "apue.h"
#include <ctype.h>
/* 将大写字符转换成小写字符的过滤程序 */

int main(void)
{
	int c;
	while ((c = getchar()) != EOF) {
		if (isupper(c)) // 大写
			c = tolower(c);
		if (putchar(c) == EOF)
			err_sys("output error");
		if (c=='\n')
			fflush(stdout);
	}

	exit(0);
}
