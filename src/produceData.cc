#include "header/header.h"

int main(int argc, char const *argv[])
{
	int num;
	num = atoi(argv[1]);

	FILE *src;
	src = fopen("data.in","w+");

	srand((int)time(0));
	int temp;
	fprintf(src, "%d ",num);
	for (int i = 0; i < num; ++i)
	{
		/* code */
		temp = rand();
		fprintf(src,"%d ",temp);
	}

	fclose(src);
	return 0;
}