#include <stdio.h>
int add_val(int *a,int *b)
{
	return(*a + *b);
}
int main(int argc, const char *argv[])
{
	int a = 9,b = 10; 
	int add = add_val(&a,&b);
	printf("hello world\n");
	printf("add = %d\n",add);
	return 0;
}
