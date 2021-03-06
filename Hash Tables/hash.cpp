
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Profiler.h"


Profiler profiler("hash");
int m = 10007;
int k=10;
int searchCount;
int arrayFound[10007], arrayNotFound[10007];
int avg_found, avg_notFound, max_found, max_notFound;


#pragma warning(disable : 4996)
struct entity {
	int  id;
	char  name[30];
};
entity T[10007];



int hashFunction(int id, int i) {
	
		return (id + 7 * i + 113 * i * i) %m ;
}

int hashInsert(entity T[], int k, char string[30]) {
	int j,i = 0;
	do {
		 j = hashFunction(k,i);
		if (T[j].id == NULL) {
			T[j].id = k;
			strcpy(T[j].name, string);
			return j;
		}
		else i++;
	}while (i != m);


	
}



int hashSearch(entity T[], int k) {
	searchCount = 0;
	int i = 0;
	int j;
	do {
		searchCount ++;

		 j = hashFunction(k,i);
		if (T[j].id == k) return j;
		i++;
	} while (T[j].id != 0 && i <= m);

	return NULL;
}

void solve(int alpha) {
	avg_found = 0;
	max_found = 0;
	avg_notFound = 0;
	max_notFound = 0;

	char c[15] = "clatite";
	int inc = 0;

	FillRandomArray(arrayFound,m *alpha / 100, 1, 15000, true, 0);
	for (int i = 0; i < m; i++)
		T[i].id = 0;

	for (int i = 0; i < m * alpha / 100; i++) {
		hashInsert(T, arrayFound[i], c);
	}
	for (int j = 0; j < 5; j++) 
	{

		for (int i = 0; i <= 1500; i++) {
			avg_found += searchCount;
			int r = hashSearch(T, arrayFound[ m * alpha / 100 - 1 - 2 * i]);
			if (max_found < searchCount) {
				max_found = searchCount;
			}
		}
		for (int i = 15001; i < 16501; i ++) {
			int r = hashSearch(T, i);
			avg_notFound += searchCount;
			if (max_notFound < searchCount) {
				max_notFound = searchCount;
			}
		}
	}
	/*else {
		if (max_notFound < searchCount) {
			max_notFound = searchCount;
			avg_notFound += searchCount;
			avg_notFound++;
		}
	}*/
	

	printf(" %d \t\t| %.2lf\t\t\t| %d\t\t\t| %.2lf\t\t\t| %d\n", alpha,avg_found * 1.0 / 7500, max_found, avg_notFound * 1.0 / 7500, max_notFound);


}
int main()
{
	

	int demo;
	printf("want demo? \n");
	scanf_s("%d", &demo);
	if (demo == 1) {
		char c[15] = "clatite";
		char q[15] = "papanasi";
		char w[15] = "briose";
		for (int j = 1; j <= 4; j++) {
			hashInsert(T, j, c);
		}
		for (int j = 5; j <= 15; j++) {
			hashInsert(T, j, q);
		}
		for (int j = 16; j <= 20; j++) {
			hashInsert(T, j, w);
		}

		for (int i = 0; i <= 10007; i++) {
			if (T[i].id != NULL) {
				printf("at position %d there is key %d with the name %s \n\n\n", i, T[i].id, T[i].name);
			}
		}
	}

	printf(" alpha \t\t| avg found \t\t| max found \t\t| avg not found \t| max not found\n");
	solve(80);
	//profiler.showReport();
	solve(85);
	solve(90);
	solve(95);
	solve(99);
}

