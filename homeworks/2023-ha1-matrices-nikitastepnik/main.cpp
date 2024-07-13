#include "matrices.hpp"

const std::string ADD_OPERATOR = "--add";
const std::string MULT_OPERATOR = "--mult";


class InvalidArgc : public std::invalid_argument {
public:
    explicit InvalidArgc(const std::string &message) : std::invalid_argument(message) {}
};

class InvalidArgv : public std::invalid_argument {
public:
    explicit InvalidArgv(const std::string &message) : std::invalid_argument(message) {}
};

void setOperatorToInitVal(std::string &exprOperator) {
    exprOperator = "";
}

void setOperandToInitVal(const char *&fileRightOperand) {
    fileRightOperand = nullptr;
}

void calculateMatricesExpr(
        Matrix &resMatrix,
        const std::string &exprOperator,
        Matrix &rightMatrix
) {
    if (exprOperator == ADD_OPERATOR) {
        Matrix::addMatrices(resMatrix, rightMatrix);
    } else {
        Matrix::multMatrices(resMatrix, rightMatrix);
    }
}

void calculateMatricesExpressions(size_t argc, char **argv, Matrix &resMatrix) {
    const char *fileRightOperand = nullptr;
    std::string exprOperator;

    for (size_t i = 2; i < argc; i++) {
        if (i % 2 != 0) {
            {
                fileRightOperand = argv[i];
            }
        } else {
            exprOperator = argv[i];
        }

        if (!(exprOperator.empty()) and fileRightOperand) {
            Matrix rightMatrix(fileRightOperand);
            calculateMatricesExpr(resMatrix, exprOperator, rightMatrix);

            setOperandToInitVal(fileRightOperand);
            setOperatorToInitVal(exprOperator);
        }
    }
}

void checkUserInput(size_t argc, char **argv) {
    int countFileArgc = 0;
    int countOperationsArgc = 0;

    for (size_t i = 1; i < argc; i++) {
        if (i % 2 == 0) {
            if (argv[i] != ADD_OPERATOR and argv[i] != MULT_OPERATOR) {
                throw InvalidArgv(argv[i]);
            }
            countOperationsArgc += 1;
        } else {
            countFileArgc += 1;
        }
    }

    if (countFileArgc - 1 != countOperationsArgc) {
        throw InvalidArgc("Invalid count of arguments!");
    }
}

int main(int argc, char **argv) {
    try {
        checkUserInput(argc, argv);
        Matrix resMatrix(argv[1]);
        calculateMatricesExpressions(argc, argv, resMatrix);
        resMatrix.displayMatrix();
    } catch (const InvalidArgv &exc) {
        std::cerr << "Invalid or unexpected argument: " << exc.what() << std::endl;
        return 1;
    } catch (const InvalidArgc &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    catch (const std::ifstream::failure &exc) {
        std::cerr << "Failed to open file: " << exc.what() << std::endl;
        return 1;
    } catch (const InvalidMatricesAdding &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    return 0;
}
