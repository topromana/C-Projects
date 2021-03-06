/*

The TopDown approach has O(nlogn) complexity, and BottomUp has O(n);
Chart Analysis:
Average case: the results were obtained by analyzing the graphics in the average case on 5 random arrays with sizes from 100 to 1000
By analyzing the graphics we observe that both assignment-wise and comparrison-wise the BottomUp approach behaves better than the TopDown.
Worst case: the results are obtained on arrays that are ordered ascending;
By analyzing the graphics we observe that both comparisson and assignment wise the BottomUp approach behaves better;


*/


#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler profiler("heaps");


int assignBottomUp, compBottomUp, assignTopDown, compTopDown;
int heapSize;


void printArray(int *a, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
}
void maxHeapify(int *a, int i) {
	int l = 2 * i + 1;

	int max;
	int r = 2 * i + 2;
	compBottomUp++;
	if (l < heapSize && a[i] < a[l]) {


		max = l;

	}

	else {
		max = i;

	}
	compBottomUp++;
	if (r < heapSize && a[r] > a[max]) {

		max = r;

	}
	if (max != i) {
		int aux = a[max];
		a[max] = a[i];
		a[i] = aux;
		assignBottomUp += 3;
		maxHeapify(a, max);
	}
}


void buildMaxHeap(int *a, int arraySize) {//bottomup
	heapSize = arraySize;
	assignBottomUp++;
	for (int i = arraySize / 2 - 1; i >= 0; i--)
		maxHeapify(a, i);

}

void buildMaxHeapSteps(int *a, int arraySize) {//bottomup
	heapSize = arraySize;
	for (int i = arraySize / 2 - 1; i >= 0; i--) {
		printf("\n la pasul %d:  ", i);
		printArray(a, arraySize);
		maxHeapify(a, i);
	}

}


void heapsort(int *a, int arraySize) {
	buildMaxHeap(a, arraySize);
	for (int i = arraySize - 1; i >= 1; i--) {
		printArray(a, arraySize);
		printf("\n");
		int aux = a[i];
		a[i] = a[0];
		a[0] = aux;
		heapSize--;
		maxHeapify(a, 0);
	}

}

int parent(int i) {
	if (i % 2 == 1)
		return i / 2;
	else
		return i / 2 - 1;
}

void heapIncreaseKey(int *a, int i, int key) {

	compTopDown++;
	if (key < a[i])
		printf("\nerror new key smaller than current key\n");
	a[i] = key;
	assignTopDown++;
	while (i > 0 && a[parent(i)] < a[i]) {
		compTopDown++;
		int aux = a[i];
		a[i] = a[parent(i)];
		a[parent(i)] = aux;
		assignTopDown += 3;
		i = parent(i);
	}
	compTopDown++;

}
void maxHeapInsert(int *a, int key) {
	heapSize++;
	a[heapSize - 1] = -999;
	assignTopDown++;
	heapIncreaseKey(a, heapSize - 1, key);
}
void buildMaxHeap2(int *a, int arraySize) {
	heapSize = 1;
	assignTopDown++;
	for (int i = 1; i < arraySize; i++)
		maxHeapInsert(a, a[i]);
}

void buildMaxHeap2Steps(int *a, int arraySize) {
	heapSize = 1;
	assignTopDown++;
	for (int i = 1; i < arraySize; i++) {
		
		printf("\n la pasul %d:  ", i);
		printArray(a, arraySize);
		maxHeapInsert(a, a[i]);
	}
}


void average(int inc, int max_x) {
	for (int n = inc; n < max_x; n += inc) {
		
		int *a = (int *)malloc(n * sizeof(int));
		assignBottomUp = 0;
		assignTopDown = 0;
		compBottomUp = 0;
		compTopDown = 0;
		for (int j = 0; j < 5; j++) {
			FillRandomArray(a, n, 100, 1000, true);
			buildMaxHeap(a, n);

		}
		for (int j = 0; j < 5; j++) {
			FillRandomArray(a, n, 100, 1000, true);
			buildMaxHeap2(a, n);

		}

		profiler.countOperation("avg_TopDown_c", n, compTopDown / 5);
		profiler.countOperation("avg_BottomUp_c", n, compBottomUp / 5);
		profiler.countOperation("avg_TopDown_a", n, assignTopDown / 5);
		profiler.countOperation("avg_BottomUp_a", n, assignBottomUp / 5);
		profiler.countOperation("avg_TopDown_c+a", n, (assignTopDown + compTopDown)/ 5);
		profiler.countOperation("avg_BottomUp_c+a", n, (assignBottomUp + compBottomUp) / 5);
		
	}
	
	profiler.createGroup("average comp", "avg_TopDown_c", "avg_BottomUp_c");
	profiler.createGroup("average assign", "avg_TopDown_a", "avg_BottomUp_a");
	profiler.createGroup("average comp+assign", "avg_TopDown_c+a", "avg_BottomUp_c+a");
}
void worst(int inc, int x_max) {
	for (int n = inc; n < x_max; n += inc) {
		int *a = (int *)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			a[i] = i;
		}
		assignBottomUp = 0;
		assignTopDown = 0;
		compBottomUp = 0;
		compTopDown = 0;
		buildMaxHeap(a, n);
		for (int i = 0; i < n; i++) {
			a[i] = i;
		}
		buildMaxHeap2(a, n);
		
		
		profiler.countOperation("worst_TopDown_a", n, assignTopDown);
		profiler.countOperation("worst_TopDown_c", n, compTopDown);
		profiler.countOperation("worst_TopDown_c+a", n, assignTopDown + compTopDown);
		profiler.countOperation("worst_BottomUp_a", n, assignBottomUp);
		profiler.countOperation("worst_BottomUp_c", n, compBottomUp);
		profiler.countOperation("worst_BottomUp_c+a", n, assignBottomUp+compBottomUp);
		
	}
	
	profiler.createGroup("worst assign", "worst_BottomUp_a", "worst_TopDown_a");
	profiler.createGroup("worst comp", "worst_BottomUp_c", "worst_TopDown_c");
	profiler.createGroup("worst assign+comp", "worst_BottomUp_c+a", "worst_TopDown_c+a");
}

int main()
{
	int demo;
	printf("want to see demo? \n");
	scanf_s("%d", &demo);
	if (demo == 1) {
		int arr1[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 }, n = 10;
		int arr2[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };

		int arr3[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };



		for (int i = 0; i < 10; i++)
			printf("%d ", arr1[i]);
		printf("\n");

		buildMaxHeapSteps(arr1, 10);
		printf("dupa buttomup\n");
		for (int i = 0; i < 10; i++)
			printf("%d ", arr1[i]);
		printf("\n\n");


		for (int i = 0; i < 10; i++)
			printf("%d ", arr2[i]);
		printf("\n");

		heapsort(arr2, 10);
		printf("dupa heapsort \n");
		for (int i = 0; i < 10; i++)
			printf("%d ", arr2[i]);
		printf("\n\n");


		for (int i = 0; i < 10; i++)
			printf("%d ", arr3[i]);
		printf("\n");

		buildMaxHeap2Steps(arr3, 10);
		printf("dupa topdown\n");
		for (int i = 0; i < 10; i++)
			printf("%d ", arr3[i]);
		printf("\n");
	}
	average(100, 1000);
	worst(100, 1000);
	profiler.showReport();
}





