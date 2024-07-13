#include "matrices.hpp"

void checkFileAccess(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ifstream::failure(filename);
    }
}

void Matrix::allocateNewData_() {
    data_ = new double[rowDimension_ * columnDimension_]();
}

Matrix::Matrix(size_t inputRowDimension, size_t inputColumnDimension) {
    rowDimension_ = inputRowDimension;
    columnDimension_ = inputColumnDimension;
    allocateNewData_();
}

Matrix::Matrix(const char* filename) {
    checkFileAccess(filename);
    std::ifstream matrixFile(filename);
    double matrixElem;

    matrixFile >> rowDimension_ >> columnDimension_;

    allocateNewData_();

    for (size_t i = 0; i < rowDimension_; i++) {
        for (size_t j = 0; j < columnDimension_; j++) {
            matrixFile >> matrixElem;
            data_[i * columnDimension_ + j] = matrixElem;
        }
    }
}

Matrix::Matrix(const Matrix& initMatrix) {
    rowDimension_ = initMatrix.rowDimension_;
    columnDimension_ = initMatrix.columnDimension_;

    allocateNewData_();

    for (size_t i = 0; i < rowDimension_; i++) {
        for (size_t j = 0; j < columnDimension_; j++) {
            data_[i * columnDimension_ + j] = initMatrix.data_[i * columnDimension_ + j];
        }
    }
}

void Matrix::reformatMatrix_(size_t newColumnDimension, const double* newData) {
    delete[] data_;

    columnDimension_ = newColumnDimension;

    allocateNewData_();

    for (size_t i = 0; i < rowDimension_; i++) {
        for (size_t j = 0; j < columnDimension_; j++) {
            data_[i * columnDimension_ + j] = newData[i * columnDimension_ + j];
        }
    }
}

bool Matrix::isAddingMatricesAvailable_(const Matrix& a, const Matrix& b) {
    return (a.rowDimension_ == b.rowDimension_ && a.columnDimension_ == b.columnDimension_);
}

bool Matrix::isMultingMatricesAvailable_(const Matrix& a, const Matrix& b) {
    return (a.columnDimension_ == b.rowDimension_);
}

void Matrix::addMatrices(const Matrix& a, const Matrix& b) {
    if (!isAddingMatricesAvailable_(a, b)) {
        throw InvalidMatricesAdding(
                "Add operation between matrices "
                "A and B can't be performed because dimensions of matrices are not equal!"
        );
    }
    for (size_t i = 0; i < a.rowDimension_; i++) {
        for (size_t j = 0; j < a.columnDimension_; j++) {
            a.data_[i * a.columnDimension_ + j] += b.data_[i * a.columnDimension_ + j];
        }
    }
}

void Matrix::multMatrices(Matrix &a, const Matrix &b) {
    int matrixIndex = 0;
    Matrix newMatrix = Matrix(a.rowDimension_, b.columnDimension_);
    if (!isMultingMatricesAvailable_(a, b)) {
        throw InvalidMatricesMulting(
                "Mult operation between matrices "
                "A and B can't be performed, "
                "because A.rowDimension does not equal B.columnDimension!"
        );
    }
    for (size_t i = 0; i < newMatrix.rowDimension_; i++) {
        for (size_t j = 0; j < newMatrix.columnDimension_; j++) {
            for (size_t k = 0; k < a.columnDimension_; k++) {
                newMatrix.data_[matrixIndex] += a.data_[i*a.columnDimension_+k] * b.data_[k*b.columnDimension_+j];
            }
            ++matrixIndex;
        }
    }

    a.reformatMatrix_(b.columnDimension_, newMatrix.data_);
}

void Matrix::displayMatrix() const {
    std::cout << rowDimension_ << " " << columnDimension_ << std::endl;
    for (size_t i = 0; i < rowDimension_; i++) {
        for (size_t j = 0; j < columnDimension_; j++) {
            std::cout << data_[i * columnDimension_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix::~Matrix() {
    delete[] data_;
}
