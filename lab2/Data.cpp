
#include <iostream>
#include "Data.h"

void fill(int *vector, int value) {
	for (int i = 0; i < N; i++)
		vector[i] = value;
}

void fill(int **matrix, int value) {
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		matrix[i][j] = value;
}

int findMax(int *vector, int begin, int end) {
	int maxElem = vector[begin];
	for (int i = begin + 1; i < end; i++) {
		if (vector[i] > maxElem) maxElem = vector[i];
	}

	return maxElem;
}

void disp(int **matrix) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << " " << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void init(int **matrix) {
	for (int i = 0; i < N; ++i)
		matrix[i] = new int[N];
}
