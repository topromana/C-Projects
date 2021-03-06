
/*
We notice that when varying the number of arrays received, for small numbers of arrays the differences regarding the
amount of comparisons and assignments will not be that big, but for larger amounts of arrays the difference will be considerable.

we have an array of lists, and then we will put the elements of the lists of that array in turns into the heap, and swap the first 
list with the last one.
the complexity will be O(heapsize*n*logHeapsize)

	
*/
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Profiler.h"


Profiler profiler("merging");

struct element {
	int listIndex;
	int value;
	element *nextElement;
};

struct listOfElements {
	element *first;
	element *last;
	int length;
};

listOfElements elem[1001],emptyListOfElements;
int k, hsize, rez[100000001], lrez, assign, comp, x[10002];


void addElem(int listIndex, int value) {
	element *e = new element;
	e->listIndex = listIndex;
	e->value = value;
	if (elem[listIndex].length == 0)
		elem[listIndex].first = elem[listIndex].last = e;
	else {
		elem[listIndex].last->nextElement = e;
		elem[listIndex].last = e;
	}
	elem[listIndex].length++;

}

void heapify(int poz)
{
	int bst = poz;
	comp += 2;
	if (2 * poz + 1 <= hsize && elem[2 * poz + 1].first->value < elem[poz].first->value)
		bst = 2 * poz + 1;
	if (2 * poz + 2 <= hsize && elem[2 * poz + 2].first->value < elem[bst].first->value)
		bst = 2 * poz + 2;
	if (bst != poz) {
		listOfElements aux;
		assign += 3;
		aux = elem[poz];
		elem[poz] = elem[bst];
		elem[bst] = aux;
		heapify(bst);
	}
}

void bottomUp()
{
	for (int i = hsize / 2; i >= 0; i--) {
		heapify(i);
	}
}


void solve()
{
	int ec = 0;
	hsize = k - 1;
	bottomUp();
	for (int i = 0; i < k; i++)
		ec += elem[i].length;

	while (ec)
	{
		rez[lrez++] = elem[0].first->value;
		element *e;
		e = elem[0].first;
		elem[0].length--;
		if (elem[0].length)
			elem[0].first = elem[0].first->nextElement;
		else
		{
			listOfElements aux;
			aux = elem[0];
			elem[0] = elem[hsize];
			elem[hsize] = aux;
			hsize--;
		}
		free(e);
		heapify(0);
		ec--;
	}
}

void average() {
	k = 5;
	for (int n = 100; n < 10000; n += 100) {
		for (int i = 0; i < k; i++){
				FillRandomArray(x, n / k, 0, 15000, false, 1);
				for (int j = 0; j < n / k; j++)
					addElem(i, x[j]);
			}
			assign = 0;
			comp = 0;
			solve();
			profiler.countOperation("k5", n, assign + comp);
		
	}
	k = 10;
	for (int n = 100; n < 10000; n += 100) {
		for (int i = 0; i < k; i++) {
			FillRandomArray(x, n / k, 0, 15000, false, 1);
			for (int j = 0; j < n / k; j++)
				addElem(i, x[j]);
		}
		assign = 0;
		comp = 0;
		solve();
		profiler.countOperation("k10", n, assign+comp);

	}

	k = 100;
	for (int n = 100; n < 10000; n += 100) {
		for (int i = 0; i < k; i++) {
			FillRandomArray(x, n / k, 0, 15000, false, 1);
			for (int j = 0; j < n / k; j++)
				addElem(i, x[j]);
		}
		assign = 0;
		comp = 0;
		solve();
		profiler.countOperation("k100", n, assign+comp);

	}
	int n = 10000;
	for (k = 10; k <= 500; k += 10)
	{
		for (int i = 0; i < k; i++)
		{
			FillRandomArray(x, n / k, 0, 15000, false, 1);
			for (int j = 0; j < n / k; j++)
				addElem(i, x[j]);
		}
		assign = 0;
		comp = 0;
		solve();
		profiler.countOperation("n10000", k, assign+comp);
	}
	profiler.createGroup("when k varies", "k5", "k10", "k100");
	profiler.createGroup("n is 10000", "n10000");


		
}

int main()
{
	int demo;
	printf("want to see the demo?\n");
	scanf_s("%d", &demo);
	if (demo == 1) {
		k = 5 + rand() % 5;
		for (int i = 0; i < k; i++)
		{
			int n = 2 + rand() % 8;
			FillRandomArray(x, n, 0, 10, false, 1);

			printf("elem in list %d ", i);
			for (int j = 0; j < n; j++)
			{
				addElem(i, x[j]);
				printf("%d ", x[j]);
			}
			printf("\n");
		}
		printf("\n\n");
		solve();

		for (int i = 1; i < lrez; i++)
			printf("%d ", rez[i]);
	}
	
	average();
	profiler.showReport();
}

