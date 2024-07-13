// bignum.hpp - header-only solution goes into this file.
#pragma once

#include <cmath>
#include <cctype>
#include <iostream>
#include <vector>

namespace mp {
    uint32_t MAX_DIGIT = 9;
    int MAX_LENGTH_UINT32_NUMBER = 10;
    int NOT_INITIALIZED_NUMBER_VAL = -1;

    class bignum {
    private:
        std::vector<uint32_t> num;
        mutable std::string numAsString;

        std::vector<uint32_t> getVecWithDigits() const {
            std::vector<uint32_t> vecWithDigits;
            for (const auto &elem: to_string()) {
                vecWithDigits.push_back(std::stoi(std::string(1, elem)));
            }
            return vecWithDigits;
        }

    public:
        explicit bignum() {
            num.push_back(0);
        }

        explicit bignum(int valInt) {
            if (valInt == NOT_INITIALIZED_NUMBER_VAL) {
                return;
            }
            num.insert(num.begin(), valInt);
        }

        explicit bignum(uint32_t valUint) {
            num.insert(num.begin(), valUint);
        }

        explicit bignum(const std::string &valStr) {
            bool isSymbolAdded = false;
            std::string valStrWithoutLeadingUselessSymbols;
            for (char i: valStr) {
                if (i == '+') {
                    continue;
                }
                if (i == '0' and !isSymbolAdded) {
                    continue;
                }
                valStrWithoutLeadingUselessSymbols += i;
                isSymbolAdded = true;
            }
            size_t offset = 0;
            size_t countElems = 0;
            uint64_t numberPart = 0;
            while (offset != valStr.size()) {
                if (valStr.size() < offset + MAX_LENGTH_UINT32_NUMBER) {
                    countElems = valStr.size() - offset;
                } else {
                    countElems = MAX_LENGTH_UINT32_NUMBER;
                }
                numberPart = std::stoul(valStr.substr(offset, countElems));
                if (numberPart > UINT32_MAX) {
                    countElems -= 1;
                    numberPart = std::stoul(valStr.substr(offset, countElems));
                }
                num.push_back(numberPart);
                offset += countElems;
            }
        }

        explicit bignum(const bignum &copiedNum) {
            num.clear();
            for (auto &elem: copiedNum.num) {
                num.push_back(elem);
            }
            num = copiedNum.num;
        }

        bignum &operator=(const bignum &copiedNum) {
            if (this != &copiedNum) {
                num = copiedNum.num;
            }
            return *this;
        }

        bignum &operator=(uint32_t val) {
            num.resize(0);
            num.push_back(val);
            return *this;
        }

        std::string getNumAsString() const {
            return to_string();
        }

        explicit operator uint32_t() const {
            uint32_t result = 0;
            size_t multiplier;
            size_t restDigits;
            for (size_t i = 0; i < num.size(); i++) {
                if (i != num.size() - 1) {
                    restDigits = to_string(i + 1, num.size()).size();
                    multiplier = static_cast<size_t>(pow(10, restDigits));
                    result += num[i] * multiplier;
                } else {
                    result += num[i];
                }
            }
            return result;
        }

        explicit operator bool() const {
            if (!num.empty() and num[0] != 0) {
                return true;
            }
            return false;
        }

        bignum &operator-(bignum &otherNum) = delete;

        bignum operator+(const bignum &rightNum) const {
            bignum result(NOT_INITIALIZED_NUMBER_VAL);

            std::vector<uint32_t> copyLeftNum = getVecWithDigits();
            std::vector<uint32_t> copyRightNum = rightNum.getVecWithDigits();
            uint32_t digitOverflowOnPrevIter = 0;

            while (!copyLeftNum.empty() or !copyRightNum.empty()) {
                uint32_t lastDigitsSum = digitOverflowOnPrevIter;
                if (!copyLeftNum.empty()) {
                    lastDigitsSum += copyLeftNum.back();
                    copyLeftNum.pop_back();
                }
                if (!copyRightNum.empty()) {
                    lastDigitsSum += copyRightNum.back();
                    copyRightNum.pop_back();
                }
                digitOverflowOnPrevIter = 0;

                if (lastDigitsSum > MAX_DIGIT) {
                    digitOverflowOnPrevIter = lastDigitsSum / (MAX_DIGIT + 1);
                    lastDigitsSum -= (MAX_DIGIT + 1);
                }
                result.num.insert(result.num.begin(), lastDigitsSum);
            }
            if (digitOverflowOnPrevIter) {
                result.num.insert(result.num.begin(), digitOverflowOnPrevIter);
            }
            return bignum(result);
        }

        bignum operator*(const bignum &rightNum) const {
            bignum result(NOT_INITIALIZED_NUMBER_VAL);
            std::vector<bignum> resultMultiplications;
            std::vector<uint32_t> copyLeftNum = getVecWithDigits();
            std::vector<uint32_t> copyRightNum = rightNum.getVecWithDigits();

            uint32_t counterMultiplications = 0;
            uint32_t digitOverflowOnPrevIter = 0;

            while (!copyRightNum.empty()) {
                uint32_t multiplier = copyRightNum.back();
                copyRightNum.pop_back();

                resultMultiplications.emplace_back(NOT_INITIALIZED_NUMBER_VAL);
                digitOverflowOnPrevIter = 0;

                for (size_t i = copyLeftNum.size(); i != 0; i--) {
                    uint32_t resDigitMultiplication = copyLeftNum[i - 1] * multiplier + digitOverflowOnPrevIter;
                    resultMultiplications[counterMultiplications].num.insert(
                            resultMultiplications[counterMultiplications].num.begin(),
                            resDigitMultiplication % (MAX_DIGIT + 1)
                    );
                    digitOverflowOnPrevIter = resDigitMultiplication / (MAX_DIGIT + 1);
                }

                for (size_t i = 0; i < counterMultiplications; i++) {
                    resultMultiplications[counterMultiplications].num.push_back(0);
                }

                if (digitOverflowOnPrevIter) {
                    resultMultiplications[counterMultiplications].num.insert(
                            resultMultiplications[counterMultiplications].num.begin(),
                            digitOverflowOnPrevIter
                    );
                }
                counterMultiplications += 1;
            }
            while (!resultMultiplications.empty()) {
                bignum multiplicationItem = bignum(resultMultiplications.back());
                resultMultiplications.pop_back();
                result = result + multiplicationItem;
            }
            return bignum(result);
        }

        bignum *operator*=(const size_t multiplier) {
            bignum result(NOT_INITIALIZED_NUMBER_VAL);
            std::vector<bignum> resultMultiplications;
            std::vector<uint32_t> copyLeftNum = getVecWithDigits();

            uint32_t counterMultiplications = 0;
            uint32_t digitOverflowOnPrevIter = 0;

            resultMultiplications.emplace_back(NOT_INITIALIZED_NUMBER_VAL);
            digitOverflowOnPrevIter = 0;

            for (size_t i = copyLeftNum.size(); i != 0; i--) {
                uint32_t resDigitMultiplication = copyLeftNum[i - 1] * multiplier + digitOverflowOnPrevIter;
                resultMultiplications[counterMultiplications].num.insert(
                        resultMultiplications[counterMultiplications].num.begin(),
                        resDigitMultiplication % (MAX_DIGIT + 1)
                );
                digitOverflowOnPrevIter = resDigitMultiplication / (MAX_DIGIT + 1);
            }
            if (digitOverflowOnPrevIter) {
                resultMultiplications[counterMultiplications].num.insert(
                        resultMultiplications[counterMultiplications].num.begin(),
                        digitOverflowOnPrevIter
                );
            }
            counterMultiplications += 1;
            while (!resultMultiplications.empty()) {
                bignum multiplicationItem = bignum(resultMultiplications.back());
                resultMultiplications.pop_back();
                result = result + multiplicationItem;
            }
            num = result.num;
            return this;
        }

        bignum *operator+=(const bignum &rightNum) {
            bignum result(NOT_INITIALIZED_NUMBER_VAL);
            result.num = this->num;
            result = result + rightNum;
            this->num = result.num;
            return this;
        }

        bignum *operator*=(const bignum &rightNum) {
            bignum result(NOT_INITIALIZED_NUMBER_VAL);
            result.num = this->num;
            result = result * rightNum;
            this->num = result.num;
            return this;
        }

        std::string to_string() const {
            numAsString = "";
            for (unsigned int i: num) {
                numAsString += std::to_string(i);
            }
            return numAsString;
        }

        std::string to_string(const size_t start, const size_t end) const {
            numAsString = "";
            for (size_t i = start; i < end; i++) {
                numAsString += std::to_string(num[i]);
            }
            return numAsString;
        }
    };

    class polynomial {
    private:
        std::vector<uint32_t> multipliers;
        std::vector<uint32_t> degrees;

        void makePolynomFullForm() {
            uint32_t maxPolynomDegree = degrees[0];
            for (uint32_t i = 0; i < maxPolynomDegree; i++) {
                if (degrees[i] != maxPolynomDegree - i) {
                    degrees.insert(degrees.begin() + i, maxPolynomDegree - i);
                    multipliers.insert(multipliers.begin() + i, 0);
                }
            }
        }

    public:
        explicit polynomial(const std::string &expression) {
            bool isElemIsDegree = false;
            bool elemIsDigit = false;
            char prevElem = '0';

            for (const char elem: expression) {
                if (isspace(elem)) {
                    continue;
                }
                if (isElemIsDegree) {
                    degrees.push_back(std::stoi(std::string(1, elem)));
                    isElemIsDegree = false;
                    elemIsDigit = false;
                } else if (elem == '^') {
                    isElemIsDegree = true;
                    elemIsDigit = false;
                    continue;
                } else if (elem == '+' or elem == '-' or elem == '*') {
                    elemIsDigit = false;
                } else if (isdigit(elem)) {
                    if (elemIsDigit) {
                        uint32_t lastDigit = multipliers.back();
                        multipliers.pop_back();
                        std::string numberAsSting = std::to_string(lastDigit) + elem;
                        multipliers.push_back(std::stoi(numberAsSting));
                        continue;
                    }
                    multipliers.push_back(std::stoi(std::string(1, elem)));
                    elemIsDigit = true;
                } else {
                    if (prevElem != '*' and !elemIsDigit) {
                        multipliers.push_back(1);
                    }
                }
                prevElem = elem;
            }
            makePolynomFullForm();
        }

        uint32_t at(int index) const {
            return multipliers[multipliers.size() - 1 - index];
        }

        uint32_t at(int index) {
            if (index + 1 <= static_cast<int>(multipliers.size())) {
                return multipliers[multipliers.size() - 1 - index];
            }

            for (size_t i = index + 1 - multipliers.size(); i > 0; i--) {
                multipliers.insert(multipliers.begin(), 0);
                degrees.insert(degrees.begin(), 0);
            }

            return multipliers[multipliers.size() - 1 - index];
        }

        template<typename T>
        T operator()(T xVal) const {
            if (multipliers.size() == 1) {
                return xVal * static_cast<T>(multipliers[0]);
            }
            std::vector<T> gornerElems;
            for (size_t i = 0; i < multipliers.size(); i++) {
                if (i == 0) {
                    gornerElems.push_back(static_cast<T>(multipliers[i]));
                    continue;
                }
                gornerElems.push_back(xVal * gornerElems[i - 1] + static_cast<T>(multipliers[i]));
            }

            return static_cast<T>(gornerElems.back());
        }
    };


    std::ostream &operator<<(std::ostream &os, const bignum &obj) {
        os << obj.getNumAsString();
        return os;
    }

    std::istream &operator>>(std::istream &is, bignum &obj) {
        std::string numAsString;
        is >> numAsString;
        obj = bignum(numAsString);
        return is;
    }
}

