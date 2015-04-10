/*
** -------------------------------------------------
** -- Lab #2. Win32                               --
** -- Input: MA = max(Z) * MT + alpha * (MK * MR) --
** -- Date: 26.03.2015	                          --
** -- Author: Alexander Guk                       --
** -------------------------------------------------
*/

#include <iostream>
#include <Windows.h>
#include <limits>
#include "data.h"

HANDLE sem_Z, sem_MR, sem_MT_a, sem_MK;
HANDLE mut_p;
HANDLE e_p1, e_p2, e_p3, e_p4;
HANDLE e4_MAh, e2_MAh, e3_MAh;
CRITICAL_SECTION cs_all;

int a;
int p = INT_MIN;  //max element from Z
int *Z = new int[N];
int **MA = new int*[N];
int **MT = new int*[N];
int **MK = new int*[N];
int **MR = new int*[N];

void setMAh(int p, int a, int b, int** MR, int begin, int end);

void T1()
{
	std::cout << "Thread 1 has started\n";
	int begin = 0;
	int end = H;
	int p1, a1;
	int **MK1;

	fill(Z, 1);
	ReleaseSemaphore(sem_Z, 3, NULL);
	fill(MR, 1);
	ReleaseSemaphore(sem_MR, 3, NULL);

	int t1 = findMax(Z, begin, end);

	WaitForSingleObject(mut_p, INFINITE);
	if (t1 > p) p = t1;
	ReleaseMutex(mut_p);

	SetEvent(e_p1);

	WaitForSingleObject(e_p2, INFINITE);
	WaitForSingleObject(e_p3, INFINITE);
	WaitForSingleObject(e_p4, INFINITE);

	WaitForSingleObject(sem_MT_a, INFINITE);
	WaitForSingleObject(sem_MK, INFINITE);

	EnterCriticalSection(&cs_all);
	p1 = p;
	a1 = a;
	MK1 = MK;
	LeaveCriticalSection(&cs_all);

	setMAh(p1, a1, MK1, begin, end);

	WaitForSingleObject(e2_MAh, INFINITE);
	WaitForSingleObject(e3_MAh, INFINITE);
	WaitForSingleObject(e4_MAh, INFINITE);

	if (N <= 10) {
		std::cout << "T1: MA = \n";
		disp(MA);
	}
	std::cout << "Thread 1 has finished\n";
}


void T2()
{
	std::cout << "Thread 2 has started\n";
	int begin = H;
	int end = 2 * H;
	int p2, a2;
	int **MK2;
	WaitForSingleObject(sem_Z, INFINITE);

	int t2 = findMax(Z, begin, end);

	WaitForSingleObject(mut_p, INFINITE);
	if (t2 > p) p = t2;
	ReleaseMutex(mut_p);

	SetEvent(e_p2);

	WaitForSingleObject(e_p1, INFINITE);
	WaitForSingleObject(e_p3, INFINITE);
	WaitForSingleObject(e_p4, INFINITE);

	WaitForSingleObject(sem_MR, INFINITE);
	WaitForSingleObject(sem_MT_a, INFINITE);
	WaitForSingleObject(sem_MK, INFINITE);

	EnterCriticalSection(&cs_all);
	a2 = a;
	p2 = p;
	MK2 = MK;
	LeaveCriticalSection(&cs_all);

	setMAh(p2, a2, MK2, begin, end);

	SetEvent(e2_MAh);
	std::cout << "Thread 2 has finished\n";
}

void T3()
{
	std::cout << "Thread 3 has started\n";
	int begin = 2 * H;
	int end = 3 * H;
	int p3, a3;
	int **MK3;
	fill(MT, 1);
	a = 1;
	ReleaseSemaphore(sem_MT_a, 3, NULL);

	WaitForSingleObject(sem_Z, INFINITE);

	int t3 = findMax(Z, begin, end);

	WaitForSingleObject(mut_p, INFINITE);
	if (t3 > p) p = t3;
	ReleaseMutex(mut_p);

	SetEvent(e_p3);

	WaitForSingleObject(e_p1, INFINITE);
	WaitForSingleObject(e_p2, INFINITE);
	WaitForSingleObject(e_p4, INFINITE);

	WaitForSingleObject(sem_MR, INFINITE);
	WaitForSingleObject(sem_MK, INFINITE);

	EnterCriticalSection(&cs_all);
	p3 = p;
	a3 = a;
	MK3 = MK;
	LeaveCriticalSection(&cs_all);

	setMAh(p3, a3, MK3, begin, end);

	SetEvent(e3_MAh);

	std::cout << "Thread 3 has finished\n";
}

void T4()
{
	std::cout << "Thread 4 has started\n";
	int begin = 3 * H;
	int end = N;
	int p4, a4;
	int **MK4;
	fill(MK, 1);
	ReleaseSemaphore(sem_MK, 3, NULL);

	WaitForSingleObject(sem_Z, INFINITE);

	int t4 = findMax(Z, begin, end);

	WaitForSingleObject(mut_p, INFINITE);
	if (t4 > p) p = t4;
	ReleaseMutex(mut_p);

	SetEvent(e_p4);

	WaitForSingleObject(e_p1, INFINITE);
	WaitForSingleObject(e_p2, INFINITE);
	WaitForSingleObject(e_p3, INFINITE);

	WaitForSingleObject(sem_MR, INFINITE);
	WaitForSingleObject(sem_MT_a, INFINITE);

	EnterCriticalSection(&cs_all);
	p4 = p;
	a4 = a;
	MK4 = MK;
	LeaveCriticalSection(&cs_all);

	setMAh(p4, a4, MK4, begin, end);

	SetEvent(e4_MAh);

	std::cout << "Thread 4 has finished\n";
}

int main()
{
	std::cout << "Main thread has started\n";

	init(MA);
	init(MT);
	init(MK);
	init(MR);

	sem_MR = CreateSemaphore(NULL, 0, 3, NULL);
	sem_Z = CreateSemaphore(NULL, 0, 3, NULL);
	mut_p = CreateMutex(NULL, 0, NULL);
	sem_MT_a = CreateSemaphore(NULL, 0, 3, NULL);
	sem_MK = CreateSemaphore(NULL, 0, 3, NULL);

	e_p1 = CreateEvent(NULL, 1, 0, NULL);
	e_p2 = CreateEvent(NULL, 1, 0, NULL);
	e_p3 = CreateEvent(NULL, 1, 0, NULL);
	e_p4 = CreateEvent(NULL, 1, 0, NULL);

	e4_MAh = CreateEvent(NULL, 1, 0, NULL);
	e2_MAh = CreateEvent(NULL, 1, 0, NULL);
	e3_MAh = CreateEvent(NULL, 1, 0, NULL);

	InitializeCriticalSection(&cs_all);

	DWORD TdId1, TdId2, TdId3, TdId4;

	HANDLE Thread1 = CreateThread(NULL, STACK_SIZE, (LPTHREAD_START_ROUTINE)T1, NULL, 0, &TdId1);
	HANDLE Thread2 = CreateThread(NULL, STACK_SIZE, (LPTHREAD_START_ROUTINE)T2, NULL, 0, &TdId2);
	HANDLE Thread3 = CreateThread(NULL, STACK_SIZE, (LPTHREAD_START_ROUTINE)T3, NULL, 0, &TdId3);
	HANDLE Thread4 = CreateThread(NULL, STACK_SIZE, (LPTHREAD_START_ROUTINE)T4, NULL, 0, &TdId4);

	CloseHandle(Thread1);
	CloseHandle(Thread2);
	CloseHandle(Thread3);

	std::cout << " Main thread has finished\n";

	getchar();
}

void setMAh(int p, int a, int** MK, int begin, int end) {
	for (int iH = begin; iH < end; iH++) {
		for (int jH = 0; jH < N; jH++) {
			int a_mki_MRj = 0;
			for (int ind = 0; ind < N; ind++) { 
				a_mki_MRj += MK[iH][ind] * MR[ind][iH];
			}
			int MAij = p * MT[iH][jH] + a * a_mki_MRj;
			MA[jH][iH] = MAij;
		}
	}
}
