#include "../modules.hpp"

using std::vector;
using std::ostream;
using std::endl;

Matrix::Matrix() {
    values = NULL;
    size = 0;
}

Matrix::Matrix(const Matrix & matrix) {
    allocate(matrix.getSize());
    copyValues(matrix);
}

Matrix::~Matrix() {
    deallocate();
}

void Matrix::copyValues(const Matrix & matrix) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            values[i][j] = matrix.getValue(i, j);
        }
    }
}

void Matrix::allocate(int size) {
    if (size < 1) {
        throw InvalidSizeException("Matrix size must be greater than zero.");
    }

    this->size = size;

    values = new int * [size];

    for (int i = 0; i < size; i++) {
        values[i] = new int[size];

        for (int j = 0; j < size; j++) {
            values[i][j] = 0;
        }
    }
}

void Matrix::deallocate() {
    if (values) {
        for (int i = 0; i < size; i++) {
            delete [] values[i];
        }

        delete [] values;
        values = NULL;
    }

    size = 0;
}

void Matrix::reallocate(int size) {
    deallocate();
    allocate(size);
}

void Matrix::fill(vector<Edge> edges, Vertex * vertices) {
    for (vector<Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
        int i, j;

        for (int k = 0; k < size; k++) {
            if (vertices[k].getId() == it->getA()) i = k;
            if (vertices[k].getId() == it->getB()) j = k;
        }

        values[i][j] = 1;
        // values[j][i] = 1;
    }
}

void Matrix::fillWith(int value) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            values[i][j] = value;
        }
    }
}

int Matrix::getSize() const {
    return size;
}

int Matrix::getValue(int i, int j) const {
    if (i >= size || j >= size) {
        throw InvalidIndexException("Requested cell is out of range.");
    }

    return values[i][j];
}

void Matrix::setValue(int i, int j, int value) {
    if (i >= size || j >= size) {
        throw InvalidIndexException("Requested cell is out of range.");
    }

    this->values[i][j] = value;
}

Matrix Matrix::operator * (const Matrix & matrix) const {
    Matrix result;
    result.allocate(size);

    int sum;

    for (int i =  0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum = 0;

            // Sums up values in cells.
            for (int k = 0; k < size; k++) {
                sum += values[i][k] * matrix.getValue(k, j);
            }

            result.setValue(i, j, sum);
        }
    }

    return result;
}

Matrix & Matrix::operator = (const Matrix & matrix) {
    if (this != &matrix) {
        reallocate(matrix.getSize());
        copyValues(matrix);
    }

    return * this;
}

ostream & operator << (ostream & os, const Matrix & matrix) {
    os << endl;

    for (int i = 0; i < matrix.size; i++) {
        for (int j = 0; j < matrix.size; j++) {
            os << matrix.values[i][j] << " ";
        }

        os << endl;
    }

    return os;
}
