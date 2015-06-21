#pragma once
#include <iostream>
class Matrix {
private:
	static const int FILLER = 1;
	int rows;
	int columns;
public:
	int *matrix;
	Matrix(int size);
	Matrix(int rows, int columns);
	~Matrix();
	int getRows() const;
	int getColumns() const;
	void* getPtrToArray();
	int* operator [] (int row);
	void input();
	void copy(Matrix& copyMatrix);
	void mult(Matrix& res, Matrix& multMatr);
};
std::ostream& operator << (std::ostream &out, Matrix &matrix);