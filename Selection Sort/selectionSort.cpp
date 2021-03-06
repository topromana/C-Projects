


#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"


Profiler profiler("sortari");

int assign, comp;


void selectionSort(int a[], int n) {
	int i, j, pos, buff;
	for (i = 0; i < n - 1; i++) {
		pos = i;
		for (j = i + 1; j < n; j++) {
			comp++;
			if (a[j] < a[pos]) pos = j;
		}
		buff = a[pos];
		a[pos] = a[i];
		a[i] = buff;
		assign = assign + 3;

	}
}

void printString(int a[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", a[i]);
	}
	printf("\n");
}
void selectionSortPasi(int a[], int n) {
	int i, j, pos, buff;
	for (i = 0; i < n - 1; i++) {
		printf("la pasul %d ",i);
		pos = i;
		for (j = i + 1; j < n; j++) {
			comp++;
			if (a[j] < a[pos]) pos = j;
		}
		buff = a[pos];
		a[pos] = a[i];
		a[i] = buff;
		assign = assign + 3;
		printString(a, n);

	}
}

void average(int inc, int max_x) {
	for (int n = inc; n < max_x; n += inc) {
		assign = 0;
		comp = 0;
		int *a = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < 5; j++) {
			FillRandomArray(a, n, 100, 1000, true);
			selectionSort(a, n);
		}

		profiler.countOperation("avg_sel_a", n, assign / 5);
		profiler.countOperation("avg_sel_c", n, comp / 5);
		profiler.countOperation("avg_sel_c+a", n, (assign + comp) / 5);
	}
	profiler.addSeries("avg_sel_a", "avg_sel_c", "avg_sel_c+a");
	profiler.createGroup("toate trei de la avg grupate", "avg_sel_a", "avg_sel_c", "avg_sel_c+a");
}
void best(int inc, int x_max) {
	for (int n = inc; n < x_max; n += inc) {
		int *a = (int *)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			a[i] = i;
		}
		assign = 0;
		comp = 0;
		selectionSort(a, n);
		profiler.countOperation("Best_sel_a", n, assign);
		profiler.countOperation("Best_sel_c", n, comp);
		profiler.countOperation("Best_sel_c+a", n, assign + comp);
	}
	profiler.addSeries("Best_sel_a", "Best_sel_c", "Best_sel_c+a");
	profiler.createGroup("toate trei de la best grupate", "Best_sel_a", "Best_sel_c", "Best_sel_c+a");
}

void worst(int inc, int max_x) {
	for (int n = inc; n < max_x; n += inc) {
		int *a = (int *)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			a[i] = n - i;
		}
		assign = 0;
		comp = 0;
		selectionSort(a, n);
		profiler.countOperation("worst_sel_a", n, assign);
		profiler.countOperation("worst_sel_c", n, comp);
		profiler.countOperation("worst_sel_c+a", n, assign + comp);
	}
	profiler.addSeries("worst_sel_a", "worst_sel_c", "worst_sel_c+a");
	profiler.createGroup("toate trei de la worst grupate", "worst_sel_a", "worst_sel_c", "worst_sel_c+a");
}

int main()
{
	int test;
	printf("want to see how it sorts?\n");
	scanf_s("%d", &test);
	if (test == 1) {
		int n = 5;
		int i, a[100];
		for (i = 0; i < n; i++)
			scanf_s("%d", &a[i]);
		selectionSortPasi(a, n);
		for (i = 0; i < n; i++)
			printf("%d ", a[i]);
		printf("\n assign si comp %d %d", assign, comp);
	}
	best(10, 100);
	average(10, 100);
	worst(10, 100);
	profiler.createGroup("cele 3 assign grupate", "worst_sel_a", "Best_sel_a", "avg_sel_a");
	profiler.createGroup("cele 3 comp grupate", "worst_sel_c", "Best_sel_c", "avg_sel_c");
	profiler.createGroup("cele 3 assign si comp grupate", "worst_sel_c+a", "Best_sel_c+a", "avg_sel_c+a");
	
	profiler.showReport();
}
