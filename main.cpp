#include <stdio.h>
#include <stdlib.h>
#include "infomap.h"
#include "labelpropagation.h"
#include "walktrap.h"

#define INFOMAP 0x1
#define LPA 0x2
#define WALKTRAP 0x3

int main(){
	char splite[100];
	int mothed = WALKTRAP;

	const char* name = "MC";
	const char* intercept = "E"; 
	const int number = 10000;
	const char* nodetype = "A";

	sprintf_s(splite, 100, "%s_%s_%s%d.txt", name, nodetype, intercept, number);
	const char* path = splite;

	switch (mothed)
	{
	case INFOMAP:
		infomap(path);
		printf("results obtained by method infomap \n");
		break;
	case LPA:
		labelpropagation(path);
		printf("results obtained by mothed labelpropagation \n");
		break;
	case WALKTRAP:
		walktrap(path);
		printf("results obtained by mothed walktrap \n");
		break;
	default:
		printf("未定义的方法\n");
		exit(0);
	}

	system("pause");
}
