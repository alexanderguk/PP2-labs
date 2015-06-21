#include "Matrix.h"
#include <iostream>
Matrix::Matrix(int size) {
	this->rows = size;
	this->columns = size;
	matrix = new int[size*size];
}
Matrix::Matrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	matrix = new int[rows*columns];
}
Matrix::~Matrix() {
	delete(matrix);
}
int Matrix::getRows() const {
	return rows;
}
int Matrix::getColumns() const {
	return columns;
}
void* Matrix::getPtrToArray(){
	return (void*)(&(*matrix));
}
int* Matrix::operator[](int row) {
	return matrix + row*columns;
}
void Matrix::input() {
	for (int i = 0; i < rows*columns; i++) {
		matrix[i] = FILLER;
	}
}
void Matrix::copy(Matrix& copyMatrix) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			copyMatrix[i][j] = matrix[i*columns + j];
		}
	}
}
void Matrix::mult(Matrix& res, Matrix& multMatr){
	int* r;
	int* mm;
	int* tm;
	int rColumns = res.getColumns();
	int mmColumns = multMatr.getColumns();
	int tmColumns = columns;
	for (int i = 0; i < mmColumns; i++)
	{
		r = res.matrix;
		tm = matrix;
		for (int j = 0; j < rows; j++)
		{
			r[i] = 0;
			mm = multMatr.matrix;
			for (int k = 0; k < rows; k++)
			{
				r[i] += tm[k] * mm[i];
				mm += mmColumns;
			};
			r += rColumns;
			tm += tmColumns;
		}
	}
}
std::ostream& operator<<(std::ostream &out, Matrix &matrix) {
	int last = matrix.getColumns() - 1;
	out << "Matrix:" << std::endl;
	for (int row = 0; row < matrix.getRows(); row++) {
		for (int col = 0; col < last; col++)
			out << matrix[row][col] << " ";
		out << matrix[row][last] << std::endl;
	}
	return out;
};