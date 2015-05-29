/*
** -------------------------------------------------
** -- Lab #4. OpenMP                              --
** -- Input: A=B*(MO*MK)+a*(Z*ME)*MT              --
** -- Date: 22.04.2015	                          --
** -- Author: Alexander Guk                       --
** -------------------------------------------------
*/
#include <iostream>
#include "omp.h"
#include <windows.h>

using namespace std;

// Stack size
#pragma comment(linker, "/stack:160000000") 

const int N = 6;
const int P = 6;
const int H = N/P;

int *A = new int[N];
int *B = new int[N];
int **MO = new int*[N];
int **MK = new int*[N];
int alpha;
int *Z = new int[N];
int **ME = new int*[N];
int **MT = new int*[N];
int *T = new int[N];

void inMatrix(int** matr) {
	for (int i = 0; i < N; i++) {
		matr[i] = new int[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matr [i][j] = 1;
		}
	}
}

void inVector(int* vec) {
	for (int i = 0; i < N; i++) {
		vec [i] = 1;
	}
}

void outVector(int* vec) {
	for (int i = 0; i < N; i++) {
		printf("%d  ", vec [i]);
	}
}

void cloneV(int* V, int* M) { 
    for (int i = 0; i < N; i++) {
        V [i] = M [i];
    }
}

void cloneM(int **MT, int **MM) {
	for (int i = 0; i < N; i++) {
		MT[i] = new int[N];
	}

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            MT [i][j] = MM [i][j];
        }
    }
}

int main(int argc, char *argv[])
{
	printf("Main thread has started\n");
	
	omp_lock_t lck, lck2;
	omp_init_lock(&lck);
	omp_init_lock(&lck2);
	omp_set_num_threads(P);
	//cin.get();

	#pragma omp parallel 
    {
		int num = omp_get_thread_num();
		
		printf("Thread %d has started\n", num);
		
		switch (num) {
			case 0:		
				inVector(B);
				inMatrix(MO);
				break;
			case 1:
				inMatrix(MK);
				inMatrix(ME);
			break;
			case 5:
				alpha = 1;
				inVector(Z);
				inMatrix(MT);
				break;
		}
// Input sync
#pragma omp barrier

		int **MOx = new int*[N];
		int *Zx = new int[N];
		int *Bx = new int[N];
		int alphaX;
		// Critical section begin
		omp_set_lock(&lck);
		cloneM(MOx, MO);
		cloneV(Zx, Z);
		cloneV(Bx, B);
		alphaX = alpha;
		omp_unset_lock(&lck);
		// Critical section end

		// Calculate Th = Zx * ME
		int sum;
		for (int z = num * H; z < (num + 1) * H; z++) {
			for (int i = 0; i < N; i++) {
				sum = 0;
				for (int j = 0; j < N; j++) {
					sum = sum + Zx[i] * ME[j][z];
				}
				T[z] = sum;
			}
		}
// Calculation Th sync
#pragma omp barrier

		int *Tx = new int[N];
		// Critical section begin
		omp_set_lock(&lck2);
		cloneV(Tx, T);
		omp_unset_lock(&lck2);
		// Critical section end

		// Calculate Ah=Bx*(MOx*MKh)+alphaX*Tx*MTh
		int tmpM[N][N];

		for (int z = num * H; z < (num + 1) * H; z++) {
			for (int i = 0; i < N; i++) {
				sum = 0;
				for (int j = 0; j < N; j++) {
					sum = sum + MOx[i][j] * MK[j][z];
				}
				tmpM[i][z] = sum;
			}
		}

		int tmpV1[N];

		for (int z = num * H; z < (num + 1) * H; z++) {
			for (int i = 0; i < N; i++) {
				sum = 0;
				for (int j = 0; j < N; j++) {
					sum = sum + Bx[i] * tmpM[j][z];
				}
				tmpV1[z] = sum;
			}
		}

		int tmpV2[N];

		for (int z = num * H; z < (num + 1) * H; z++) {
			for (int i = 0; i < N; i++) {
				sum = 0;
				for (int j = 0; j < N; j++) {
					sum = sum + Tx[i] * MT[j][z];
				}
				tmpV2[z] = alphaX * sum;
			}
		}

		for (int z = num * H; z < (num + 1) * H; z++) {
			A[z] = tmpV1[z] + tmpV2[z];
		}

// Output sync
#pragma omp barrier

		// Output
		if (num == 0) {
			if (N <= 12) outVector(A);	
		}
		printf("Thread %d has finished\n", num);
	}

	printf("Main thread has finished\n");
	cin.get();
	return 0;
}
