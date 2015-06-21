#include "Vector.h"
#include "Matrix.h"
#include <iostream>
Vector::Vector(int size) {
	this->size = size;
	vector = new int[size];
}
Vector::~Vector() {
	delete(vector);
}
void* Vector::getPtrToArray(){
	return (void*)vector;
}
int& Vector::operator[](int index) {
	return *(vector + index);
}

Vector Vector::operator * (int integer) {
	Vector v(size);
	for (int i = 0; i < size; ++i)
		v[i] = vector[i] * integer;
	return v;
}
void Vector::input() {
	for (int i = 0; i < size; i++) {
		vector[i] = FILLER;
	}
}
void Vector::copy(Vector& copyVector) {
	for (int i = 0; i < size; i++) {
		copyVector[i] = vector[i];
	}
}
void Vector::mult(const Vector& res, const Matrix& multMatr) {
	mult(res, multMatr, 0, multMatr.getColumns());
}
void Vector::mult(const Vector& res, const Matrix& multMatr, int start, int end) {
	int sum;
	for (int z = start; z < end; z++) {
		for (int i = 0; i < multMatr.getColumns(); i++) {
			sum = 0;
			for (int j = 0; j < multMatr.getColumns(); j++) {
				sum = sum + res.vector[i] * multMatr.matrix[j * multMatr.getRows() + z];
			}
			vector[z] = sum;
		}
	}
}
int Vector::getSize()
{
	return size;
}
std::ostream& operator<<(std::ostream &out, Vector &Vector) {
	out << "Vector:" << std::endl;
	for (int row = 0; row < Vector.getSize(); row++) {
		out << Vector[row] << " ";
	}
	return out;
};

int Vector::getMax(int from, int to) const
{
	int m = -99999;
	for (int i = from; i < to; ++i)
	{
		if (*(vector + i) > m)
		{
			m = *(vector + i);
		}
	}
	return m;
}