//--------------------------
//Лабораторна робота 8
//MA = MB * max(Z) + alpha * (MO * MK)
//Гук Олександр
//Група ІП-22
//05.06.15
//--------------------------
#include <mpi.h>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include <time.h>
#include <vector>
using namespace std;
int N = 18;
int P = 9;
int H = N / P;

enum Tag {
	_1_2_MB,
	_1_2_Z,
	_1_2_alpha,
	_1_2_MO,
	_1_2_MK,
	_1_6_MB,
	_1_6_Z,
	_1_6_alpha,
	_1_6_MO,
	_1_6_MK,

	_1_2_m,
	_1_6_m,

	_2_1_MA,
	_6_1_MA,

	_2_1_m,
	_6_1_m,

	_2_3_MB,
	_2_3_Z,
	_2_3_alpha,
	_2_3_MO,
	_2_3_MK,

	_2_4_MB,
	_2_4_Z,
	_2_4_alpha,
	_2_4_MO,
	_2_4_MK,

	_2_5_MB,
	_2_5_Z,
	_2_5_alpha,
	_2_5_MO,
	_2_5_MK,

	_3_2_m,
	_4_2_m,
	_5_2_m,

	_2_3_m,
	_2_4_m,
	_2_5_m,

	_3_2_MA,
	_4_2_MA,
	_5_2_MA,

	_6_7_MB,
	_6_7_Z,
	_6_7_alpha,
	_6_7_MO,
	_6_7_MK,

	_6_8_MB,
	_6_8_Z,
	_6_8_alpha,
	_6_8_MO,
	_6_8_MK,

	_6_9_MB,
	_6_9_Z,
	_6_9_alpha,
	_6_9_MO,
	_6_9_MK,

	_7_6_m,
	_8_6_m,
	_9_6_m,

	_6_7_m,
	_6_8_m,
	_6_9_m,

	_7_6_MA,
	_8_6_MA,
	_9_6_MA
};

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
void calc(Matrix& MA, Matrix& MB, int m, Matrix& MO, Matrix& MK, int alpha, int start, int end)
{
	Matrix tmpM(N);

	for (auto i = start; i < end; ++i)
	{
		for (auto j = 0; j < N; ++j)
		{
			tmpM[i][j] = MB[i][j] * m;
		}
	}

	for (auto i = start; i < end; ++i)
	{
		for (auto j = 0; j < N; ++j)
		{
			MA[i][j] = 0;
			for (auto k = 0; k < N; ++k)
			{
				MA[i][j] += MO[i][k] * MK[k][j];
			}
			MA[i][j] = tmpM[i][j] + MA[i][j] * alpha;
		}
	}
}

void func1(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	MB.input();
	MO.input();
	MK.input();
	Z.input();
	int alpha = 1;

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N*H), N * 4 * H, MPI_INT, 1, _1_2_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + H), 4 * H, MPI_INT, 1, _1_2_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 1, _1_2_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N*H), N * 4 * H, MPI_INT, 1, _1_2_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 1, _1_2_MK, MPI_COMM_WORLD);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 5 * H), N * 4 * H, MPI_INT, 5, _1_6_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 5 * H), 4 * H, MPI_INT, 5, _1_6_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 5, _1_6_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 5 * H), N * 4 * H, MPI_INT, 5, _1_6_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 5, _1_6_MK, MPI_COMM_WORLD);

	int m2, m6;
	MPI_Recv(&m2, 1, MPI_INT, 1, _2_1_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&m6, 1, MPI_INT, 5, _6_1_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int mh = Z.getMax(rank * H, (rank + 1) * H);

	int m = -9999;
	m = max(m, m2);
	m = max(m, m6);
	m = max(m, mh);

	MPI_Send(&m, 1, MPI_INT, 1, _1_2_m, MPI_COMM_WORLD);
	MPI_Send(&m, 1, MPI_INT, 5, _1_6_m, MPI_COMM_WORLD);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N*H), N * 4 * H, MPI_INT, 1, _2_1_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 5 * H), N * 4 * H, MPI_INT, 5, _6_1_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	cout << "Result1:" << endl << MA << endl;
}

void func2(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N*H), N * 4 * H, MPI_INT, 0, _1_2_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + H), 4 * H, MPI_INT, 0, _1_2_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 0, _1_2_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N*H), N * 4 * H, MPI_INT, 0, _1_2_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 0, _1_2_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 2 * H), N*H, MPI_INT, 2, _2_3_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 2 * H), H, MPI_INT, 2, _2_3_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 2, _2_3_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 2 * H), N*H, MPI_INT, 2, _2_3_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 2, _2_3_MK, MPI_COMM_WORLD);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 3 * H), N*H, MPI_INT, 3, _2_4_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 3 * H), H, MPI_INT, 3, _2_4_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 3, _2_4_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 3 * H), N*H, MPI_INT, 3, _2_4_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 3, _2_4_MK, MPI_COMM_WORLD);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 4 * H), N*H, MPI_INT, 4, _2_5_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 4 * H), H, MPI_INT, 4, _2_5_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 4, _2_5_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 4 * H), N*H, MPI_INT, 4, _2_5_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 4, _2_5_MK, MPI_COMM_WORLD);

	int m3, m4, m5;
	MPI_Recv(&m3, 1, MPI_INT, 2, _3_2_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&m4, 1, MPI_INT, 3, _4_2_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&m5, 1, MPI_INT, 4, _5_2_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int mh = Z.getMax(rank * H, (rank + 1) * H);

	int m = -9999;
	m = max(m, m3);
	m = max(m, m4);
	m = max(m, m5);
	m = max(m, mh);

	MPI_Send(&m, 1, MPI_INT, 0, _2_1_m, MPI_COMM_WORLD);
	cout << "T2_1" << endl;

	MPI_Recv(&m, 1, MPI_INT, 0, _1_2_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	cout << "T2_2" << endl;

	MPI_Send(&m, 1, MPI_INT, 2, _2_3_m, MPI_COMM_WORLD);
	MPI_Send(&m, 1, MPI_INT, 3, _2_4_m, MPI_COMM_WORLD);
	MPI_Send(&m, 1, MPI_INT, 4, _2_5_m, MPI_COMM_WORLD);
	
	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 2 * H), N*H, MPI_INT, 2, _3_2_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 3 * H), N*H, MPI_INT, 3, _4_2_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 4 * H), N*H, MPI_INT, 4, _5_2_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N*H), N * 4 * H, MPI_INT, 0, _2_1_MA, MPI_COMM_WORLD);
}

void func3(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 2 * H), N*H, MPI_INT, 1, _2_3_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 2 * H), H, MPI_INT, 1, _2_3_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 1, _2_3_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 2 * H), N*H, MPI_INT, 1, _2_3_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 1, _2_3_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int m = Z.getMax(rank * H, (rank + 1) * H);

	MPI_Send(&m, 1, MPI_INT, 1, _3_2_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 1, _2_3_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 2 * H), N*H, MPI_INT, 1, _3_2_MA, MPI_COMM_WORLD);
}

void func4(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 3 * H), N*H, MPI_INT, 1, _2_4_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 3 * H), H, MPI_INT, 1, _2_4_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 1, _2_4_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 3 * H), N*H, MPI_INT, 1, _2_4_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 1, _2_4_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int m = Z.getMax(rank * H, (rank + 1) * H);

	MPI_Send(&m, 1, MPI_INT, 1, _4_2_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 1, _2_4_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 3 * H), N*H, MPI_INT, 1, _4_2_MA, MPI_COMM_WORLD);
}

void func5(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 4 * H), N*H, MPI_INT, 1, _2_5_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 4 * H), H, MPI_INT, 1, _2_5_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 1, _2_5_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 4 * H), N*H, MPI_INT, 1, _2_5_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 1, _2_5_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int m = Z.getMax(rank * H, (rank + 1) * H);

	MPI_Send(&m, 1, MPI_INT, 1, _5_2_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 1, _2_5_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 4 * H), N*H, MPI_INT, 1, _5_2_MA, MPI_COMM_WORLD);
}

void func6(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 5 * H), N * 4 * H, MPI_INT, 0, _1_6_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 5 * H), 4 * H, MPI_INT, 0, _1_6_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 0, _1_6_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 5 * H), N * 4 * H, MPI_INT, 0, _1_6_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 0, _1_6_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 6 * H), N*H, MPI_INT, 6, _6_7_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 6 * H), H, MPI_INT, 6, _6_7_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 6, _6_7_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 6 * H), N*H, MPI_INT, 6, _6_7_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 6, _6_7_MK, MPI_COMM_WORLD);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 7 * H), N*H, MPI_INT, 7, _6_8_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 7 * H), H, MPI_INT, 7, _6_8_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 7, _6_8_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 7 * H), N*H, MPI_INT, 7, _6_8_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 7, _6_8_MK, MPI_COMM_WORLD);

	MPI_Send((void*)((int*)(MB.getPtrToArray()) + N * 8 * H), N*H, MPI_INT, 8, _6_9_MB, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(Z.getPtrToArray()) + 8 * H), H, MPI_INT, 8, _6_9_Z, MPI_COMM_WORLD);
	MPI_Send(&alpha, 1, MPI_INT, 8, _6_9_alpha, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MO.getPtrToArray()) + N * 8 * H), N*H, MPI_INT, 8, _6_9_MO, MPI_COMM_WORLD);
	MPI_Send((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 8, _6_9_MK, MPI_COMM_WORLD);

	int m7, m8, m9;
	MPI_Recv(&m7, 1, MPI_INT, 6, _7_6_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&m8, 1, MPI_INT, 7, _8_6_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&m9, 1, MPI_INT, 8, _9_6_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int mh = Z.getMax(rank * H, (rank + 1) * H);

	int m = -9999;
	m = max(m, m7);
	m = max(m, m8);
	m = max(m, m9);
	m = max(m, mh);

	MPI_Send(&m, 1, MPI_INT, 0, _6_1_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 0, _1_6_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	MPI_Send(&m, 1, MPI_INT, 6, _6_7_m, MPI_COMM_WORLD);
	MPI_Send(&m, 1, MPI_INT, 7, _6_8_m, MPI_COMM_WORLD);
	MPI_Send(&m, 1, MPI_INT, 8, _6_9_m, MPI_COMM_WORLD);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 6 * H), N*H, MPI_INT, 6, _7_6_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 7 * H), N*H, MPI_INT, 7, _8_6_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MA.getPtrToArray()) + N * 8 * H), N*H, MPI_INT, 8, _9_6_MA, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 5 * H), N * 4 * H, MPI_INT, 0, _6_1_MA, MPI_COMM_WORLD);
}

void func7(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 6 * H), N*H, MPI_INT, 5, _6_7_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 6 * H), H, MPI_INT, 5, _6_7_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 5, _6_7_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 6 * H), N*H, MPI_INT, 5, _6_7_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 5, _6_7_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int m = Z.getMax(rank * H, (rank + 1) * H);

	MPI_Send(&m, 1, MPI_INT, 5, _7_6_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 5, _6_7_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 6 * H), N*H, MPI_INT, 5, _7_6_MA, MPI_COMM_WORLD);
}

void func8(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 7 * H), N*H, MPI_INT, 5, _6_8_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 7 * H), H, MPI_INT, 5, _6_8_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 5, _6_8_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 7 * H), N*H, MPI_INT, 5, _6_8_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 5, _6_8_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int m = Z.getMax(rank * H, (rank + 1) * H);

	MPI_Send(&m, 1, MPI_INT, 5, _8_6_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 5, _6_8_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 7 * H), N*H, MPI_INT, 5, _8_6_MA, MPI_COMM_WORLD);
}

void func9(int rank)
{
	Matrix MB(N), MO(N), MK(N), MA(N);
	Vector Z(N);
	int alpha;

	MPI_Recv((void*)((int*)(MB.getPtrToArray()) + N * 8 * H), N*H, MPI_INT, 5, _6_9_MB, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(Z.getPtrToArray()) + 8 * H), H, MPI_INT, 5, _6_9_Z, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv(&alpha, 1, MPI_INT, 5, _6_9_alpha, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MO.getPtrToArray()) + N * 8 * H), N*H, MPI_INT, 5, _6_9_MO, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	MPI_Recv((void*)((int*)(MK.getPtrToArray())), N * N, MPI_INT, 5, _6_9_MK, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	int m = Z.getMax(rank * H, (rank + 1) * H);

	MPI_Send(&m, 1, MPI_INT, 5, _9_6_m, MPI_COMM_WORLD);

	MPI_Recv(&m, 1, MPI_INT, 5, _6_9_m, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	calc(MA, MB, m, MO, MK, alpha, rank * H, (rank + 1) * H);

	MPI_Send((void*)((int*)(MA.getPtrToArray()) + N * 8 * H), N*H, MPI_INT, 5, _9_6_MA, MPI_COMM_WORLD);
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	long tStart = clock();
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	H = N / P;
	cout << "Thread " << (rank + 1) << " started." << endl;
	switch (rank)
	{
	case 0:
		func1(rank);
		break;
	case 1:
		func2(rank);
		break;
	case 2:
		func3(rank);
		break;
	case 3:
		func4(rank);
		break;
	case 4:
		func5(rank);
		break;
	case 5:
		func6(rank);
		break;
	case 6:
		func7(rank);
		break;
	case 7:
		func8(rank);
		break;
	case 8:
		func9(rank);
		break;
	}
	cout << "Thread " << (rank + 1) << " finished" << endl;
	MPI_Finalize();
	return 0;
}