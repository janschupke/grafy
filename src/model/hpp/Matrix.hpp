#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

using std::vector;
using std::ostream;

/**
 * Stores relations of vertices and edges between them.
 */
class Matrix {
    private:
        /**
         * Size of the matrix. Matrix is always square, size*size.
         */
        int size;

        /**
         * Two-dimensional array representing matrix cells.
         */
        int ** values;

        /**
         * Copies cell values from the provided matrix.
         * Centralizes the loop used in assignment operator and copy constructor.
         *
         * @param matrix Provided matrix from which the values are copied.
         */
        void copyValues(const Matrix & matrix);

    public:
        /**
         * Creates a new matrix with size = 0.
         */
        Matrix();
        Matrix(const Matrix & matrix);
        ~Matrix();

        /**
         * Allocates the array that stores the information about edges. Fills defaultly with zero values.
         *
         * @param size Size of the matrix.
         * @throws InvalidSize if size < 1.
         */
        void allocate(int size);

        /**
         * Frees all value memory and sets size to 0.
         */
        void deallocate();

        /**
         * Calls deallocate() and reallocate(size);
         *
         * @param size Size of the matrix.
         */
        void reallocate(int size);

        /**
         * Goes through the edge list and fills values symmetrically into matrix.
         *
         * @param edges List of graph's edges.
         * @param vertices Array of graph's vertices
         */
        void fill(vector<Edge> edges, Vertex * vertices);

        /**
         * Fills all matrix cells with provided value.
         *
         * @param value New value of each cell.
         */
        void fillWith(int value);

        int getSize() const;

        /**
         * @param i Coordinate.
         * @param j Coordinate.
         * @throws InvalidIndexException if either of the provided coordinates reaches outside the matrix.
         * @return Value on the requested position.
         */
        int getValue(int i, int j) const;

        /**
         * @param i Coordinate.
         * @param j Coordinate.
         * @param value The value to be set into the cell [i, j].
         * @throws InvalidIndexException if either of the provided coordinates reaches outside the matrix.
         */
        void setValue(int i, int j, int value);

        /**
         * Multiplies two matrices and returns a new instance as a result.
         */
        Matrix operator * (const Matrix & matrix) const;

        /**
         * Assigns new matrix dimensions and values to the existing instance.
         */
        Matrix & operator = (const Matrix & matrix);

        /**
         * Sends the whole matrix to the output stream for printouts.
         */
        friend ostream & operator << (ostream & os, const Matrix & matrix);
};

#endif // MATRIX_HPP
