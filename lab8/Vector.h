#pragma once
#include <iostream>
#include "Matrix.h"
class Vector {
private:
	static const int FILLER = 1;
	int size;
public:
	int *vector;
	Vector(int size);
	Vector(int rows, int columns);
	~Vector();
	int getSize();
	void* getPtrToArray();//--
	int& operator [] (int index);
	Vector operator * (int integer);
	void input();
	void copy(Vector& copyMatrix);
	void mult(const Vector& res, const Matrix& multMatr);
	void mult(const Vector& res, const Matrix& multMatr, int start, int end);

	int getMax(int from, int to) const;
};
std::ostream& operator << (std::ostream &out, Vector &matrix);