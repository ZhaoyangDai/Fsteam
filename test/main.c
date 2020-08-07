#include <stdio.h>

int main(int argc, const char *argv[])
{
	int sub;
	int a = 10 ,b = 30;
	sub = add_val(&a + &b);
	printf("%d\n",sub);
	return 0;
}
