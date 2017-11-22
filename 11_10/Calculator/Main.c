#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cal_priority(char operation)
{
	switch (operation)
	{
		case '+':
		case '-':return 1;break;
		case '*':
		case '/':return 2;break;
		default:return -1;break;
	}
}


int main(int argc, char const *argv[])
{
	
	return 0;
}