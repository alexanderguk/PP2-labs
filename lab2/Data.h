
#ifndef _DATA_H
#define _DATA_H

const int STACK_SIZE = 30000;
const int N = 4000;
const int P = 4;
const int H = N / P;

void fill(int *vector, int value);
void fill(int **matrix, int value);
int findMax(int *vector, int begin, int end);
void setMAh(int b, int a, int** MT, int begin, int end);
void disp(int **matrix);
void init(int **matrix);

#endif
