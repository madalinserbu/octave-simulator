## Tema 2 PCLP1 Serbu Ovidiu-Madalin 324CA

# Overview
This program provides a basic implementation of matrix operations in the style of an Octave command-line interface. It supports various operations such as loading matrices, displaying dimensions, printing matrices, resizing, multiplying, sorting, transposing, and calculating powers of matrices.

# Files
my_octave.c: The main program file containing the user interface and command handling logic.
matrix_struct.h: Header file defining the Matrix and MatrixArray structures.
matrix_operations.h: Header file containing function prototypes for matrix operations.
matrix_operations.c: Implementation file containing the actual matrix operation functions.

# How to Compile and Run

Compile the program using a C compiler such as gcc:

gcc my_octave.c matrix_operations.c -o my_octave

Run the compiled program:

./my_octave
    
# Commands
L (Load Matrix): Load a matrix with specified dimensions and elements.
D (Dimensions): Display the dimensions of a matrix.
P (Print Matrix): Print the elements of a matrix.
C (Resize Matrix): Resize a matrix by specifying new rows and columns and providing row and column indices to keep.
M (Multiply Matrices): Multiply two matrices.
O (Sort Matrices): Sort matrices based on the sum of their elements.
T (Transpose Matrix): Transpose a matrix.
R (Power Matrix): Raise a matrix to a specified power.
F (Free Matrix): Free the memory occupied by a matrix.
Q (Quit): Quit the program.

1. Load Matrix (Command: L)
Allows the user to load a matrix into the system.

Implementation:
Checks MatrixArray capacity and dynamically resizes if necessary.
Initializes a new matrix, reads dimensions, and allocates memory for matrix data.
Handles negative values using modular arithmetic.
Adds the matrix to the MatrixArray.

2. Dimensions (Command: D)
Displays the dimensions (rows and columns) of a matrix at a given index.

Implementation:
Validates the provided index.
Prints the rows and columns of the matrix at the specified index.

3. Print Matrix (Command: P)
Prints the elements of a matrix at a given index.

Implementation:
Validates the provided index.
Calls printMatrix function to display the matrix elements.

4. Resize Matrix (Command: C)
Resizes a matrix at a given index, specifying new rows and columns while preserving specified row and column indices.

Implementation:
Validates the provided index.
Dynamically allocates a temporary matrix for resized data.
Copies selected rows and columns from the original matrix to the new matrix.
Frees memory from the original matrix and assigns the resized matrix to the specified index.

5. Multiply Matrices (Command: M)
Multiplies two matrices at given indices and stores the result in a new matrix.

Implementation:
Validates provided indices.
Initializes a new matrix for the result.
Performs matrix multiplication using the multiplyMatrices function.
Adds the result matrix to the MatrixArray.

6. Sort Matrices (Command: O)
Sorts matrices in the MatrixArray based on the sum of their elements.

Implementation:
Uses a simple sorting algorithm to compare matrices based on the sum of positive and negative elements.
Swaps matrices in the MatrixArray accordingly.

7. Transpose Matrix (Command: T)
Transposes a matrix at a given index.

Implementation:
Validates the provided index.
Creates a new matrix for the transposed result using the transpose function.
Updates the original matrix with the transposed one.

8. Power Matrix (Command: R)
Raises a matrix at a given index to a specified power.

Implementation:
Validates provided index and ensures the power is non-negative.
Uses the matrixPower function to perform matrix exponentiation.
Replaces the original matrix with the result.

9. Free Matrix (Command: F)
Frees the memory occupied by a matrix at a given index.

Implementation:
Validates the provided index.
Frees the memory of the matrix using the freeMatrix function.
Shifts remaining matrices in the MatrixArray to fill the gap.

10. Quit (Command: Q)
Quits the program and frees all allocated memory.

Implementation:
Calls freeMatrixArray to release memory for all matrices in the MatrixArray.
Returns from the program.
Matrix Representation
Matrices are represented as structures (Matrix) containing rows, columns, and a dynamic two-dimensional array for data.
The MatrixArray holds an array of matrices.
Memory Management
Memory allocation and deallocation are done dynamically to handle matrices of varying sizes.
Modular arithmetic with a defined constant (MOD) is used to handle negative values and prevent integer overflow.

