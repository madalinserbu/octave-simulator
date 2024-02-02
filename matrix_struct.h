#ifndef MATRIX_STRUCT_H
#define MATRIX_STRUCT_H

typedef struct
{
	int rows;
	int cols;
	int **data;
} Matrix;

typedef struct
{
	Matrix *matrices;
	int size;
	int capacity;
} MatrixArray;

#endif
