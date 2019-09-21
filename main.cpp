#include <stdio.h>
#include <stdlib.h>
#include "header/method.h"

#define INFOMAP 0x1
#define LPA 0x2
#define WALKTRAP 0x3

int main(){
	char splite[100];
	int mothed = WALKTRAP;
	char name[80] = "Fakedata_1000_500_10_100_10";

  printf("please input mothed code and file name: \n");
  scanf("%d %s", &mothed, name);

	sprintf(splite,"%s_SingleA_E10000.txt", name);
	const char* path = splite;

	switch (mothed)
	{
	case INFOMAP:
		printf("results obtained by method infomap \n");
		infomap(path);
		break;
	case LPA:
		printf("results obtained by mothed labelpropagation \n");
		labelpropagation(path);
		break;
	case WALKTRAP:
		printf("results obtained by mothed walktrap \n");
		walktrap(path);
		break;
	default:
		printf("input error!\n");
		exit(0);
	}

  return 0;
}