#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "matrix_struct.h"
#define MOD 10007

void initMatrixArray(MatrixArray *array, int initialCapacity)
{
	array->matrices = (Matrix *)malloc(initialCapacity * sizeof(Matrix));
	if (array->matrices == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	array->size = 0;
	array->capacity = initialCapacity;
}

void resizeMatrixArray(MatrixArray *array)
{
	array->capacity *= 2;
	array->matrices = (Matrix *)realloc(array->matrices, array->capacity * sizeof(Matrix));
	if (array->matrices == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
}

void freeMatrix(Matrix *matrix)
{
	for (int i = 0; i < matrix->rows; ++i)
	{
		free(matrix->data[i]);
	}
	free(matrix->data);
}

void freeMatrixArray(MatrixArray *array)
{
	for (int i = 0; i < array->size; ++i)
	{
		freeMatrix(&(array->matrices[i]));
	}
	free(array->matrices);
}

void loadMatrix(MatrixArray *array, int rows, int cols)
{
	if (array->size == array->capacity)
	{
		resizeMatrixArray(array);
	}

	Matrix *matrix = &(array->matrices[array->size]);
	matrix->rows = rows;
	matrix->cols = cols;

	matrix->data = (int **)malloc(rows * sizeof(int *));
	if (matrix->data == NULL)
	{
		fprintf(stderr, "malloc() failed\n");
		free(matrix);
		return;
	}

	for (int i = 0; i < rows; ++i)
	{
		matrix->data[i] = (int *)malloc(cols * sizeof(int));
		if (matrix->data[i] == NULL)
		{
			fprintf(stderr, "malloc() failed\n");
			for (int j = 0; j < i; j++)
				free(matrix->data[j]);
			free(matrix->data);
			free(matrix);
			return;
		}

		for (int j = 0; j < cols; ++j)
		{
			scanf("%d", &(matrix->data[i][j])); // Read values into the matrix
			if (matrix->data[i][j] < 0)
			{
				// Handle negative values
				matrix->data[i][j] = (matrix->data[i][j]) % MOD;
			}
			// No need to handle positive values here
		}
	}

	array->size++;
}

void printMatrix(Matrix *matrix)
{
	for (int i = 0; i < matrix->rows; ++i)
	{
		for (int j = 0; j < matrix->cols; ++j)
		{
			printf("%d ", matrix->data[i][j]);
		}
		printf("\n");
	}
}

void dimensions(MatrixArray *array, int index)
{
	if (index < 0 || index >= array->size)
	{
		printf("No matrix with the given index\n");
		return;
	}

	printf("%d %d\n", array->matrices[index].rows, array->matrices[index].cols);
}

void print(MatrixArray *array, int index)
{
	if (index < 0 || index >= array->size)
	{
		printf("No matrix with the given index\n");
		return;
	}

	printMatrix(&(array->matrices[index]));
}

void resize(MatrixArray *array, int index, int newRows, int *rowsIndices, int newCols, int *colsIndices)
{
	if (index < 0 || index >= array->size)
	{
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix = &(array->matrices[index]);
	int **tempData = (int **)malloc(newRows * sizeof(int *));
	for (int i = 0; i < newRows; ++i)
	{
		tempData[i] = (int *)malloc(newCols * sizeof(int));
	}

	// Copy specified rows and columns
	for (int i = 0; i < newRows; ++i)
	{
		for (int j = 0; j < newCols; ++j)
		{
			tempData[i][j] = matrix->data[rowsIndices[i]][colsIndices[j]];
		}
	}

	// Free memory for the old matrix
	for (int i = 0; i < matrix->rows; ++i)
	{
		free(matrix->data[i]);
	}
	free(matrix->data);

	// Update matrix dimensions
	matrix->rows = newRows;
	matrix->cols = newCols;

	// Assign the new data set
	matrix->data = tempData;
}
void multiply(MatrixArray *array, int index1, int index2)
{
	if (index1 < 0 || index1 >= array->size || index2 < 0 || index2 >= array->size)
	{
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix1 = &(array->matrices[index1]);
	Matrix *matrix2 = &(array->matrices[index2]);

	if (matrix1->cols != matrix2->rows)
	{
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	// Use a new index for the result matrix
	int resultIndex = array->size;

	Matrix *result = &(array->matrices[resultIndex]);
	result->rows = matrix1->rows;
	result->cols = matrix2->cols;
	result->data = (int **)malloc(result->rows * sizeof(int *));

	for (int i = 0; i < result->rows; ++i)
	{
		result->data[i] = (int *)calloc(result->cols, sizeof(int));
		for (int j = 0; j < result->cols; ++j)
		{
			for (int k = 0; k < matrix1->cols; ++k)
			{
				// Ensure proper handling of negative numbers
				long long temp = (long long)matrix1->data[i][k] * matrix2->data[k][j];
				result->data[i][j] = (result->data[i][j] + temp % MOD + MOD) % MOD;
			}
		}
	}

	array->size++;
}

void sortMatrices(MatrixArray *array)
{
	// Sortarea matricelor în funcție de suma elementelor (mod MOD)
	for (int i = 0; i < array->size; ++i)
	{
		int sum_pos = 0;
		int sum_neg = 0;

		for (int j = 0; j < array->matrices[i].rows; ++j)
		{
			for (int k = 0; k < array->matrices[i].cols; ++k)
			{
				if (array->matrices[i].data[j][k] >= 0)
				{
					sum_pos = (sum_pos + array->matrices[i].data[j][k]) % MOD;
				}
				else
				{
					sum_neg = (sum_neg + array->matrices[i].data[j][k] + MOD) % MOD;
				}
			}
		}

		int sum = (sum_pos + sum_neg) % MOD;

		for (int j = i + 1; j < array->size; ++j)
		{
			int sum2_pos = 0;
			int sum2_neg = 0;

			for (int k = 0; k < array->matrices[j].rows; ++k)
			{
				for (int l = 0; l < array->matrices[j].cols; ++l)
				{
					if (array->matrices[j].data[k][l] >= 0)
					{
						sum2_pos = (sum2_pos + array->matrices[j].data[k][l]) % MOD;
					}
					else
					{
						sum2_neg = (sum2_neg + array->matrices[j].data[k][l] + MOD) % MOD;
					}
				}
			}

			int sum2 = (sum2_pos + sum2_neg) % MOD;

			if (sum > sum2)
			{
				Matrix temp = array->matrices[i];
				array->matrices[i] = array->matrices[j];
				array->matrices[j] = temp;
				sum = sum2;
			}
		}
	}
}

void transpose(MatrixArray *array, int index)
{
	if (index < 0 || index >= array->size)
	{
		printf("No matrix with the given index\n");
		return;
	}

	Matrix *matrix = &(array->matrices[index]);

	// Create a new matrix for the transpose
	Matrix transposed;
	transposed.rows = matrix->cols;
	transposed.cols = matrix->rows;
	transposed.data = (int **)malloc(transposed.rows * sizeof(int *));
	for (int i = 0; i < transposed.rows; ++i)
	{
		transposed.data[i] = (int *)malloc(transposed.cols * sizeof(int));
	}

	// Populate the transposed matrix
	for (int i = 0; i < matrix->rows; ++i)
	{
		for (int j = 0; j < matrix->cols; ++j)
		{
			transposed.data[j][i] = matrix->data[i][j];
		}
	}

	// Free the original matrix's data
	for (int i = 0; i < matrix->rows; ++i)
	{
		free(matrix->data[i]);
	}
	free(matrix->data);

	// Update the original matrix with the transposed one
	matrix->rows = transposed.rows;
	matrix->cols = transposed.cols;
	matrix->data = transposed.data;
}

Matrix multiplyMatrices(Matrix *matrix1, Matrix *matrix2)
{
	Matrix result;
	result.rows = matrix1->rows;
	result.cols = matrix2->cols;

	// Alocare matrice rezultat
	result.data = (int **)malloc(result.rows * sizeof(int *));
	for (int i = 0; i < result.rows; ++i)
	{
		result.data[i] = (int *)calloc(result.cols, sizeof(int));
	}

	// Multiplicare matrici
	for (int i = 0; i < result.rows; ++i)
	{
		for (int j = 0; j < result.cols; ++j)
		{
			long long temp = 0;
			for (int k = 0; k < matrix1->cols; ++k)
			{
				temp += (long long)matrix1->data[i][k] * matrix2->data[k][j];
				temp %= MOD;
			}
			result.data[i][j] = (int)temp;
		}
	}

	return result;
}

Matrix matrixPower(Matrix *matrix, int pow)
{
	Matrix result;
	result.rows = matrix->rows;
	result.cols = matrix->cols;
	result.data = (int **)malloc(result.rows * sizeof(int *));
	for (int i = 0; i < result.rows; ++i)
	{
		result.data[i] = (int *)malloc(result.cols * sizeof(int));
	}

	// Initialize the result matrix with the identity matrix
	for (int i = 0; i < result.rows; ++i)
	{
		for (int j = 0; j < result.cols; ++j)
		{
			result.data[i][j] = (i == j) ? 1 : 0;
		}
	}

	// Perform matrix exponentiation
	while (pow > 0)
	{
		if (pow % 2 == 1)
		{
			Matrix temp = multiplyMatrices(&result, matrix);
			// Free the memory of the old result.data
			for (int i = 0; i < result.rows; ++i)
			{
				free(result.data[i]);
			}
			free(result.data);
			result = temp;
		}
		*matrix = multiplyMatrices(matrix, matrix);
		pow /= 2;
	}

	return result;
}

// Modify the power function in your main program
void power(MatrixArray *array, int index, int pow)
{
	if (index < 0 || index >= array->size)
	{
		printf("No matrix with the given index\n");
		return;
	}

	if (pow < 0)
	{
		printf("Power should be positive\n");
		return;
	}

	Matrix matrix = array->matrices[index];
	Matrix result = matrixPower(&matrix, pow);

	// Free the original matrix's data
	freeMatrix(&(array->matrices[index]));

	// Replace the original matrix with the result matrix
	array->matrices[index] = result;
}

#endif
