#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_struct.h"
#include "matrix_operations.h"

#define MOD 10007

int main(void)
{
	MatrixArray matrixArray;
	initMatrixArray(&matrixArray, 10);
	char command;
	do {
		scanf(" %c", &command);
		if (command == 'L') {
			int rows, cols;
			scanf("%d %d", &rows, &cols);
			loadMatrix(&matrixArray, rows, cols);
		} else if (command == 'D') {
			int index;
			scanf("%d", &index);
			dimensions(&matrixArray, index);
		} else if (command == 'P') {
			int index;
			scanf("%d", &index);
			print(&matrixArray, index);
		} else if (command == 'C') {
			int index, newRows;
			scanf("%d %d", &index, &newRows);
			int *rowsIndices = (int *)malloc(newRows * sizeof(int));
			for (int i = 0; i < newRows; ++i)
				scanf("%d", &rowsIndices[i]);
			int newCols;
			scanf("%d", &newCols);
			int *colsIndices = (int *)malloc(newCols * sizeof(int));
			for (int i = 0; i < newCols; ++i)
				scanf("%d", &colsIndices[i]);
			resize(&matrixArray, index, newRows, rowsIndices, newCols,
				   colsIndices);
			free(rowsIndices);
			free(colsIndices);
		} else if (command == 'M') {
			int index1, index2;
			scanf("%d %d", &index1, &index2);
			multiply(&matrixArray, index1, index2);
		} else if (command == 'O') {
			sortMatrices(&matrixArray);
		} else if (command == 'T') {
			int index;
			scanf("%d", &index);
			transpose(&matrixArray, index);
		} else if (command == 'R') {
			int index, pow;
			scanf("%d %d", &index, &pow);
			power(&matrixArray, index, pow);
		} else if (command == 'F') {
			int index;
			scanf("%d", &index);
			if (index < 0 || index >= matrixArray.size)
				printf("No matrix with the given index\n");
			else {
				freeMatrix(&(matrixArray.matrices[index]));
				for (int i = index; i < matrixArray.size - 1; ++i)
					matrixArray.matrices[i] = matrixArray.matrices[i + 1];
				matrixArray.size--;
			}
		} else if (command == 'Q') {
			freeMatrixArray(&matrixArray);
			return 0;
		}
		 else
			printf("Unrecognized command\n");
	} while (command != 'Q');

	return 0;
}
