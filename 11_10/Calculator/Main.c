#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cal_priority(char operation)
{
	switch (operation)
	{
		case '+':
		case '-':return 1;
		case '*':
		case '/':return 2;
		default:return -1;
	}
}





int main(int argc, char const *argv[])
{
	return 0;
}