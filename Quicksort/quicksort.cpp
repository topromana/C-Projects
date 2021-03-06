/*
worst case quicksort
The worst case will ocuur when the partitioning will produce one subroblem with n-1 elements and one with 0 elements.
so, if the partitioning is unbalanced at every recursive level of the algorithm the running time is O(n^2).


best case quicksort
In the best case, partition produces the most even possible split, into 2 subproblems, each of size no more than n/2 (one n/2, the other n/2-1).
So, by equally balancing the 2 sides of the partition at every recursion, we will get O(nlogn) running time, which is way faster.


average case quicksort
In the average case, the combination of good and bad splits will produce three subarrays of sizes 0, (n-1)/2-1 and (n-1)/2.
So, the running time of quicksort in the average case will be just like in the best case, O(n log n) just with a bigger constant.

By analysing the graphics in the average case for heapsort and quicksort, we notice that both from the assignment and comparisons
point of view, the quicksort algorithm is better comparing to heapsort.

iterative versiion
we avoided function calls, since they are time consuming. I did not use the stack to store the data.
I passed only one item, the pivot, through a swap variable, only once/round.

*/

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Profiler.h"


Profiler profiler("sorts");
int heapSize, assignBottomUp, compBottomUp, compQuicksort, assignQuicksort;

void printArray(int *a, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
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
void heapsort(int *a, int arraySize) {
	buildMaxHeap(a, arraySize);
	for (int i = arraySize - 1; i >= 1; i--) {
		int aux = a[i];
		a[i] = a[0];
		a[0] = aux;
		heapSize--;
		maxHeapify(a, 0);
	}

}



int partition(int *a, int p, int r) {
	int x = a[r];
	assignQuicksort++;
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		compQuicksort++;
		if (a[j] <= x) {
			i++;
			int aux = a[i];
			a[i] = a[j];
			a[j] = aux;
			assignQuicksort += 3;
		}
	}
	int aux1 = a[i + 1];
	a[i + 1] = a[r];
	a[r] = aux1;
	assignQuicksort += 3;
	return i + 1;
}

int partitionBest(int *a, int p, int r) {
	int x = a[r];
	int m = (p + r + 1) / 2;
	int aux = a[m];
	a[m] = a[r];
	a[r] = aux;
	assignQuicksort += 4;
	
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		compQuicksort++;
		if (a[j] <= x) {
			i++;
			int aux = a[i];
			a[i] = a[j];
			a[j] = aux;
			assignQuicksort += 3;
		}
	}
	int aux1 = a[i + 1];
	a[i + 1] = a[r];
	a[r] = aux1;
	assignQuicksort += 3;
	return i + 1;
}

void quicksort(int *a, int p, int r){

	if (p < r) {
		int q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);

	}
}

void quicksortBest(int *a, int p, int r) {
	
	if (p < r) {
		int q = partitionBest(a, p, r);
		quicksortBest(a, p, q - 1);
		quicksortBest(a, q + 1, r);

	}
}

void quicksortSteps(int *a, int p, int r) {
	printArray(a, 9);
	compQuicksort++;
	if (p < r) {
		int q = partition(a, p, r);
		quicksortSteps(a, p, q - 1);
		quicksortSteps(a, q + 1, r);
		}
}


int random(int p, int r) {
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return p + rand() % ((r + 1) - p);
}
int randomizedPartition(int *a, int p, int r) {
	srand(time(0));
	int i = random(p, r);
	int aux = a[r];
	a[r] = a[i];
	a[i] = aux;
	return partition(a, p, r);
}


int randomizedSelect(int *a, int p, int r, int i) {
	if (p == r) return a[p];
	int q = randomizedPartition(a, p, r);
	int k = q - p + 1;
	if (i == k) return a[q];
	else if (i < k) return randomizedSelect(a, p, q - 1, i);
	else return randomizedSelect(a, q + 1, r, i - k);
}

void average(int inc, int max_x) {
	for (int n = inc; n < max_x; n += inc) {

		int *a1 = (int *)malloc(n * sizeof(int));
		int *a2 = (int *)malloc(n * sizeof(int));
		assignBottomUp = 0;
		compBottomUp = 0;
		assignQuicksort = 0;
		compQuicksort = 0;

		for (int j = 0; j < 5; j++) {
			FillRandomArray(a1, n, 100, 1000, true);
			for (int k = 0; k < n; k++) {
				a2[k] = a1[k];
			}
			quicksort(a2, 0, n - 1);
			heapsort(a1, n);


		}
		

		
		profiler.countOperation("avg_heapsort_c", n, compBottomUp / 5);
		profiler.countOperation("avg_heapsort_a", n, assignBottomUp / 5);
		profiler.countOperation("avg_heapsort_c+a", n, (assignBottomUp + compBottomUp) / 5);
		profiler.countOperation("avg_quicksort_c", n, compQuicksort / 5);
		profiler.countOperation("avg_quicksort_a", n, assignQuicksort/ 5);
		profiler.countOperation("avg_quicksort_c+a", n, (assignQuicksort + compQuicksort) / 5);

	}

	profiler.createGroup("average comp", "avg_heapsort_c", "avg_quicksort_c");
	profiler.createGroup("average assign", "avg_heapsort_a", "avg_quicksort_a");
	profiler.createGroup("average comp+assign", "avg_heapsort_c+a", "avg_quicksort_c+a");
}


void worst(int inc, int max_x) {
	for (int n = inc; n < max_x; n += inc) {

		int *a2 = (int *)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {

			a2[i] = n-i;
		}
		compQuicksort = 0;
		assignQuicksort = 0;
		quicksort(a2, 0, n - 1);



		profiler.countOperation("worst_quicksort_a", n, assignQuicksort);
		profiler.countOperation("worst_quicksort_c", n, compQuicksort);
		profiler.countOperation("worst_quicksort_c+a", n, assignQuicksort + compQuicksort);

	}
	profiler.createGroup("worst comp quicksort", "worst_quicksort_c");
	profiler.createGroup("worst assign quicksort", "worst_quicksort_a");
	profiler.createGroup("worst comp+assign quicksort", "worst_quicksort_c+a");

}

void best(int inc, int max_x) {
	for (int n = inc; n < max_x; n += inc) {
		int *a2 = (int *)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			a2[i] = i;
		}
		compQuicksort = 0;
		assignQuicksort = 0;

		quicksortBest(a2, 0, n - 1);
		profiler.countOperation("best_quicksort_a", n, assignQuicksort);
		profiler.countOperation("best_quicksort_c", n, compQuicksort);
		profiler.countOperation("best_quicksort_c+a", n, assignQuicksort + compQuicksort);
	}
	profiler.createGroup("best comp quicksort", "best_quicksort_c");
	profiler.createGroup("best assign quicksort", "best_quicksort_a");
	profiler.createGroup("best comp+assign quicksort", "best_quicksort_c+a");
}

void quicksortIt(int *a, int elem) {
#define MAX_LVL 1000
	int piv, start[MAX_LVL], end[MAX_LVL], i, l, r, aux;
	i = 0;
	start[0] = 0;
	end[0] = elem;
	while (i >= 0) {
		l = start[i];
		r = end[i] - 1;
		if (l < r) {
			piv = a[l];
			while (l < r) {
				while (a[r] >= piv && l < r) r--;
				if (l < r) a[l++] = a[r];
				while (a[l] <= piv && l < r) l++;
				if (l < r) a[r--] = a[l];
			}
			a[l] = piv;
			start[i + 1] = l + 1;
			end[i + 1] = end[i];
			end[i++] = l;
			if (end[i] - start[i] > end[i - 1] - start[i - 1]) {
				aux = start[i]; 
				start[i] = start[i - 1]; 
				start[i - 1] = aux;
				aux = end[i]; 
				end[i] = end[i - 1]; 
				end[i - 1] = aux;
			}
		}
		
		else { i--; }
		printArray(a, 9);
	}
}
int main()
{

	int demo;
	printf("want to see demo?\n");
	scanf_s("%d", &demo);
	if (demo == 1) {
		int a[] = { 1,9,4,3,7,6,10,2,12 };
		int a1[] = { 1,9,4,3,7,6,10,2,12 };
		printArray(a, 9);
		int n = sizeof(a) / sizeof(a[0]);
		
		quicksortSteps(a, 0, n - 1);
		printf("\nafter quicksort:\n");
		printArray(a, 9);
		printf("\n\n******\n %d", randomizedSelect(a, 0, n - 1, 7));
		printf("\n dupa quicksort iterativ \n");
		quicksortIt(a1, 9);
		printArray(a1, 9);
		
	}

	
	average(100, 1000);
	worst(100, 1000);
	best(100, 1000);
	profiler.showReport();
}

