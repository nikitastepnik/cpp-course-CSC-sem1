#pragma once

#include <fstream>
#include <iostream>
#include <regex>

void checkFileAccess(const char *filename);

class InvalidMatricesAdding : public std::invalid_argument {
public:
    explicit InvalidMatricesAdding(const std::string &message) : std::invalid_argument(message) {}
};

class InvalidMatricesMulting : public std::invalid_argument {
public:
    explicit InvalidMatricesMulting(const std::string &message) : std::invalid_argument(message) {}
};

class Matrix {
private:
    size_t rowDimension_;
    size_t columnDimension_;
    double *data_;

    static bool isAddingMatricesAvailable_(const Matrix &a, const Matrix &b);

    static bool isMultingMatricesAvailable_(const Matrix &a, const Matrix &b);

    void allocateNewData_();

    void reformatMatrix_(size_t newColumnDimension, const double *newData);

public:
    Matrix(size_t inputRowDimension, size_t inputColumnDimension);

    Matrix(const Matrix &initMatrix);

    explicit Matrix(const char *filename);

    ~Matrix();

    static void addMatrices(const Matrix &a, const Matrix &b);

    static void multMatrices(Matrix &a, const Matrix &b);

    void displayMatrix() const;
};
