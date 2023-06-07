//
// Created by Ющенко Андрей on 07.06.2023.
//

#include "Numeral_2.h"

string Numeral_2 :: DecimalToBinary(int decimalNumber) {

    string binaryStr = "";

    if (decimalNumber == 0) {
        return "0";
    }
    while (decimalNumber > 0) {
        binaryStr = ((decimalNumber & 1) ? "1" : "0") + binaryStr;
        decimalNumber >>= 1;
    }
    return binaryStr;
}

//конструктори
Numeral_2 :: Numeral_2() {
    binaryNumber = "0";
}
Numeral_2:: Numeral_2(const string& binaryNumber) {
    this->binaryNumber = binaryNumber;
}
Numeral_2:: Numeral_2(int decimalNumber) {
    this->binaryNumber = DecimalToBinary(decimalNumber);
}

//методи
string Numeral_2 :: getBinaryNumber() {
    return binaryNumber;
}
int Numeral_2 :: BinaryToDecimal(const string& binaryNumber) {
    int decimalNumber = 0;

    for (int i = binaryNumber.length() - 1; i >= 0; i--) {
        if (binaryNumber[i] == '1') {
            decimalNumber += pow(2, binaryNumber.length() - 1 - i);
        }
    }
    return decimalNumber;
}

//оператори
Numeral_2 & Numeral_2 :: operator++() {

    int res = BinaryToDecimal(binaryNumber);
    ++res;
    this->binaryNumber = DecimalToBinary(res);
    return *this;
}
Numeral_2 Numeral_2 :: operator+(Numeral_2& other) {

    int var1 = BinaryToDecimal(this->binaryNumber);
    int var2 = BinaryToDecimal(other.binaryNumber);

    int var3 = 0;
    var3 = var1 + var2;

    Numeral_2 temp = DecimalToBinary(var3);
    return temp;
}
Numeral_2& Numeral_2 :: operator +=(Numeral_2& other) {

    int var1 = BinaryToDecimal(this->binaryNumber);
    int var2 = BinaryToDecimal(other.binaryNumber);

    var1 += var2;

    this->binaryNumber = DecimalToBinary(var1);

    return *this;
}